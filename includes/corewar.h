/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:34:02 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/27 18:46:00 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "op.h"

#define REG_CODE					1
#define DIR_CODE					2
#define IND_CODE					3

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
