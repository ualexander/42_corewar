/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/09/29 19:50:42 by vsanta           ###   ########.fr       */
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

/*
** arg in_procces
** if CMD_NAME_START in_procces must be 0
** if CMD_NAME_PROCCES in_procces must be 1
** return value
** if done return 0 else return 1
** if error return -1
*/
int put_line(char *srs, char *dest, int in_procces, int max_len)
{
	int		start;
	int		len;
	char	*tmp;

	start = ft_get_char_i(srs, CMD_BRACKETS);
	len = ft_get_char_i(&(srs[start + 1]), CMD_BRACKETS);
	if (in_procces == 0)
	{
		in_procces = len == -1 ? 1 : 0;
		len = len == -1 ? ft_strlen(&(srs[start + 1])) : len;
		start++;
	}
	else if (in_procces == 1)
	{
		in_procces = start == -1 ? 1 : 0;
		len = start == -1 ? ft_strlen(srs) : start;
		start = 0;
	}
	if ((tmp = ft_strsub(srs, start, len)) == NULL ||
		ft_strlen(dest) + len + (in_procces == 1 ? 1 : 0) > max_len)
		in_procces = -1;
	else
		ft_strncpy(&(dest[ft_strlen(dest)]), tmp, len);
	dest[ft_strlen(dest)] = in_procces == 1 ? '\n' : '\0';
	return (ft_str_free(&tmp, in_procces));
}


int set_prog_name(t_asm *asemb, int line_type)
{
	int result;
	int last_brackets_i;

	result = put_line(asemb->parse_line, asemb->prog_name,
				line_type == CMD_NAME_START ? 0 : 1, PROG_NAME_LENGTH);
	if (result == -1)
		printf("ERROR NAME LEN\n");
	return (result == 0 ? 0 : CMD_NAME_PROCCES);
}


int set_comment(t_asm *asemb, int line_type)
{
	int result;
	int last_brackets_i;

	result = put_line(asemb->parse_line, asemb->comment,
				line_type == CMD_COMMENT_START ? 0 : 1, COMMENT_LENGTH);
	if (result == -1)
		printf("ERROR NAME LEN\n");
	return (result == 0 ? 0 : CMD_COMMENT_PROCCES);
}




	// int		start;
	// int		len;
	// char	*tmp;
	// int		ret_val;

	// start = ft_get_char_i(asemb->parse_line, CMD_BRACKETS);
	// len = ft_get_char_i(&(asemb->parse_line[start + 1]), CMD_BRACKETS);
	// if (line_type == LINE_CMD_NAME)
	// {
	// 	ret_val = len == -1 ? LINE_CMD_NAME + 1 : 0;
	// 	len = len == -1 ? ft_strlen(&(asemb->parse_line[start + 1])) : len;
	// 	start++;
	// }
	// else if (line_type == LINE_CMD_NAME + 1)
	// {
	// 	ret_val = start == -1 ? LINE_CMD_NAME + 1 : 0;
	// 	len = start == -1 ? ft_strlen(asemb->parse_line) : start;
	// 	start = 0;
	// }
	// tmp = ft_strsub(asemb->parse_line, start, len);
	// printf("s = %i | len = %i | --- %s ----\n", start, len, tmp);
	// return (ret_val);


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
		if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = set_prog_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = set_comment(asemb, line_type);
		else
		{
			line_type = 0;
		}
		

	}

	printf("%s\n", asemb->prog_name);
	printf("%s\n", asemb->comment);
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