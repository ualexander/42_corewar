/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/29 16:49:52 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init()
{
	t_asm *asemb;

	asemb = (t_asm*)malloc(sizeof(t_asm));
	asemb->fd = -1;
	asemb->parse_line = NULL;
	asemb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asemb->comment, COMMENT_LENGTH + 1);
	return (asemb);
}



// char *get_line(char *line, char *dest, int len)
// {
	
// }


int set_prog_name(t_asm *asemb)
{
	int start;
	int len;
	char *tmp;
	int ret_val;

	start = ft_get_char_i(asemb->parse_line, CMD_BRACKETS) + 1;
	len = ft_get_char_i(&(asemb->parse_line[start]), CMD_BRACKETS);


	
	if (asemb->prog_name[0] == 0 && len == -1)
		len = ft_strlen(&(asemb->parse_line[start]));
	else if (asemb->prog_name[0] != 0 && len == -1)
	{
		len = start;
		start = 0;
		ret_val = 30;
	}
	tmp = ft_strsub(asemb->parse_line, start, len);

	printf("--- %s ----\n", tmp);

	// .name           "HelasdkasH"
	// .name           "Helasd
	// kasH"

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
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);

		printf("%i\n", line_type);
		if (line_type == 30)
			line_type = set_prog_name(asemb);
		else
		{
			line_type = 0 ;
		}
		

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