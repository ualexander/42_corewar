/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/02 14:56:18 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"


t_label label_new

int parse_instruction(t_asm *asemb, int line_type)
{

}

int parse_label(t_asm *asemb, int line_type)
{
	asemb->col = ft_skip_chars_i(asemb->parse_line, SPACE_CHARS);
}


int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((asemb->gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		asemb->col = 0;
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);
		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
			line_type = 0;
		else if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = parse_command_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = parse_command_comment(asemb, line_type);
		else if (line_type == LABEL)
			line_type = parese_label(asemb, line_type);
		else if (line_type == INSTRUCTION)
			line_type = parse_instruction(asemb, line_type);
		else
			line_type = 0;
	}
	return (1);
}