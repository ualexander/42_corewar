/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/06 20:05:58 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

# include <limits.h>


/*
r12
%12
%:label
12
:label
*/

// REG - регистр r 1-16  (code 01) (size 1 bit)
// DIR - прямой % + число/метка (прямое это само значение) (code 10) (size T_DIR)
// IND - непрямое число/метка (непрямое это относительный адрес байт) (code 11) (size 2 bit)


/*
set_arg_reg
set_arg_dir
set_arg_ind
*/


t_asm	*init_asemb(void)
{
	t_asm *asemb;

	if ((asemb = (t_asm*)malloc(sizeof(t_asm))) == NULL)
		return NULL;
	asemb->fd = -1;
	asemb->gnl = -1;
	asemb->parse_line = NULL;
	asemb->row = 0;
	asemb->magic = COREWAR_EXEC_MAGIC;
	asemb->exec_code_size = 0;
	ft_bzero((void*)asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero((void*)asemb->comment, COMMENT_LENGTH + 1);
	asemb->labels = NULL;
	asemb->labels_queue = NULL;
	asemb->insts = NULL;
	return (asemb);
}




// #define REG_CODE					1
// #define DIR_CODE					2
// #define IND_CODE					3

	// new->args[0].bit_move = 6;
	// new->args[1].bit_move = 4;
	// new->args[2].bit_move = 2;


/* ************************************************************************** */

void set_instruction_size(t_asm *asemb, t_lst *inst)
{
	int arg_i;
	unsigned int cur_bit_pos;

	cur_bit_pos = 0;
	while (inst)
	{
		arg_i = 0;
		INST(inst)->bit_pos = cur_bit_pos;
		INST(inst)->bit_size = INST(inst)->op->args_types_code ? A_REG_SIZE + A_ARGS_SIZE : A_REG_SIZE;
		while (arg_i < INST(inst)->op->args_num)
		{
			if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & IND_CODE) == IND_CODE)
				INST(inst)->bit_size += A_IND_SIZE;
			else if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & REG_CODE) == REG_CODE)
				INST(inst)->bit_size += A_REG_SIZE;
			else if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & DIR_CODE) == DIR_CODE)
				INST(inst)->bit_size += INST(inst)->op->t_dir_size;
			arg_i++;
		}
		cur_bit_pos += INST(inst)->bit_size;
		if (inst->next == NULL)
			asemb->exec_code_size = cur_bit_pos;
		inst = inst->next;
	}
}

void file_put_arg(int fd, int buf, int byts)
{
	int data;

	while (byts)
	{
		data = buf >> (8 * (byts - 1));
		write(fd, &(data), 1);
		byts--;
	}
}

t_label *find_label(t_lst *labels, char *name)
{
	while (labels)
	{
		if (ft_strcmp(LABEL(labels)->name, name) == 0)
			return (LABEL(labels));
		labels = labels->next;
	}
	return (NULL);
}

void convert_labels_to_args(t_asm *asemb, t_lst *inst)
{
	int arg_i;

	t_label *label;
	while (inst)
	{
		arg_i = 0;
		while (arg_i < INST(inst)->op->args_num)
		{
			if (INST(inst)->args[arg_i].larg)
			{
				label = find_label(asemb->labels, INST(inst)->args[arg_i].larg);
				if (label == NULL)
					put_error(asemb); // label not find
				INST(inst)->args[arg_i].arg = label->inst->bit_pos - INST(inst)->bit_pos;
			}
			arg_i++;
		}
		inst = inst->next;
	}
}




void put_exec_code(t_lst *inst, int fd)
{
	int arg_i;
	while (inst)
	{
		arg_i = 0;
		file_put_arg(fd, INST(inst)->op->code, 1);

		if (INST(inst)->op->args_types_code)
				file_put_arg(fd, INST(inst)->args_codes, 1);

		while (arg_i < INST(inst)->op->args_num)
		{

			
			if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & IND_CODE) == IND_CODE)
			{
				file_put_arg(fd, INST(inst)->args[arg_i].arg, A_IND_SIZE);
			}
				
			else if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & REG_CODE) == REG_CODE)
			{
				file_put_arg(fd, INST(inst)->args[arg_i].arg, A_REG_SIZE);
			}
				
			else if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bit_move) & DIR_CODE) == DIR_CODE)
			{
				file_put_arg(fd, INST(inst)->args[arg_i].arg, INST(inst)->op->t_dir_size);
			}
			arg_i++;
		}
		inst = inst->next;
	}
}




int main(int ac, char **av)
{


	t_asm *asemb;

	asemb = init_asemb();
	if (ac != 2)
	{
		printf("%s\n", "AC ERROR");
		return (0);
	}

	//printf("%s\n", ft_strchr(LABEL_CHARS, '9'));


	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);

	set_instruction_size(asemb, asemb->insts);
	convert_labels_to_args(asemb, asemb->insts);
	

	t_inst *cur_inst = NULL;
	t_label *cur_lab = NULL;


	// char  re;
 
	// re = 0;

	// re = re | (IND_CODE << 6);
	// printf("|%u|\n", re);

	int ffd = open("0rere", O_RDWR);
	




	printf("exec_code_size = %i\n", asemb->exec_code_size);

	file_put_arg(ffd, asemb->magic, 4);
	write(ffd, &(asemb->prog_name), 128);
	file_put_arg(ffd, 0, 4);
	file_put_arg(ffd, asemb->exec_code_size, 4);
	write(ffd, &(asemb->comment), 2048);
	file_put_arg(ffd, 0, 4);

	put_exec_code(asemb->insts, ffd);


		while ((cur_inst = (t_inst*)ft_lst_pop_front_data(&(asemb->insts))))
	{
		printf("op = %s | bit_size = %i | bit_pos = %i | arg_codes = %u | arg0 = %i, larg0 = %s | arg1 = %i, larg1 = %s | arg2 = %i, larg2 = %s\n",
			cur_inst->op->name, cur_inst->bit_size, cur_inst->bit_pos, cur_inst->args_codes, cur_inst->args[0].arg, cur_inst->args[0].larg, cur_inst->args[1].arg, cur_inst->args[1].larg, cur_inst->args[2].arg, cur_inst->args[2].larg);
		// file_put_arg(ffd, (cur_inst->args[0].arg), 1);
		// write(ffd, &(cur_inst->args[0].arg), 4);
	}


	// 989
	// 1002

	// !!! 13



	// Magic header - 4
	// Champion name - 128
	// NULL - 4
	// Champion exec code size - 4
	// Champion comment - 2048
	// NULL - 4
	// Champion exec code --||--





	

	long int num1 = 45465465465465;


	// num1 = num1 * 10;


	// int num2;


	// num2 = ((int)num1);

	// // num1 += 1;

	// // num1 

	// printf("%i\n", num2);




	// while ((cur_lab = (t_label*)ft_lst_pop_front_data(&(asemb->labels))))
	// {
	// 	printf("label = %s | ", cur_lab->name);
	// 	printf("op = %s | arg_codes = %u | arg0 = %i, larg0 = %s | arg1 = %i, larg1 = %s | arg2 = %i, larg2 = %s\n",
	// 		cur_lab->inst->op->name, cur_lab->inst->args_codes, cur_lab->inst->args[0].arg, cur_lab->inst->args[0].larg,
	// 		cur_lab->inst->args[1].arg, cur_lab->inst->args[1].larg, cur_lab->inst->args[2].arg, cur_lab->inst->args[2].larg);
	// }



	
	


	// printf("---   %i\n", is_label_inst("1qwe23:     sti r1, %:live, %1"));

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}