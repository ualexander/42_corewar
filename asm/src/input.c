/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:46:48 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/27 17:18:38 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_file_name(char *file_name, char *ext)
{
	int i;

	i = ft_get_char_i_rev(file_name, '.');
	if (i == -1 || ft_strlen(file_name) < ft_strlen(ext) ||
		ft_strlen(ext) < 2 || ext[0] != '.')
		return (NULL);
	if (ft_strcmp(&(file_name[i]), ext) != 0)
		return (NULL);
	return (ft_strsub(file_name, 0, i));
}

void		open_input_file(t_asm *asemb, int ac, char **av)
{
	if (ac != 2)
		put_error_file(asemb, ERR_NUMB_ARG, NULL);
	else if ((asemb->fd = open(av[1], O_RDONLY)) == -1)
		put_error_file(asemb, ERR_READ_FILE, av[1]);
	else if ((asemb->file_name =
		get_file_name(av[1], INPUT_FILE_EXT)) == NULL)
		put_error_file(asemb, ERR_FILE_NAME, NULL);
}
