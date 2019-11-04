/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:01:58 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/04 20:18:40 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

int get_instruction_i_in_op(char *instruction)
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

int get_arg_type(char *args)
{
	if (args[0] && args[0] == REG_CHAR)
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
