/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 16:26:25 by vsanta           ###   ########.fr       */
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

/*
r12
%12
%:label
12
:label
*/

// REG - регистр r 1-16  (code 01) (size 1 bite)
// DIR - прямой % + число/метка (прямое это само значение) (code 10) (size T_DIR)
// IND - непрямое число/метка (непрямое это относительный адрес байт) (code 11) (size 2 bite)



// char *set_arg(t_asm *asemb, char *line, int *arg, char **larg)
// {
// 	int arg_type;

// 	arg_type = get_arg_type(line);
// 	if (arg_type == T_REG || arg_type == T_DIR)
// 		return (set_val_numb(asemb, arg, &line[1]));
// 	else if (arg_type == T_IND)
// 		return (set_val_numb(asemb, arg, line));
// 	else if (arg_type == (T_DIR | T_LAB))
// 		return (set_val_str(asemb, larg, &line[2]));
// 	else if (arg_type == (T_IND | T_LAB))
// 		return (set_val_str(asemb, larg, &line[1]));
// 	else
// 		put_error(asemb); // not valid token
// 	return (NULL);
// }




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


// char *set_arg_0(t_asm *asemb, t_inst *inst, char *line)
// {
// 	int arg_type;

// 	arg_type = get_arg_type(line);
// 	inst->args_codes = modif_arg_codes(inst->args_codes, arg_type, 6);
// 	if (arg_type & T_LAB)
// 		return (set_arg(asemb, line, 0, &(inst->larg_0)));
// 	else
// 		return (set_arg(asemb, line, &(inst->arg_0), NULL));
// }

// char *set_arg_1(t_asm *asemb, t_inst *inst, char *line)
// {
// 	int arg_type;

// 	arg_type = get_arg_type(line);
// 	inst->args_codes = modif_arg_codes(inst->args_codes, arg_type, 4);
// 	if (arg_type & T_LAB)
// 		return (set_arg(asemb, line, 0, &(inst->larg_1)));
// 	else
// 		return (set_arg(asemb, line, &(inst->arg_1), NULL));
// }

// char *set_arg_2(t_asm *asemb, t_inst *inst, char *line)
// {
// 	int arg_type;

// 	arg_type = get_arg_type(line);
// 	inst->args_codes = modif_arg_codes(inst->args_codes, arg_type, 2);
// 	if (arg_type & T_LAB)
// 		return (set_arg(asemb, line, 0, &(inst->larg_2)));
// 	else
// 		return (set_arg(asemb, line, &(inst->arg_2), NULL));
// }


// int check_last(t_asm *asemb, char *line)
// {
// 	if (get_arg_type(line) != 0)
// 		put_error(asemb); // too much args
// 	if (line[0] != '\0' && is_comment_char(line[0]) == 0)
// 		put_error(asemb); // not valid token
// }


int parse_instruction(t_asm *asemb, char *line)
{
	t_inst *inst;
	int arg_i;

	
	if ((inst = instruction_new(asemb->row)) == NULL)
		put_error(asemb); // system error
	arg_i = 0;
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
	line = set_op(asemb, inst, line);
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);

	while (arg_i < inst->op->args_num)
	{
		line = set_arg(asemb, inst, arg_i, line);
		line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
		printf("arg codes = %u | arg = %i | larg = %s || ", inst->args_codes, inst->args[arg_i].arg, inst->args[arg_i].larg);
		arg_i++;
	}
	printf("\n");
	





	// while (i < inst->op->args_num)
	// {
	// 	line = set_arg(asemb, line, &(inst->args[i]), &(inst->args_codes));
	// 	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
	// 	printf("arg codes = %u | arg0 = %i | larg0 = %s\n", inst->args_codes, inst->args[0].arg, inst->args[0].larg);
	// 	i++;
	// }



	

	// line = set_arg_1(asemb, inst, line);
	// line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);

	// line = set_arg_2(asemb, inst, line);
	// line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);

	



	// // line = set_int(asemb, &rere, line);

	// printf("---- |%s| ---- |%s| --- |%s| ----\n", inst->op->name, rere, line);
	
	
	connect_with_labels(asemb, inst);
	ft_lst_push_back_data(&(asemb->insts), (void*)inst);
	
	return (0);
}


int parse_label(t_asm *asemb, char *line)
{
	t_label *label;
	char	*label_name;
	int		char_i;

	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
	char_i = ft_get_char_i(line, LABEL_CHAR);
	if ((label_name = ft_strsub(line, 0, char_i)) == NULL)
		put_error(asemb); // system error
	if ((label = label_new(label_name)) == NULL)
		put_error(asemb); // system error // free label_name
	ft_lst_push_back_data(&(asemb->labels_queue), (void*)label);
	line = &(line[char_i + 1]);
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
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
