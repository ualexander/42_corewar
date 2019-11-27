/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:56:13 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/27 18:46:14 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include "corewar.h"
# include <limits.h>

# define INPUT_FILE_EXT ".s"
# define OUTPUT_FILE_EXT ".cor"

# define EMPTY_LINE 10
# define COMMENT_LINE 20
# define CMD_NAME_START 30
# define CMD_NAME_PROCCES 31
# define CMD_COMMENT_START 40
# define CMD_COMMENT_PROCCES 41
# define IS_LABEL 50
# define IS_INSTRUCTION 60

# define IS_NEW_LINE 1
# define MAX_REG 99

# define ERR_LEX 1
# define ERR_LEX_NL 2
# define ERR_SYNTX 3
# define ERR_INVALID_PARAM 4
# define ERR_LONG_NAME 5
# define ERR_LONG_COM 6
# define ERR_NUMB_ARG 7
# define ERR_READ_FILE 8
# define ERR_FILE_NAME 9
# define ERR_CREATE_FILE 10

# define A_REG_SIZE 1
# define A_ARGS_SIZE 1
# define A_IND_SIZE 2

# define COMMENT_CHAR_ALT ';'
# define BRACKET_CHAR '"'
# define SPACE_CHARS " \t"
# define REG_CHAR 'r'
# define CMD_NUMBERS 16

# define LABEL(L) ((t_label*)(L->data))
# define INST(I) ((t_inst*)(I->data))

typedef struct		s_arg
{
	int				arg;
	char			*larg;
	int				size;
	int				bit_move;
}					t_arg;

typedef struct		s_inst
{
	t_op			*op;
	t_arg			args[3];
	unsigned char	args_codes;
	unsigned int	bit_size;
	unsigned int	bit_pos;
	int				row;
}					t_inst;

typedef struct		s_label
{
	char			*name;
	t_inst			*inst;
}					t_label;

typedef struct		s_asm
{
	int				fd;
	int				gnl;
	char			*file_name;
	char			*parse_line;
	unsigned int	row;
	unsigned int	magic;
	unsigned int	exec_code_size;
	char			name[PROG_NAME_LENGTH + 1];
	int				name_set;
	char			comment[COMMENT_LENGTH + 1];
	int				comment_set;
	t_lst			*labels;
	t_lst			*labels_queue;
	t_lst			*insts;
}					t_asm;

void				put_error(t_asm *asemb, int err_n, int row, int col);
void				put_error_inst(t_asm *asemb, int row,
						int arg_i, char *op_name);
void				put_error_label(t_asm *asemb, int row, char *label);
void				put_error_file(t_asm *asemb, int err_n, char *file_name);

void				open_input_file(t_asm *asemb, int ac, char **av);

int					is_command(char *line, char *command);
int					is_label(char *line);
int					is_instruclion(char *line);
int					is_comment_char(char c);
int					get_line_type(t_asm *asemb, char *line);

int					free_asemb(t_asm *asemb, int ret);

void				write_output_file(t_asm *asemb, char *ext);

int					parse_command_name(t_asm *asemb, int line_type);
int					parse_command_comment(t_asm *asemb, int line_type);

int					get_instruction_i_in_op(char *instruction);
int					get_arg_type(char *args);
char				*set_val_numb(t_asm *asemb, int *set_numb, char *line);
char				*set_val_str(t_asm *asemb, char **set_str, char *line);
unsigned char		modif_arg_codes(unsigned char last_codes,
						int arg_type, int bit_move);

int					parse_instruction(t_asm *asemb, char *line);

void				connect_with_labels(t_asm *asemb, t_inst *inst);

int					parse_label(t_asm *asemb, char *line);

void				parse_file(t_asm *asemb);

void				convert_labels_to_args(t_asm *asemb, t_lst *inst);
void				set_instructions_size(t_asm *asemb, t_lst *inst);

int					skip_space(char **line);
int					skip_space_and_sep(char **line);

#endif
