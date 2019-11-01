/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:55:18 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/29 19:52:53 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "asm.h"

// t_pos *init_pos(void)
// {
// 	t_pos *pos;
// 	if ((pos = malloc(sizeof(t_pos))) == NULL)
// 		return NULL;
// 	pos->lab = -1;
// 	pos->inst = -1;
// 	pos->arg_0 = -1;
// 	pos->arg_1 = -1;
// 	pos->arg_2 = -1;
// 	pos->i = 0;
// 	pos->is_sep = 1;
// 	return (pos);
// }

// t_pos *get_instr_pos(t_asm *asemb, int line_type)
// {
// 	t_pos *ps;

// 	ps = init_pos();
// 	while (asemb->parse_line[ps->i])
// 	{
// 		if (ps->arg_0 != -1 && ps->arg_1 != -1 && ps->arg_2 != -1)
// 			break;
// 		else if (ps->lab == -1 && ps->inst == -1 &&
// 			is_instruction_label(&(asemb->parse_line[ps->i])))
// 			ps->lab = ps->i;
// 		else if (ps->inst == -1 && is_instruction(&(asemb->parse_line[ps->i])))
// 			ps->inst = ps->i;
// 		else if (ps->inst != -1 && ps->is_sep &&
// 			get_arg_type(&(asemb->parse_line[ps->i])))
// 		{
// 			ps->arg_2 = ps->arg_2 == -1 && ps->arg_1 != -1 ? ps->i : ps->arg_2;
// 			ps->arg_1 = ps->arg_1 == -1 && ps->arg_0 != -1 ? ps->i : ps->arg_1;
// 			ps->arg_0 = ps->arg_0 == -1 ? ps->i : ps->arg_0;
// 			ps->is_sep = 0;
// 		}
// 		else if (asemb->parse_line[ps->i] == SEPARATOR_CHAR)
// 			ps->is_sep = 1;
// 		ps->i++;
// 	}
// 	return (ps);
// }

// int parse_instruction(t_asm *asemb, int line_type)
// {
// 	t_pos *pos;

// 	pos = get_instr_pos(asemb, line_type);


	
// 	printf("lab = %i | inst = %i | arg_0 = %i | arg_1 = %i | arg_2 = %i \n", pos->lab, pos->inst, pos->arg_0, pos->arg_1, pos->arg_2);

// 	return (0);
// }