/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alexandr <Alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:56:13 by vsanta            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/10/03 19:01:04 by Alexandr         ###   ########.fr       */
=======
/*   Updated: 2019/10/29 20:12:21 by vsanta           ###   ########.fr       */
>>>>>>> ba79005be90bbab0fdc2d4e549a8a3331babac92
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "op.h"

#ifndef ASM_H
# define ASM_H

#define EMPTY_LINE 10
#define COMMENT_LINE 20
#define CMD_NAME_START 30
#define CMD_NAME_PROCCES 31
#define CMD_COMMENT_START 40
#define CMD_COMMENT_PROCCES 41
#define ONLY_INST 50
#define ONLY_LABEL 51
#define LABEL_INST 52

#define BRACKET_CHAR '"'
#define SPACE_CHARS " \t"
#define REG_CHAR 'r'
#define CMD_NUMBERS 16

typedef struct		s_pos
{
	int				lab;
	int				inst;
	int				arg_0;
	int				arg_1;
	int				arg_2;
	int				i;
	int				is_sep;
}					t_pos;

typedef struct		s_label
{
	char			*name;
	void			*inst;
}					t_label;

typedef struct		s_inst
{
	t_label			*label;
	char			*name;
	char			args_codes;
	int				arg_0;
	int				arg_1;
	int				arg_2;
	t_label			*argl_0;
	t_label			*argl_1;
	t_label			*argl_2;
	int				len;
}					t_inst;


typedef struct		s_asm
{
	int				fd;
	int				row;
	char			*parse_line;
 	unsigned int	magic;
 	char			prog_name[PROG_NAME_LENGTH + 1];
 	unsigned int	prog_size;
 	char			comment[COMMENT_LENGTH + 1];
	t_inst			inst;
}					t_asm;


typedef enum
{
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL
}	t_type;

static char				*g_type[] = {
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL"
};

// typedef enum
// {
// 	COMMAND,
// 	STRING,
// 	LABEL,
// 	OPERATOR,
// 	REGISTER,
// 	DIRECT,
// 	DIRECT_LABEL,
// 	INDIRECT,
// 	INDIRECT_LABEL,
// 	SEPARATOR,
// 	NEW_LINE,
// 	END
// }	t_type;

// static char				*g_type[] = {
// 	"COMMAND",
// 	"STRING",
// 	"LABEL",
// 	"OPERATOR",
// 	"REGISTER",
// 	"DIRECT",
// 	"DIRECT_LABEL",
// 	"INDIRECT",
// 	"INDIRECT_LABEL",
// 	"SEPARATOR",
// 	"NEW_LINE",
// 	"END"
// };

typedef struct	s_op
{
	char		*name;
	char		code;
	char		args_num;
	char		args_types_code;
	char		args_types[3];
	char		t_dir_size;
}				t_op;

static t_op		g_op[16] = {
	{"live", 1, 1, 0, {T_DIR, 0, 0}, 4},
	{"ld", 2, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4},
	{"st", 3, 2, 1, {T_REG, T_REG | T_IND, 0}, 4},
	{"add", 4, 3, 1, {T_REG, T_REG, T_REG}, 4},
	{"sub", 5, 3, 1, {T_REG, T_REG, T_REG}, 4},
	{"and", 6, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"or", 7, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"xor", 8, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 4},
	{"zjmp", 9, 1, 0, {T_DIR, 0, 0}, 2},
	{"ldi", 10, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2},
	{"sti", 11, 3, 1, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, 2},
	{"fork", 12, 1, 0, {T_DIR, 0, 0}, 2},
	{"lld", 13, 2, 1, {T_DIR | T_IND, T_REG, 0}, 4},
	{"lldi", 14, 3, 1, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 2},
	{"lfork", 15, 1, 0, {T_DIR, 0, 0}, 2},
	{"aff", 16, 1, 1, {T_REG, 0, 0}, 4}
};		


int get_line_type(char *line);
int parse_command_name(t_asm *asemb, int line_type);
int parse_command_comment(t_asm *asemb, int line_type);
int get_instruction_i_in_op(char *instruction);
int is_command(char *line, char *command);
int is_instruction(char *line);
int is_instruction_label(char *line);
int get_arg_type(char *args);
int parse_instruction(t_asm *asemb, int line_type);
int parse_file(t_asm *asemb);

int is_label_inst(char *line);
int instruction_label(char *line);


#endif
