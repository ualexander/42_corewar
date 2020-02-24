# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 18:48:40 by vsanta            #+#    #+#              #
#    Updated: 2019/12/01 15:29:57 by vsanta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= asm

NAME_LIB 			= libft/libft.a
NAME_PRINTF 		= printf/libftprintf.a

HEADER_NAME_MAIN	= corewar.h
HEADER_NAME_OP		= op.h
HEADER_NAME_ASM		= asm.h

INC_DIR_MIAN 		= ../includes/
INC_DIR_ASM 		= ./includes/
INC_DIR_LIB_FT 		= ./libft/includes/
INC_DIR_PRINTF 		= ./printf/includes/

SRC_DIR 			= ./src/
OBJ_DIR 			= ./obj/

SRC_NAME			= error.c main.c parse_command.c parse_label.c \
					input.c output.c parse_instruction.c process_instrructions.c \
					line_type.c parse.c parse_instruction_utils.c skip.c

HEADER_MAIN 		= $(addprefix $(INC_DIR_MIAN), $(HEADER_NAME_MAIN))
HEADER_OP 			= $(addprefix $(INC_DIR_MIAN), $(HEADER_NAME_OP))
HEADER_ASM 			= $(addprefix $(INC_DIR_ASM), $(HEADER_NAME_ASM))

SRC					= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ					= $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

CC					= gcc
FLAGS				= -Wall -Wextra -Werror
GCC_LIBFT 			= -L ./libft -l ft
GCC_PRINTF 			= -L ./printf -l ftprintf
GCC_INCLUDES		= -I $(INC_DIR_MIAN) -I $(INC_DIR_ASM) -I $(INC_DIR_LIB_FT) -I $(INC_DIR_PRINTF)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(NAME_LIB) $(NAME_PRINTF)
	$(CC) $(GCC_LIBFT) $(GCC_PRINTF) $(GCC_INCLUDES) $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p obj

$(NAME_LIB):
	@make -C libft/

$(NAME_PRINTF):
	@make -C printf/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_MAIN) $(HEADER_OP) $(HEADER_ASM)
	$(CC) -c $(GCC_INCLUDES) $(FLAGS) $< -o $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C libft/
	@make clean -C printf/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/
	@make fclean -C printf/

re: fclean all
