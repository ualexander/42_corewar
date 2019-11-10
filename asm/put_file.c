/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:57:48 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/10 16:58:56 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

void file_put_arg(int fd, int val, int byts)
{
	int data;

	while (byts)
	{
		data = val >> (8 * (byts - 1));
		write(fd, &(data), 1);
		byts--;
	}
}

void put_exec_code(t_lst *inst, int fd)
{
	int arg_i;
	while (inst)
	{
		arg_i = 0;
		file_put_arg(fd, INST(inst)->op->code, 1);

		if (INST(inst)->op->args_types_code)
				file_put_arg(fd, INST(inst)->args_codes, 1);

		while (arg_i < INST(inst)->op->args_num)
		{
			file_put_arg(fd, INST(inst)->args[arg_i].arg,
				get_arg_size(INST(inst)->args_codes,
					INST(inst)->args[arg_i], INST(inst)->op));
			arg_i++;
		}
		inst = inst->next;
	}
}