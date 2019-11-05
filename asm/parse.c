/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 17:48:56 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_label *label_new(char *name)
{
	t_label *new;
	if (name == NULL)
		return (NULL);
	if ((new = (t_label*)malloc(sizeof(t_label))) == NULL)
		return (NULL);
	new->name = name;
	new->inst = NULL;
	return (new);
}

t_inst *instruction_new(int row)
{
	t_inst *new;

	if ((new = (t_inst*)malloc(sizeof(t_inst))) == NULL)
		return (NULL);
	ft_bzero((void*)new, sizeof(t_inst));
	new->row = row;
	new->args[0].bite_move = 6;
	new->args[1].bite_move = 4;
	new->args[2].bite_move = 2;
	return (new);
}

void connect_with_labels(t_asm *asemb, t_inst *inst)
{
	t_lst *cur_label;

	while ((cur_label = ft_lst_pop_front(&(asemb->labels_queue))))
	{
		LABEL(cur_label)->inst = inst;
		ft_lst_push_back(&(asemb->labels), cur_label);
	}
}

char *set_op(t_asm *asemb, t_inst *inst, char *line)
{
	inst->op = &(g_op[get_instruction_i_in_op(line)]);
	line = &(line[ft_strlen(inst->op->name)]);
	if (line[0] != DIRECT_CHAR &&
		ft_in_line_symbols_only(line, 1, SPACE_CHARS) == 0)
		put_error(asemb); // not valid token
	return (&(line[ft_skip_chars_i(line, SPACE_CHARS)]));
}

char	*set_val_numb(t_asm *asemb, int *set_numb, char *line)
{
	int	num;
	int	i;

	num = 0;
	i = line[0] == '-' ? 1 : 0;
	if ((line[0] == '-' && ft_isdigit(line[1]) == 0) ||
		(line[0] != '-' && ft_isdigit(line[0]) == 0))
		put_error(asemb); // not valid token
	while (ft_isdigit(line[i]))
	{
		num = num * 10 + line[i] - '0';
		i++;
	}
	*set_numb = (line[0] == '-' ? -num : num);
	return (&line[i]);
}

char	*set_val_str(t_asm *asemb, char **set_str, char *line)
{
	int len;

	len = 0;
	while (line[len] && ft_strchr(LABEL_CHARS, line[len]))
		len++;
	if (len == 0)
		put_error(asemb); // not valid token
	if ((*set_str = ft_strsub(line, 0, len)) == NULL)
		put_error(asemb); // system error
	return (&line[len]);
}

// REG - регистр r 1-16  (code 01) (size 1 bite)
// DIR - прямой % + число/метка (прямое это само значение) (code 10) (size T_DIR)
// IND - непрямое число/метка (непрямое это относительный адрес байт) (code 11) (size 2 bite)


unsigned char modif_arg_codes(unsigned char last_codes,
	int arg_type, int bite_move)
{
	if (arg_type & T_REG)
		return (last_codes | (REG_CODE << bite_move));
	if (arg_type & T_DIR)
		return (last_codes | (DIR_CODE << bite_move));
	if (arg_type & T_IND)
		return (last_codes | (IND_CODE << bite_move));
	return (0);
}

/* ************************************************************************** */
char *set_arg(t_asm *asemb, t_inst *inst, int arg_i, char *line)
{
	int arg_type;

	arg_type = get_arg_type(line);
	if ((arg_type & inst->op->args_types[arg_i]) == 0)
		put_error(asemb); // not valid token
	inst->args_codes = modif_arg_codes(inst->args_codes,
		arg_type, inst->args[arg_i].bite_move);
	if (arg_type == T_REG || arg_type == T_DIR)
		return (set_val_numb(asemb, &(inst->args[arg_i].arg), &line[1]));
	if (arg_type == T_IND)
		return (set_val_numb(asemb, &(inst->args[arg_i].arg), line));
	if (arg_type == (T_DIR | T_LAB))
		return (set_val_str(asemb, &(inst->args[arg_i].larg), &line[2]));
	if (arg_type == (T_IND | T_LAB))
		return (set_val_str(asemb, &(inst->args[arg_i].larg), &line[1]));
	return (NULL);
}


int skip_space(char **line)
{
	int skip_chars;

	skip_chars = ft_skip_chars_i(*line, SPACE_CHARS);
	*line = &((*line)[skip_chars]);
	return (skip_chars);
}

int skip_space_and_sep(char **line)
{
	skip_space(line);
	if ((*line)[0] != SEPARATOR_CHAR)
		return(0);
	*line = &((*line)[1]);
	skip_space(line);
	return (1);
}


int parse_instruction(t_asm *asemb, char *line)
{
	t_inst *inst;
	int arg_i;

	if ((inst = instruction_new(asemb->row)) == NULL)
		put_error(asemb); // system error
	arg_i = 0;
	skip_space(&line);
	line = set_op(asemb, inst, line);
	skip_space(&line);
	while (arg_i < inst->op->args_num)
	{
		line = set_arg(asemb, inst, arg_i, line);
		if (arg_i < (inst->op->args_num - 1) &&
			skip_space_and_sep(&line) == 0)
			put_error(asemb); // wrong separatop
		arg_i++;
	}
	skip_space(&line);
	if (line[0] != '\0' && is_comment_char(line[0]) == 0)
		put_error(asemb); // wrong symbol after label
	connect_with_labels(asemb, inst);
	ft_lst_push_back_data(&(asemb->insts), (void*)inst);
	return (0);
}

int parse_label(t_asm *asemb, char *line)
{
	t_label *label;
	char	*label_name;
	int		char_i;

	skip_space(&line);
	char_i = ft_get_char_i(line, LABEL_CHAR);
	if ((label_name = ft_strsub(line, 0, char_i)) == NULL)
		put_error(asemb); // system error
	if ((label = label_new(label_name)) == NULL)
		put_error(asemb); // system error // free label_name
	ft_lst_push_back_data(&(asemb->labels_queue), (void*)label);
	line = &(line[char_i + 1]);
	skip_space(&line);
	if (line[0] != '\0' && is_instruclion(line))
		return (parse_instruction(asemb, line));
	if (line[0] != '\0' && is_comment_char(line[0]) == 0)
		put_error(asemb); // wrong symbol after label
	return (0);
}


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
