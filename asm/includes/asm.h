/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:56:13 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/05 16:38:32 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "corewar.h"

#ifndef ASM_H
# define ASM_H

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
	int				bite_move;
}					t_args;

typedef struct		s_inst
{
	char			*line;
	t_op			*op;
	t_args			args[3];
	unsigned char	args_codes;
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
	char			*parse_line;
	int				row;
 	unsigned int	magic;
	unsigned int	prog_size;
 	char			prog_name[PROG_NAME_LENGTH + 1];
 	char			comment[COMMENT_LENGTH + 1];
	t_lst			*labels;
	t_lst			*insts;
	t_lst			*labels_queue;
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

	

int get_line_type(char *line);
int parse_command_name(t_asm *asemb, int line_type);
int parse_command_comment(t_asm *asemb, int line_type);
int get_instruction_i_in_op(char *instruction);
int is_command(char *line, char *command);
int is_instruction(char *line);
int is_instruction_label(char *line);
int get_arg_type(char *args);
int parse_file(t_asm *asemb);


int parse_instruction(t_asm *asemb, char *line);
int parse_label(t_asm *asemb, char *line);

int put_error(t_asm *asemb);

int is_instruclion(char *line);
int is_comment_char(char c);


#endif
