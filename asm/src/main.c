/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/21 19:58:36 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		free_insts(t_lst **inst, int ret)
{
	t_lst *cur_inst;

	while ((cur_inst = ft_lst_pop_front(inst)))
	{
		ft_str_free(&(INST(cur_inst)->args[0].larg), 0);
		ft_str_free(&(INST(cur_inst)->args[1].larg), 0);
		ft_str_free(&(INST(cur_inst)->args[2].larg), 0);
		free(cur_inst->data);
		free(cur_inst);
	}
	return (ret);
}

static int		free_labels(t_lst **label, int ret)
{
	t_lst *cur_label;

	while ((cur_label = ft_lst_pop_front(label)))
	{
		free((LABEL(cur_label)->name));
		free(cur_label->data);
		free(cur_label);
	}
	return (ret);
}

int				free_asemb(t_asm *asemb, int ret)
{
	if (asemb)
	{
		free_insts(&(asemb->insts), 0);
		free_labels(&(asemb->labels), 0);
		free_labels(&(asemb->labels_queue), 0);
		ft_str_free(&(asemb->file_name), 0);
		ft_str_free(&(asemb->parse_line), 0);
		free(asemb);
	}
	return (ret);
}

static t_asm	*init_asemb(void)
{
	t_asm *new;

	if ((new = (t_asm*)malloc(sizeof(t_asm))) == NULL)
		return (NULL);
	ft_bzero((void*)new, sizeof(t_asm));
	new->fd = -1;
	new->gnl = -1;
	new->magic = COREWAR_EXEC_MAGIC;
	return (new);
}

int				main(int ac, char **av)
{
	t_asm *asemb;

	if ((asemb = init_asemb()) == NULL)
		put_error(asemb, 0, 0, 0);
	open_input_file(asemb, ac, av);
	parse_file(asemb);
	close(asemb->fd);
	if (asemb->insts == NULL)
		put_error(asemb, ERR_SYNTX, asemb->row + 1, 1);
	set_instructions_size(asemb, asemb->insts);
	convert_labels_to_args(asemb, asemb->insts);
	write_output_file(asemb, OUTPUT_FILE_EXT);
	return (free_asemb(asemb, 0));
}
