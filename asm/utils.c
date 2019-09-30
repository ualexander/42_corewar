/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:01:58 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/30 17:03:28 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

int get_instruction_i_in_str(char *instruction)
{
	int i;

	i = 0;
	while (i < CMD_NUMBERS)
	{
		if (ft_strncmp(instruction, g_op[i].name,
			ft_strlen(g_op[i].name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
