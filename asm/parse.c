/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 18:25:04 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

int parse_file(t_asm *asemb)
{
	int line_type;

	line_type = 0;
	while ((asemb->gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);
		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
			line_type = 0;
		else if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = parse_command_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = parse_command_comment(asemb, line_type);
		else if (line_type == IS_LABEL)
			line_type = parse_label(asemb, asemb->parse_line);
		else if (line_type == IS_INSTRUCTION)
			line_type = parse_instruction(asemb, asemb->parse_line);
		else
			line_type = 0;
	}
	return (1);
}
