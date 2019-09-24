/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/24 18:44:15 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init()
{
	t_asm *asemb;

	asemb = (t_asm*)malloc(sizeof(t_asm));
	asemb->fd = -1;
	asemb->parse_line = NULL;
	asemb->name = NULL;
	asemb->comment = NULL;
	return (asemb);
}

int i_skip_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '	')
			i++;
		else
			break;
	}
	return (i);
}

int is_inst_label(char *label)
{
	int i;

	i = 0;
	while (label[i])
	{
		if (label[i] == LABEL_CHAR && i > 0)
			return (1);
		else if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			return (0);
		i++;
	}
	return (0);
}

int is_instruction(char *instruction)
{
	int i;

	i = 0;
	while (i < CMD_NUMBERS)
	{
		if (ft_strncmp(instruction, g_op[i].name, ft_strlen(g_op[i].name)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int i_brackets(char *line, char *command)
{
	int space_before;
	int cmd_len;
	int space_after;

	space_before = i_skip_space(line);
	cmd_len = ft_strlen(command);
	space_after = i_skip_space(&(line[space_before + cmd_len]));
	if ((space_before + cmd_len + space_after) >= ft_strlen(line))
		return (0);
	return (space_before + cmd_len + space_after);
}

int get_line_type(char *line)
{
	int skip_space;

	skip_space = i_skip_space(line);
	if (ft_strlen(line) == skip_space)
		return (LINE_EMPTY);
	else if (line[skip_space] == COMMENT_CHAR ||
		line[skip_space] == COMMENT_CHAR_ALT)
		return (LINE_COMMENT);
	else if (line[i_brackets(line, NAME_CMD_STRING)] == CMD_BRACKETS &&
		ft_strstr(line, NAME_CMD_STRING))
		return (LINE_CMD_NAME);
	else if (line[i_brackets(line, COMMENT_CMD_STRING)] == CMD_BRACKETS &&
		ft_strstr(line, COMMENT_CMD_STRING))
		return (LINE_CMD_COM);
	else if (is_instruction(&(line[skip_space])))
		return (LINE_INST);
	else if (is_inst_label(&(line[skip_space])))
		return (LINE_INST_LABEL);
	return (0);
}

// int get_name(t_asm *asemb)
// {

// }

int parse_file(t_asm *asemb)
{
	int i;
	int line_type;

	i = 1;
	line_type = 0;
	while (get_next_line(asemb->fd, &(asemb->parse_line)) > 0)
	{
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);



	
		// printf("%i | %i\n", i, get_line_type(asemb->parse_line));
		// i++;
	}
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

	// parse_file(asemb);

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}