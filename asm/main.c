/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/23 17:57:16 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"


t_asm	*init()
{
	t_asm *asemb;

	asemb = (t_asm*)malloc(sizeof(t_asm));
	asemb->fd = -1;
	asemb->parse_line = NULL;
	asemb->name = NULL;
	asemb->comment = NULL;
	return (asemb);
}

int skip_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '	')
			i++;
		else
			break;
	}
	return (i);
}

int parse_file(t_asm *asemb)
{
	while (get_next_line(asemb->fd, &(asemb->parse_line)) > 0)
	{
		printf("len = %zu | space = %i\n", ft_strlen(asemb->parse_line), skip_space(asemb->parse_line));
	}
	return (1);
}



int main(int ac, char **av)
{
	t_asm *asemb;

	asemb = init();

	if (ac != 2)
	{
		printf("%s\n", "AC ERROR");
		return (0);
	}
		
	// printf("%i\n", ft_strncmp("Hello", "He", 3));

	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);

	

	//printf("%s\n", g_type[0]);
	return (1);
}