/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:48:00 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/20 18:48:19 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_insts(t_lst **inst, int ret)
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

int		free_labels(t_lst **label, int ret)
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

int		free_asm(t_asm *asemb, int ret)
{
	free_insts(&(asemb->insts), 0);
	free_labels(&(asemb->labels), 0);
	free_labels(&(asemb->labels_queue), 0);
	ft_str_free(&(asemb->parse_line), 0);
	free(asemb);
	return (ret);
}

void	put_error(t_asm *asemb, int err_n, int row, int col)
{
	if (err_n == ERR_LEX)
		ft_printf("Lexical error at [%03i:%03i]\n", row, col);
	else if (err_n == ERR_LEX_NL)
		ft_printf("Lexical error - unexpected end of input"\
			" (Perhaps you forgot to end with a newline ?\n");
	else if (err_n == ERR_SYNTX)
		ft_printf("Syntax error at [%03u:%03i]\n", row, col);
	else if (err_n == ERR_LONG_NAME)
		ft_printf("Champion name too long (Max length %u)\n", PROG_NAME_LENGTH);
	else if (err_n == ERR_LONG_COM)
		ft_printf("Champion comment too long"\
			" (Max length %u)\n", COMMENT_LENGTH);
	else
		ft_printf("System error - %i\n", err_n);
	exit(free_asm(asemb, err_n));
}

void	put_error_inst(t_asm *asemb, int row, int arg_i, char *op_name)
{
	ft_printf("Invalid parameter %i type indirect"\
		" for instruction \"%s\" in line %i\n", arg_i, op_name, row);
	exit(free_asm(asemb, ERR_INVALID_PARAM));
}

void	put_error_label(t_asm *asemb, int row, char *label)
{
	ft_printf("Undeclared label \"%s\" in line %i\n", label, row);
	exit(free_asm(asemb, 6));
}
