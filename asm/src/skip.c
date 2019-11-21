/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:15:55 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/21 19:52:44 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	skip_space(char **line)
{
	int	skip_chars;

	skip_chars = ft_skip_chars_i(*line, SPACE_CHARS);
	*line = &((*line)[skip_chars]);
	return (skip_chars);
}

int	skip_space_and_sep(char **line)
{
	skip_space(line);
	if ((*line)[0] != SEPARATOR_CHAR)
		return (0);
	*line = &((*line)[1]);
	skip_space(line);
	return (1);
}
