/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:20:14 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 18:28:02 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

static t_label *label_new(char *name)
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
