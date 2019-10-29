/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/10/29 20:21:25 by vsanta           ###   ########.fr       */
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


	// printf("=====%i===\n", -3000 % MEM_SIZE);

	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);


	// printf("---   %i\n", is_label_inst("1qwe23:     sti r1, %:live, %1"));

	// printf("%i\n", 1111 & 14);

	//printf("%s\n", g_type[0]);
	return (1);
}