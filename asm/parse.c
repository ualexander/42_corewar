/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/29 20:21:13 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

// int parse_file(t_asm *asemb)
// {
// 	int gnl;
// 	int line_type;

// 	line_type = 0;
// 	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
// 	{
// 		asemb->row++;
// 		if (line_type == 0)
// 			line_type = get_line_type(asemb->parse_line);
// 		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
// 		{
// 			line_type = 0;
// 			continue ;
// 		}
// 		if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
// 			line_type = parse_command_name(asemb, line_type);
// 		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
// 			line_type = parse_command_comment(asemb, line_type);
// 		else if (line_type == ONLY_INST || line_type == ONLY_LABEL ||
// 			line_type == LABEL_INST)
// 			line_type = parse_instruction(asemb, line_type);
// 		else
// 			line_type = 0;
// 	}
// 	return (1);
// }


int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		printf("-----    %i     -----\n", get_line_type(asemb->parse_line));
	}
	return (1);
}