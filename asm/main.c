/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/24 17:13:18 by vsanta           ###   ########.fr       */
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

int skip_space_i(char *line)
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


// int is_valid_command(char *line, char *command)
// {
// 	int space_before;
// 	int cmd_len;
// 	int space_after;

// 	if (ft_strstr(line, command) == NULL)
// 		return (0);
// 	space_before = skip_space_i(line);
// 	cmd_len = ft_strlen(command);
// 	space_after = skip_space_i(&(line[space_before + cmd_len]));
// 	if (line[space_before + cmd_len + space_after] == '"')
// 		return (1);
// 	return (0);
// }


int is_valid_label(char *label)
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



int is_valid_instruction(char *instruction)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strncmp(instruction, g_op[i].name, ft_strlen(g_op[i].name)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int brackets_i(char *line, char *command)
{
	int space_before;
	int cmd_len;
	int space_after;

	space_before = skip_space_i(line);
	cmd_len = ft_strlen(command);
	space_after = skip_space_i(&(line[space_before + cmd_len]));
	if ((space_before + cmd_len + space_after) >= ft_strlen(line))
		return (0);
	return (space_before + cmd_len + space_after);
}

int get_line_type(char *line)
{
	int skip_space;

	skip_space = skip_space_i(line);
	if (ft_strlen(line) == skip_space)
		return (LINE_EMPTY);
	else if (line[skip_space] == COMMENT_CHAR || line[skip_space] == COMMENT_CHAR_ALT)
		return (LINE_COMMENT);
	else if (line[brackets_i(line, NAME_CMD_STRING)] == CMD_BRACKETS && ft_strstr(line, NAME_CMD_STRING))
		return (LINE_CMD_NAME);
	else if (line[brackets_i(line, COMMENT_CMD_STRING)] == CMD_BRACKETS && ft_strstr(line, COMMENT_CMD_STRING))
		return (LINE_CMD_COM);
	else if (is_valid_label(&(line[skip_space])))
		return (50);
	else if (is_valid_instruction(&(line[skip_space])))
		return (60);
	
	return (0);
}



int parse_file(t_asm *asemb)
{
	while (get_next_line(asemb->fd, &(asemb->parse_line)) > 0)
	{
		printf("----   %i\n", get_line_type(asemb->parse_line));
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

	parse_file(asemb);

	

	//printf("%s\n", g_type[0]);
	return (1);
}