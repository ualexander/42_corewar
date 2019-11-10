/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:57:48 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/10 17:43:58 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

void file_put_numb(int fd, int val, int byts)
{
	int data;

	while (byts)
	{
		data = val >> (8 * (byts - 1));
		write(fd, &(data), 1);
		byts--;
	}
}

void file_put_exec_code(t_lst *inst, int fd)
{
	int arg_i;
	while (inst)
	{
		arg_i = 0;
		file_put_numb(fd, INST(inst)->op->code, 1);
		if (INST(inst)->op->args_types_code)
				file_put_numb(fd, INST(inst)->args_codes, 1);

		while (arg_i < INST(inst)->op->args_num)
		{
			file_put_numb(fd, INST(inst)->args[arg_i].arg,
				INST(inst)->args[arg_i].size);
			arg_i++;
		}
		inst = inst->next;
	}
}