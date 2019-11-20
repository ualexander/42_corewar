/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:02:54 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/20 16:30:47 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

t_asm	*init_asemb(void)
{
	t_asm *asemb;

	if ((asemb = (t_asm*)malloc(sizeof(t_asm))) == NULL)
		return NULL;
	asemb->fd = -1;
	asemb->gnl = -1;
	asemb->parse_line = NULL;
	asemb->row = 0;
	asemb->magic = COREWAR_EXEC_MAGIC;
	asemb->exec_code_size = 0;
	ft_bzero((void*)asemb->name, PROG_NAME_LENGTH + 1);
	asemb->name_set = 0;
	ft_bzero((void*)asemb->comment, COMMENT_LENGTH + 1);
	asemb->comment_set = 0;
	asemb->labels = NULL;
	asemb->labels_queue = NULL;
	asemb->insts = NULL;
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

	ft_printf("Hello12312312\n");


	asemb->fd = open(av[1], O_RDONLY);

	parse_file(asemb);

	if (asemb->insts == NULL)
		put_error(asemb, ERR_SYNTX, asemb->row + 1, 1);

	set_instructions_size(asemb, asemb->insts);
	convert_labels_to_args(asemb, asemb->insts);
	

	t_inst *cur_inst = NULL;
	t_label *cur_lab = NULL;


	// char  re;
 
	// re = 0;

	// re = re | (IND_CODE << 6);
	// printf("|%u|\n", re);

	int ffd = open("0rere", O_RDWR);
	




	printf("exec_code_size = %i\n", asemb->exec_code_size);

	file_put_numb(ffd, asemb->magic, 4);
	write(ffd, &(asemb->name), 128);
	file_put_numb(ffd, 0, 4);
	file_put_numb(ffd, asemb->exec_code_size, 4);
	write(ffd, &(asemb->comment), 2048);
	file_put_numb(ffd, 0, 4);

	file_put_exec_code(asemb->insts, ffd);
	
	printf("%i|%i\n", asemb->comment_set, asemb->name_set);
	free_asm(asemb, 0);

	


	return (1);
}