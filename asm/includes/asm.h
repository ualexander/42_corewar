/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:56:13 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/06 16:37:12 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "corewar.h"
# include <limits.h>

#ifndef ASM_H
# define ASM_H

# define A_REG_SIZE 1
# define A_ARGS_SIZE 1

# define LABEL(L) ((t_label*)(L->data))
# define INST(L) ((t_inst*)(L->data))

#define EMPTY_LINE 10
#define COMMENT_LINE 20
#define CMD_NAME_START 30
#define CMD_NAME_PROCCES 31
#define CMD_COMMENT_START 40
#define CMD_COMMENT_PROCCES 41
#define IS_LABEL 50
#define IS_INSTRUCTION 60

#define COMMENT_CHAR_ALT		';'
#define BRACKET_CHAR '"'
#define SPACE_CHARS " \t"
#define REG_CHAR 'r'
#define CMD_NUMBERS 16


typedef struct		s_args
{
	int				arg;
	char			*larg;
	int				bit_move;
}					t_args;

typedef struct		s_inst
{
	t_op			*op;
	t_args			args[3];
	unsigned char	args_codes;
	unsigned int	bit_size;
	unsigned int	bit_pos;
	unsigned int	row;
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
	char			*parse_line;
	unsigned int	row;
 	unsigned int	magic;
	unsigned int	prog_size;
 	char			prog_name[PROG_NAME_LENGTH + 1];
 	char			comment[COMMENT_LENGTH + 1];
	t_lst			*labels;
	t_lst			*labels_queue;
	t_lst			*insts;
}					t_asm;


/*

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

static char				*g_type[] = {
	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};
*/

	

int put_error(t_asm *asemb);

int is_command(char *line, char *command);
int is_label(char *line);
int is_instruclion(char *line);
int is_comment_char(char c);
int get_line_type(char *line);

int parse_command_name(t_asm *asemb, int line_type);
int parse_command_comment(t_asm *asemb, int line_type);

int get_instruction_i_in_op(char *instruction);
int get_arg_type(char *args);
char	*set_val_numb(t_asm *asemb, int *set_numb, char *line);
char	*set_val_str(t_asm *asemb, char **set_str, char *line);
unsigned char modif_arg_codes(unsigned char last_codes,
	int arg_type, int bit_move);

int parse_instruction(t_asm *asemb, char *line);
int parse_label(t_asm *asemb, char *line);
int parse_file(t_asm *asemb);

int skip_space(char **line);
int skip_space_and_sep(char **line);

#endif
