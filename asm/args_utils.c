/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:56:44 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/29 17:57:08 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

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
