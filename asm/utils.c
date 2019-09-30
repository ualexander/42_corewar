/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:01:58 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/30 19:00:03 by vsanta           ###   ########.fr       */
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
