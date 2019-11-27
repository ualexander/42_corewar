/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:21:23 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/27 18:45:22 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** arg in_procces
** if CMD_START in_procces must be 0
** if CMD_PROCCES in_procces must be 1
** return value
** if done return 0 else return 1
** if error return -1
*/

static int	set_line_command(char *srs, char *dest, int in_procces, int max_len)
{
	int		start;
	int		len;
	char	*tmp;

	start = ft_get_char_i(srs, BRACKET_CHAR);
	len = ft_get_char_i(&(srs[start + 1]), BRACKET_CHAR);
	if (in_procces == 0)
	{
		in_procces = len == -1 ? 1 : 0;
		len = len == -1 ? ft_strlen(&(srs[start + 1])) : len;
		start++;
	}
	else if (in_procces == 1)
	{
		in_procces = start == -1 ? 1 : 0;
		len = start == -1 ? ft_strlen(srs) : start;
		start = 0;
	}
	if ((tmp = ft_strsub(srs, start, len)) == NULL ||
		(int)ft_strlen(dest) + len + (in_procces == 1 ? 1 : 0) > max_len)
		in_procces = -1;
	else
		ft_strncpy(&(dest[ft_strlen(dest)]), tmp, len);
	dest[ft_strlen(dest)] = in_procces == 1 ? '\n' : '\0';
	return (ft_str_free(&tmp, in_procces));
}

static int	command_end_i(char *line)
{
	int bracket_f;
	int bracket_s;
	int end;

	bracket_f = ft_get_char_i(line, BRACKET_CHAR);
	bracket_s = ft_get_char_i(&(line[bracket_f + 1]), BRACKET_CHAR);
	end = bracket_f + 1 + (bracket_s == -1 ? 0 : bracket_s + 1);
	end += ft_skip_chars_i(&(line[end]), SPACE_CHARS);
	return (end);
}

int			parse_command_name(t_asm *asemb, int line_type)
{
	int last;

	asemb->name_set = 1;
	line_type = set_line_command(asemb->parse_line, asemb->name,
				line_type == CMD_NAME_START ? 0 : 1, PROG_NAME_LENGTH);
	if (line_type == -1)
		put_error(asemb, ERR_LONG_NAME, 0, 0);
	last = command_end_i(asemb->parse_line);
	if (line_type == 0 && (asemb->parse_line[last] != '\0' &&
		asemb->parse_line[last] != COMMENT_CHAR &&
		asemb->parse_line[last] != COMMENT_CHAR_ALT))
		put_error(asemb, ERR_SYNTX, asemb->row, last + 1);
	return (line_type == 0 ? 0 : CMD_NAME_PROCCES);
}

int			parse_command_comment(t_asm *asemb, int line_type)
{
	int last;

	asemb->comment_set = 1;
	line_type = set_line_command(asemb->parse_line, asemb->comment,
		line_type == CMD_COMMENT_START ? 0 : 1, COMMENT_LENGTH);
	if (line_type == -1)
		put_error(asemb, ERR_LONG_COM, 0, 0);
	last = command_end_i(asemb->parse_line);
	if (line_type == 0 && (asemb->parse_line[last] != '\0' &&
		asemb->parse_line[last] != COMMENT_CHAR &&
		asemb->parse_line[last] != COMMENT_CHAR_ALT))
		put_error(asemb, ERR_SYNTX, asemb->row, last + 1);
	return (line_type == 0 ? 0 : CMD_COMMENT_PROCCES);
}
