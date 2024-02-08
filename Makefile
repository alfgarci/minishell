# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 11:01:44 by a8                #+#    #+#              #
#    Updated: 2024/02/08 16:00:32 by alfgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=\033[1;31m
GREEN	=\033[1;32m
YELLOW	=\033[1;33m
NC		=\033[0m

#---minishell---------------------------
NAME 	=	minishell
	#---SRC
SRC_DIR	=	src
SRC 	=	${SRC_DIR}/setup/init_envp.c \
			${SRC_DIR}/setup/init_instance.c \
			${SRC_DIR}/utils/arr_utils.c\
			${SRC_DIR}/utils/other_utils.c\
			${SRC_DIR}/utils/str_utils.c \
			${SRC_DIR}/clear_prompt/clean_prompt.c\
			${SRC_DIR}/clear_prompt/quotes_closed.c\
			${SRC_DIR}/clear_prompt/split_prompt.c\
			${SRC_DIR}/clear_prompt/expander/expander_utils.c\
			${SRC_DIR}/clear_prompt/expander/expander.c\
			${SRC_DIR}/minishell.c \
			${SRC_DIR}/clear_prompt/tokenizer.c \
			${SRC_DIR}/clear_prompt/tokenizer_utils.c \
			${SRC_DIR}/utils/errors/error.c \
			${SRC_DIR}/utils/errors/parse_error.c \
			${SRC_DIR}/parse_cmd/command_utils.c \
			${SRC_DIR}/parse_cmd/parse_cmd.c \
			${SRC_DIR}/parse_cmd/parse_redirections.c \
			${SRC_DIR}/parse_cmd/parse_utils.c \
			${SRC_DIR}/parse_cmd/erase_quotes.c \
			${SRC_DIR}/executor/pipe_utils.c\
			${SRC_DIR}/executor/cmd.c\
			${SRC_DIR}/executor/executor.c\
			${SRC_DIR}/executor/heredoc.c\
			${SRC_DIR}/executor/redirections.c\
			${SRC_DIR}/executor/heredoc_utils.c\
			${SRC_DIR}/utils/free_utils.c\
			${SRC_DIR}/builtin/builtin.c\
			${SRC_DIR}/builtin/cd.c\
			${SRC_DIR}/builtin/env.c\
			${SRC_DIR}/builtin/unset.c\
			${SRC_DIR}/builtin/export.c\
			${SRC_DIR}/builtin/pwd.c\
			${SRC_DIR}/builtin/echo.c\
			${SRC_DIR}/builtin/exit.c\
			${SRC_DIR}/signals/signals.c\

	#---OBJ
OBJ 	=	${SRC:.c=.o}
	#---INC
INC 	=	includes


#---LIBFT-------------------------------
LIBFT_DIR	=	libft
LIBFT_NAME	=	ft

#---READLINE-------------------------------
RL_INC	=	${shell brew --prefix readline}/include
RL_LIB	=	${shell brew --prefix readline}/lib

	#---INC
LIBFT_INC	= ${LIBFT_DIR}/includes

CC			=	cc
C_FLAGS		=	-Werror -Wextra -Wall
RL_FLAGS	=	-lreadline
LIB_FLAGS	=	-L${LIBFT_DIR} -l${LIBFT_NAME} -L${RL_LIB}
H_FLAGS		=	-I${INC} -I${LIBFT_INC} -I${RL_INC}
FLAGS		=	${C_FLAGS} ${LIB_FLAGS} ${RL_FLAGS}

#---RECIPES------------------------------
%.o : %.c
	@${CC} ${H_FLAGS} ${C_FLAGS} -c $< -o $@

all:	${NAME}

${NAME}: ${OBJ}
		@echo "${RED}Compiling Libft...${NC}"
		@make -s -C ${LIBFT_DIR}
		@echo "${RED}Compiling minishell...${NC}"
		@${CC} ${FLAGS} ${OBJ} -o ${NAME}
		@echo "${GREEN}${NAME} READY!${NC}"

clean:
		@make clean -s -C ${LIBFT_DIR}
		@rm -f ${OBJ}
		@echo "${YELLOW}OBJS REMOVED!${NC}"

fclean:		clean
		@make fclean -s -C ${LIBFT_DIR}
		@rm -f ${NAME}
		@echo "${YELLOW}${NAME} REMOVED!${NC}"

re:		fclean all

.PHONY:	all clean fclean re
