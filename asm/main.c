/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/29 18:09:25 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"


// REG - решистр r 1-16  (code 01) (size 1 bite)
// DIR - прямой % + число/метка (прямое это само значение) (code 10) (size T_DIR)
// IND - непрямое число/метка (непрямое это относительный адрес байт) (code 11) (size 2 bite)


t_asm	*init_asemb(void)
{
	t_asm *asemb;
	if ((asemb = (t_asm*)malloc(sizeof(t_asm))) == NULL)
		return NULL;
	asemb->fd = -1;
	asemb->row = 0;
	asemb->parse_line = NULL;
	asemb->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(asemb->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(asemb->comment, COMMENT_LENGTH + 1);
	return (asemb);
}


int parse_file(t_asm *asemb)
{
	int gnl;
	int line_type;

	line_type = 0;
	while ((gnl = get_next_line(asemb->fd, &(asemb->parse_line))) > 0)
	{
		asemb->row++;
		if (line_type == 0)
			line_type = get_line_type(asemb->parse_line);
		if (line_type == EMPTY_LINE || line_type == COMMENT_LINE)
		{
			line_type = 0;
			continue ;
		}
		if (line_type == CMD_NAME_START || line_type == CMD_NAME_PROCCES)
			line_type = parse_command_name(asemb, line_type);
		else if (line_type == CMD_COMMENT_START || line_type == CMD_COMMENT_PROCCES)
			line_type = parse_command_comment(asemb, line_type);
		else if (line_type == INSTRUCTION || line_type == INSTRUCTION_LABEL)
			line_type = parse_instruction(asemb, line_type);
		else
			line_type = 0;
	}
	return (1);
}	


int main(int ac, char **av)
{


	t_asm *asemb;

	asemb = init_asemb();
	if (ac != 2)
	{
		printf("%s\n", "AC ERROR");
		return (0);
	}

	//printf("%s\n", ft_strchr(LABEL_CHARS, '9'));


	printf("=====%i===\n", -3000 % MEM_SIZE);

	// asemb->fd = open(av[1], O_RDONLY);

	// parse_file(asemb);

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}