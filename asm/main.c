/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/26 18:06:41 by vsanta           ###   ########.fr       */
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



int parse_file(t_asm *asemb)
{
	int i;

	int gnl;
	int line_type;

	i = 1;
	line_type = 0;

	

	while (i < 20)
	{
		gnl = get_next_line(asemb->fd, &(asemb->parse_line));
		// if (line_type == 0)
		// 	line_type = get_line_type(asemb->parse_line);
		// if (line_type == LINE_CMD_NAME)
		// 	line_type = get_name(asemb);

		// printf("%i\n", ft_get_char_i(asemb->parse_line, '"'));

		// printf("%i\n", ft_strchr(asemb->parse_line, '"') - asemb->parse_line);
		printf("%i | %i | %zu\n", i, gnl, ft_strlen(asemb->parse_line));

		//printf("%i | %i| %s\n", gnl, get_line_type(asemb->parse_line), asemb->parse_line);
		i++;
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

	//printf("%s\n", ft_strchr(LABEL_CHARS, '9'));

	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}