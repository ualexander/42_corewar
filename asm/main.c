/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 20:01:32 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"


/*
r12
%12
%:label
12
:label
*/

// REG - регистр r 1-16  (code 01) (size 1 bite)
// DIR - прямой % + число/метка (прямое это само значение) (code 10) (size T_DIR)
// IND - непрямое число/метка (непрямое это относительный адрес байт) (code 11) (size 2 bite)


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
	asemb->prog_size = 0;
	ft_bzero((void*)asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero((void*)asemb->comment, COMMENT_LENGTH + 1);
	asemb->labels = NULL;
	asemb->insts = NULL;
	return (asemb);
}




// #define REG_CODE					1
// #define DIR_CODE					2
// #define IND_CODE					3

	// new->args[0].bite_move = 6;
	// new->args[1].bite_move = 4;
	// new->args[2].bite_move = 2;


/* ************************************************************************** */

void set_args_size(t_lst *inst)
{
	int arg_i;

	while (inst)
	{
		arg_i = 0;
		INST(inst)->size = INST(inst)->op->args_types_code ? 2 : 1;
		while (arg_i < INST(inst)->op->args_num)
		{
			if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bite_move) & REG_CODE) == REG_CODE)
				INST(inst)->size += 1;
			if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bite_move) & DIR_CODE) == DIR_CODE)
				INST(inst)->size += INST(inst)->op->t_dir_size;
			if (((INST(inst)->args_codes >> INST(inst)->args[arg_i].bite_move) & IND_CODE) == IND_CODE)
				INST(inst)->size += 2;
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

	set_args_size(asemb->insts);

	t_inst *cur_inst = NULL;
	t_label *cur_lab = NULL;


	// char  re;
 
	// re = 0;

	// re = re | (IND_CODE << 6);
	// printf("|%u|\n", re);
	
	while ((cur_inst = (t_inst*)ft_lst_pop_front_data(&(asemb->insts))))
	{
		printf("op = %s | size = %i | arg_codes = %u | arg0 = %i, larg0 = %s | arg1 = %i, larg1 = %s | arg2 = %i, larg2 = %s\n",
			cur_inst->op->name, cur_inst->size, cur_inst->args_codes, cur_inst->args[0].arg, cur_inst->args[0].larg, cur_inst->args[1].arg, cur_inst->args[1].larg, cur_inst->args[2].arg, cur_inst->args[2].larg);
	}


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