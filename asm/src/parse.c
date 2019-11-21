/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/21 19:52:01 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_file(t_asm *asemb)
{
	int typ;

	typ = 0;
	while ((asemb->gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		typ = typ == 0 ?
			get_line_type(asemb, asemb->parse_line) : typ;
		if (typ == 0)
			put_error(asemb, ERR_SYNTX, asemb->row,
				ft_skip_chars_i(asemb->parse_line, SPACE_CHARS) + 1);
		if (typ == EMPTY_LINE || typ == COMMENT_LINE)
			typ = 0;
		else if (typ == CMD_NAME_START || typ == CMD_NAME_PROCCES)
			typ = parse_command_name(asemb, typ);
		else if (typ == CMD_COMMENT_START || typ == CMD_COMMENT_PROCCES)
			typ = parse_command_comment(asemb, typ);
		else if (typ == IS_LABEL)
			typ = parse_label(asemb, asemb->parse_line);
		else if (typ == IS_INSTRUCTION)
			typ = parse_instruction(asemb, asemb->parse_line);
		else
			typ = 0;
		ft_str_free(&(asemb->parse_line), 0);
	}
}
