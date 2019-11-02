/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:58:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/02 19:56:43 by vsanta           ###   ########.fr       */
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
	new->op = -1;
	new->arg_0 = -1;
	new->arg_1 = -1;
	new->arg_2 = -1;
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


int parse_instruction(t_asm *asemb, char *line)
{
	t_inst *inst;

	if ((inst = instruction_new()) == NULL)
		put_error(asemb); // system error
	asemb->col = ft_skip_chars_i(PARSE_LINE(asemb->col), SPACE_CHARS);

	inst->line = asemb->parse_line;
	connect_with_labels(asemb, inst);
	
	return (0);
}


// int parse_label(t_asm *asemb, char line)
// {
// 	t_label *label;
// 	char	*label_name;
// 	int		label_char_i;

// 	asemb->col = ft_skip_chars_i(PARSE_LINE(asemb->col), SPACE_CHARS);
// 	label_char_i = ft_get_char_i(PARSE_LINE(asemb->col), LABEL_CHAR);
// 	if ((label_name = ft_strsub(asemb->parse_line, asemb->col, label_char_i)) == NULL)
// 		put_error(asemb); // system error
// 	if ((label = label_new(label_name)) == NULL)
// 		put_error(asemb); // system error // free label_name
// 	ft_lst_push_back_data(&(asemb->labels_queue), (void*)label);
// 	asemb->col = label_char_i + 1 + ft_skip_chars_i(PARSE_LINE(label_char_i + 1), SPACE_CHARS);
// 	if (asemb->parse_line[asemb->col] && is_instruclion(PARSE_LINE(asemb->col)))
// 		return (parse_instruction(asemb));
// 	if (asemb->parse_line[asemb->col] != '\0' &&
// 		is_comment_char(asemb->parse_line[asemb->col]) == 0)
// 	put_error(asemb); // wrong symbol after label
// 	return (0);
// }


int parse_label(t_asm *asemb, char *line)
{
	t_label *label;
	char	*label_name;
	int		char_i;

	line = &(asemb->parse_line[ft_skip_chars_i(asemb->parse_line, SPACE_CHARS)]);
	char_i = ft_get_char_i(line, LABEL_CHAR);
	if ((label_name = ft_strsub(line, 0, char_i)) == NULL)
		put_error(asemb); // system error
	if ((label = label_new(label_name)) == NULL)
		put_error(asemb); // system error // free label_name
	ft_lst_push_back_data(&(asemb->labels_queue), (void*)label);
	line = &(line[char_i + 1]);
	line = &(line[ft_skip_chars_i(line, SPACE_CHARS)]);

	asemb->col = char_i + 1 + ft_skip_chars_i(PARSE_LINE(char_i + 1), SPACE_CHARS);
	if (asemb->parse_line[asemb->col] && is_instruclion(PARSE_LINE(asemb->col)))
		return (parse_instruction(asemb, line));
	if (asemb->parse_line[asemb->col] != '\0' &&
		is_comment_char(asemb->parse_line[asemb->col]) == 0)
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
		asemb->col = 0;
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
