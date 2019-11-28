/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:20:08 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/28 17:11:56 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_inst	*instruction_new(int row)
{
	t_inst *new;

	if ((new = (t_inst*)malloc(sizeof(t_inst))) == NULL)
		return (NULL);
	ft_bzero((void*)new, sizeof(t_inst));
	new->row = row;
	new->args[0].bit_move = 6;
	new->args[1].bit_move = 4;
	new->args[2].bit_move = 2;
	return (new);
}

static char		*set_op(t_asm *asemb, t_inst *inst, char *line)
{
	inst->op = &(g_op[get_instruction_i_in_op(line)]);
	line = &(line[ft_strlen(inst->op->name)]);
	if (line[0] != DIRECT_CHAR && line[0] != '-' &&
		ft_in_line_symbols_only(line, 1, SPACE_CHARS) == 0)
		put_error(asemb, ERR_LEX, asemb->row,
			(int)(line - asemb->parse_line + 1));
	return (&(line[ft_skip_chars_i(line, SPACE_CHARS)]));
}

static char		*set_arg(t_asm *asemb, t_inst *inst, int arg_i, char *line)
{
	int arg_type;

	arg_type = get_arg_type(line);
	if ((arg_type & inst->op->args_types[arg_i]) == 0)
		put_error_inst(asemb, asemb->row, arg_i, inst->op->name);
	inst->args_codes = modif_arg_codes(inst->args_codes,
		arg_type, inst->args[arg_i].bit_move);
	if (arg_type == T_REG)
	{
		line = set_val_numb(asemb, &(inst->args[arg_i].arg), &line[1]);
		if (inst->args[arg_i].arg > MAX_REG || inst->args[arg_i].arg < 0)
			put_error(asemb, ERR_SYNTX, asemb->row, (int)
			(line - asemb->parse_line - ft_digitcount(inst->args[arg_i].arg)));
		return (line);
	}
	if (arg_type == T_DIR)
		return (set_val_numb(asemb, &(inst->args[arg_i].arg), &line[1]));
	if (arg_type == T_IND)
		return (set_val_numb(asemb, &(inst->args[arg_i].arg), line));
	if (arg_type == (T_DIR | T_LAB))
		return (set_val_str(asemb, &(inst->args[arg_i].larg), &line[2]));
	if (arg_type == (T_IND | T_LAB))
		return (set_val_str(asemb, &(inst->args[arg_i].larg), &line[1]));
	return (NULL);
}

static char		*set_args(t_asm *asemb, t_inst *inst, char *line)
{
	int		arg_i;

	arg_i = 0;
	while (arg_i < inst->op->args_num)
	{
		line = set_arg(asemb, inst, arg_i, line);
		if (arg_i < (inst->op->args_num - 1) &&
			skip_space_and_sep(&line) == 0)
			put_error(asemb, ERR_SYNTX, asemb->row,
				(int)(line - asemb->parse_line + 1));
		arg_i++;
	}
	return (line);
}

int				parse_instruction(t_asm *asemb, char *line)
{
	t_inst	*inst;

	if (asemb->gnl != IS_NEW_LINE)
		put_error(asemb, ERR_LEX_NL, 0, 0);
	if ((inst = instruction_new(asemb->row)) == NULL)
		put_error(asemb, 0, 0, 0);
	skip_space(&line);
	line = set_op(asemb, inst, line);
	skip_space(&line);
	line = set_args(asemb, inst, line);
	skip_space(&line);
	if (line[0] != '\0' && is_comment_char(line[0]) == 0)
		put_error(asemb, ERR_SYNTX, asemb->row,
			(int)(line - asemb->parse_line + 1));
	connect_with_labels(asemb, inst);
	ft_lst_push_back_data(&(asemb->insts), (void*)inst);
	return (0);
}
