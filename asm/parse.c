/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/18 20:11:12 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

void parse_file(t_asm *asemb)
{
	int line_tp;

	line_tp = 0;
	while ((asemb->gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		line_tp = line_tp == 0 ? get_line_type(asemb->parse_line) : line_tp;
		if (line_tp == 0)
			put_error(asemb, 1, NULL); // Unknown operator
		if (line_tp == EMPTY_LINE || line_tp == COMMENT_LINE)
			line_tp = 0;
		else if (line_tp == CMD_NAME_START || line_tp == CMD_NAME_PROCCES)
			line_tp = parse_command_name(asemb, line_tp);
		else if (line_tp == CMD_COMMENT_START || line_tp == CMD_COMMENT_PROCCES)
			line_tp = parse_command_comment(asemb, line_tp);
		else if (line_tp == IS_LABEL)
			line_tp = parse_label(asemb, asemb->parse_line);
		else if (line_tp == IS_INSTRUCTION)
			line_tp = parse_instruction(asemb, asemb->parse_line);
		else
			line_tp = 0;
		ft_str_free(&(asemb->parse_line), 0);
	}
}
