/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/23 19:22:50 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init_asemb(void)
{
	t_asm *asemb;
	if ((asemb = (t_asm*)malloc(sizeof(t_asm))) == NULL)
		return NULL;
	asemb->fd = -1;
	asemb->row = 0;
	asemb->parse_line = NULL;
	asemb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asemb->comment, COMMENT_LENGTH + 1);
	return (asemb);
}

int get_arg_type(char *args)
{
	if (args[0] && args[0] == REG_CHAR)
		return (T_REG);
	if (args[0] && args[0] == DIRECT_CHAR &&
		args[1] && args[1] == LABEL_CHAR)
		return (T_DIR | T_LAB);
	if (args[0] && args[0] == DIRECT_CHAR)
		return (T_DIR);
	if (args[0] && args[0] == LABEL_CHAR)
		return (T_IND | T_LAB);
	if (args[0] &&
		(args[0] == '-' || ft_isdigit(args[0])))
		return (T_IND);
	return (0);
}

t_pos *init_pos(void)
{
	t_pos *pos;
	if ((pos = malloc(sizeof(t_pos))) == NULL)
		return NULL;
	pos->lab = -1;
	pos->inst = -1;
	pos->arg_0 = -1;
	pos->arg_1 = -1;
	pos->arg_2 = -1;
	pos->i = 0;
	pos->is_sep = 1;
	return (pos);
}

t_pos *get_instr_pos(t_asm *asemb, int line_type)
{
	t_pos *ps;

	ps = init_pos();
	while (asemb->parse_line[ps->i])
	{
		if (ps->arg_0 != -1 && ps->arg_1 != -1 && ps->arg_2 != -1)
			break;
		else if (ps->lab == -1 && ps->inst == -1 &&
			is_instruction_label(&(asemb->parse_line[ps->i])))
			ps->lab = ps->i;
		else if (ps->inst == -1 && is_instruction(&(asemb->parse_line[ps->i])))
			ps->inst = ps->i;
		else if (ps->inst != -1 && ps->is_sep &&
			get_arg_type(&(asemb->parse_line[ps->i])))
		{
			ps->arg_2 = ps->arg_2 == -1 && ps->arg_1 != -1 ? ps->i : ps->arg_2;
			ps->arg_1 = ps->arg_1 == -1 && ps->arg_0 != -1 ? ps->i : ps->arg_1;
			ps->arg_0 = ps->arg_0 == -1 ? ps->i : ps->arg_0;
			ps->is_sep = 0;
		}
		else if (asemb->parse_line[ps->i] == SEPARATOR_CHAR)
			ps->is_sep = 1;
		ps->i++;
	}
	return (ps);
}

int parse_instruction(t_asm *asemb, int line_type)
{
	t_pos *pos;

	pos = get_instr_pos(asemb, line_type);


	
	printf("lab = %i | inst = %i | arg_0 = %i | arg_1 = %i | arg_2 = %i \n", pos->lab, pos->inst, pos->arg_0, pos->arg_1, pos->arg_2);

	return (0);
}

int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);
		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
		{
			line_type = 0;
			continue ;
		}
		if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = parse_command_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = parse_command_comment(asemb, line_type);
		else if (line_type == INSTRUCTION || line_type == INSTRUCTION_LABEL)
			line_type = parse_instruction(asemb, line_type);
		else
			line_type = 0;
	}
	return (1);
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

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}