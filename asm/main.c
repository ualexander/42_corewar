/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/26 20:11:00 by vsanta           ###   ########.fr       */
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


int get_name(t_asm *asemb)
{
	int	first_bracket;
	int second_bracket;
	char *tmp;

	first_bracket = ft_get_char_i(asemb->parse_line, CMD_BRACKETS);
	second_bracket = first_bracket == -1 ? -1 : ft_get_char_i(&((asemb->parse_line)[first_bracket + 1]), CMD_BRACKETS);
	
	printf("%i | %i\n", first_bracket, second_bracket);
	

	// if (asemb->name == NULL && ff == -1)
	// 	return (-1);
	// if (asemb->name == NULL)
	// 	asemb->name = ft_strdup(&((asemb->parse_line)[ff]));
	// else
	// {
		
	// 	tmp = ft_strjoin
	// }

	return (0);
}



int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		// if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);

		printf("%i\n", line_type);
		if (line_type == 30)
			line_type = get_name(asemb);

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