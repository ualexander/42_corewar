/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:23:06 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/27 17:10:59 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				get_instruction_i_in_op(char *instruction)
{
	int i;
	int result_i;

	i = 0;
	result_i = -1;
	while (i < CMD_NUMBERS)
	{
		if (ft_strncmp(instruction, g_op[i].name,
		ft_strlen(g_op[i].name)) == 0 &&
		(result_i == -1 ||
		ft_strlen(g_op[i].name) > ft_strlen(g_op[result_i].name)))
			result_i = i;
		i++;
	}
	return (result_i);
}

int				get_arg_type(char *args)
{
	if (args[0] && args[1] && args[0] == REG_CHAR && args[1] != '-')
		return (T_REG);
	if (args[0] && args[0] == DIRECT_CHAR &&
		args[1] && args[1] == LABEL_CHAR)
		return (T_DIR | T_LAB);
	if (args[0] && args[0] == DIRECT_CHAR)
		return (T_DIR);
	if (args[0] && args[0] == LABEL_CHAR)
		return (T_IND | T_LAB);
	if (args[0] &&
		(args[0] == '-' || ft_isdigit(args[0])))
		return (T_IND);
	return (0);
}

char			*set_val_numb(t_asm *asemb, int *set_numb, char *line)
{
	unsigned long int	num;
	int					i;
	int					overflow;

	num = 0;
	i = line[0] == '-' ? 1 : 0;
	overflow = 0;
	if ((line[0] == '-' && ft_isdigit(line[1]) == 0) ||
		(line[0] != '-' && ft_isdigit(line[0]) == 0))
		put_error(asemb, ERR_LEX, asemb->row,
			(int)(line - asemb->parse_line + 1));
	while (ft_isdigit(line[i]))
	{
		num = num * 10 + line[i] - '0';
		i++;
		if (line[0] == '-' && num > LONG_MAX)
			overflow = -1;
		else if (num > LONG_MAX)
			overflow = 1;
	}
	if (overflow != 0)
		*set_numb = overflow == -1 ? 0x0 : 0xffffffff;
	else
		*set_numb = (int)(line[0] == '-' ? -num : num);
	return (&line[i]);
}

char			*set_val_str(t_asm *asemb, char **set_str, char *line)
{
	int len;

	len = 0;
	while (line[len] && ft_strchr(LABEL_CHARS, line[len]))
		len++;
	if (len == 0)
		put_error(asemb, ERR_LEX, asemb->row, (int)(line - asemb->parse_line));
	if ((*set_str = ft_strsub(line, 0, len)) == NULL)
		put_error(asemb, 0, 0, 0);
	return (&line[len]);
}

unsigned char	modif_arg_codes(unsigned char last_codes,
	int arg_type, int bit_move)
{
	if (arg_type & T_REG)
		return (last_codes | (REG_CODE << bit_move));
	if (arg_type & T_DIR)
		return (last_codes | (DIR_CODE << bit_move));
	if (arg_type & T_IND)
		return (last_codes | (IND_CODE << bit_move));
	return (0);
}
