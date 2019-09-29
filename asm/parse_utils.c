/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:28:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/29 18:21:09 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

static int is_command(char *line, char *command)
{
	int space_before;
	int cmd_len;
	int space_after;

	space_before = ft_skip_chars_i(line, SPACE_SYMBOLS);
	cmd_len = ft_strlen(command);
	if (ft_strncmp(&line[space_before], command, cmd_len) != 0)
		return (0);
	space_after = ft_skip_chars_i(&(line[space_before + cmd_len]),
					SPACE_SYMBOLS);
	if (line[space_before + cmd_len + space_after] != CMD_BRACKETS)
		return (0);
	return (1);
}

static int is_instruction_label(char *line)
{

	int label_char_i;
	int skip_space_i;

	if ((label_char_i = ft_get_char_i(line, LABEL_CHAR)) == -1)
		return (0);
	skip_space_i = ft_skip_chars_i(line, SPACE_SYMBOLS);
	return (ft_in_line_symbols_only(&line[skip_space_i],
			label_char_i - skip_space_i, LABEL_CHARS));
}

static int is_instruction(char *line)
{
	int i;
	int skip_space_i;

	i = 0;
	skip_space_i = ft_skip_chars_i(line, SPACE_SYMBOLS);
	while (i < CMD_NUMBERS)
	{
		if (ft_strncmp(&line[skip_space_i], g_op[i].name,
			ft_strlen(g_op[i].name)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int get_line_type(char *line)
{
	int skip_space_i;

	skip_space_i = ft_skip_chars_i(line, SPACE_SYMBOLS);
	if (ft_strlen(line) == skip_space_i)
		return (LINE_EMPTY);
	else if (line[skip_space_i] == COMMENT_CHAR ||
		line[skip_space_i] == COMMENT_CHAR_ALT)
		return (LINE_COMMENT);
	else if (is_command(line, NAME_CMD_STRING))
		return (CMD_NAME_START);
	else if (is_command(line, COMMENT_CMD_STRING))
		return (LINE_CMD_COMMENT);
	else if (is_instruction(line))
		return (LINE_INST);
	else if (is_instruction_label(line))
		return (LINE_INST_LABEL);
	return (0);
}
