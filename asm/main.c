/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alexandr <Alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/03 19:05:39 by Alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init(void)
{
	t_asm *asemb;

	asemb = (t_asm*)malloc(sizeof(t_asm));
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

t_pos pos_init(void)
{
	t_pos pos;

	pos.lab = -1;
	pos.inst = -1;
	pos.arg_0 = -1;
	pos.arg_1 = -1;
	pos.arg_2 = -1;
	return (pos);
}

static int is_instruction_label(char *line)
{

	int label_char_i;

	if ((label_char_i = ft_get_char_i(line, LABEL_CHAR)) == -1)
		return (0);
	return (ft_in_line_symbols_only(line, label_char_i, LABEL_CHARS));
}

static int is_instruction(char *line)
{
	return (get_instruction_i_in_op(line) == -1 ? 0 : 1);
}


int parse_unstruction(t_asm *asemb, int line_type)
{
	int		i;
	int		separator;
	t_pos	pos;

	i = 0;
	separator = 1;
	pos = pos_init();
	while (asemb->parse_line[i] && asemb->parse_line[i] != COMMENT_CHAR && asemb->parse_line[i] != COMMENT_CHAR_ALT)
	{
		if (pos.arg_0 != -1 && pos.arg_1 != -1 && pos.arg_2 != -1)
			break;
		else if (pos.lab == -1 && pos.inst == -1 && is_instruction_label(&(asemb->parse_line[i])))
			pos.lab = i;
		else if (pos.inst == -1 && is_instruction(&(asemb->parse_line[i])))
			pos.inst = i;
		else if (pos.inst != -1 && separator && get_arg_type(&(asemb->parse_line[i])))
		{
			if (pos.arg_0 == -1)
				pos.arg_0 = i;
			else if (pos.arg_1 == -1)
				pos.arg_1 = i;
			else if (pos.arg_2 == -1)
				pos.arg_2 = i;
			separator = 0;
		}
		else if (asemb->parse_line[i] == SEPARATOR_CHAR)
			separator = 1;
		i++;
	}
	printf("lab = %i | inst = %i | arg_0 = %i | arg_1 = %i | arg_2 = %i \n", pos.lab, pos.inst, pos.arg_0, pos.arg_1, pos.arg_2);
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
		printf("%i - %i\n", line_type, gnl);
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
			line_type = parse_unstruction(asemb, line_type);
		else
			line_type = 0;
	}

	printf("name = %s\n", asemb->prog_name);
	printf("comment = %s\n", asemb->comment);
	printf("rows = %i\n", asemb->row);
	return (1);
}	


int main(int ac, char **av)
{
	t_asm *asemb;

	asemb = init();

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