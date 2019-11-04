/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/04 17:08:54 by vsanta           ###   ########.fr       */
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

	// int				op;
	// int				arg_0;
	// int				arg_1;
	// int				arg_2;
	// char			*larg_0;
	// char			*larg_1;
	// char			*larg_2;
	// char			args_codes;
	
t_inst *instruction_new()
{
	t_inst *new;

	if ((new = (t_inst*)malloc(sizeof(t_inst))) == NULL)
		return (NULL);
	new->op = NULL;
	new->arg_0 = 0;
	new->arg_1 = 0;
	new->arg_2 = 0;
	new->larg_0 = NULL;
	new->larg_1 = NULL;
	new->larg_2 = NULL;
	new->args_codes = 0;
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

char *set_op(t_inst *inst, char *line)
{
	inst->op = &(g_op[get_instruction_i_in_op(line)]);
	line = &(line[ft_strlen(inst->op->name)]);
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);
	return (line);
}

char	*set_int(t_asm *asemb, int *set_int, char *line)
{
	int	num;
	int	i;

	num = 0;
	i = line[0] == '-' ? 1 : 0;
	if (line[0] == '-' && ft_isdigit(line[1]) == 0)
		put_error(asemb); // not valid token
	while (ft_isdigit(line[i]))
	{
		num = num * 10 + line[i] - '0';
		i++;
	}
	*set_int = (line[0] == '-' ? -num : num);
	return (&line[i]);
}

char	*set_label(t_asm *asemb, char **set_label, char *line)
{
	int len;

	len = 0;
	while (line[len] && ft_strchr(LABEL_CHARS, line[len]))
		len++;
	if (len == 0)
		put_error(asemb); // not valid token
	if ((*set_label = ft_strsub(line, 0, len)) == NULL)
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

/*
set_arg_reg
set_arg_numb
set_arg_label
*/


// char *set_arg_0(t_inst *inst, char *line)
// {
	
// }
// char *set_arg_1(t_inst *inst, char *line)
// {
	
// }
// char *set_arg_2(t_inst *inst, char *line)
// {
	
// }





int parse_instruction(t_asm *asemb, char *line)
{
	t_inst *inst;

	if ((inst = instruction_new()) == NULL)
		put_error(asemb); // system error
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);


	char *rere;
	line = set_op(inst, line);

	line = set_label(asemb, &rere, line);

	// line = set_int(asemb, &rere, line);

	printf("---- |%s| ---- |%s| --- |%s| ----\n", inst->op->name, rere, line);
	
	inst->line = asemb->parse_line;
	connect_with_labels(asemb, inst);
	
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
