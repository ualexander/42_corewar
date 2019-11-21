/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:57:48 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/21 19:57:30 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	file_put_numb(int fd, int val, int byts)
{
	int data;

	while (byts)
	{
		data = val >> (8 * (byts - 1));
		write(fd, &(data), 1);
		byts--;
	}
}

static void	file_put_exec_code(int fd, t_lst *inst)
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

void		write_output_file(t_asm *asemb, char *ext)
{
	char *output_file_name;

	output_file_name = NULL;
	if ((output_file_name = ft_strjoin(asemb->file_name, ext)) == NULL ||
		(asemb->fd =
			open(output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		put_error_file(asemb,
			ft_str_free(&output_file_name, ERR_CREATE_FILE), NULL);
	file_put_numb(asemb->fd, asemb->magic, 4);
	write(asemb->fd, &(asemb->name), 128);
	file_put_numb(asemb->fd, 0, 4);
	file_put_numb(asemb->fd, asemb->exec_code_size, 4);
	write(asemb->fd, &(asemb->comment), 2048);
	file_put_numb(asemb->fd, 0, 4);
	file_put_exec_code(asemb->fd, asemb->insts);
	close(asemb->fd);
	ft_printf("Writing output program to \"%s\"\n", output_file_name);
	ft_str_free(&output_file_name, 0);
}
