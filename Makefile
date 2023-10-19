# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 09:48:54 by afatir            #+#    #+#              #
#    Updated: 2023/10/19 11:24:39 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CFLAGS	=  -Wall -Werror -Wextra 
CC		= cc

LIB_FT	= ./libft_gcl_ptf/
LIB_FT_A= ./libft_gcl_ptf/libft_gcl_ptf.a

MOBJS	= ${SRCS:%.c=%.o}
SRCS	=	parsing/main.c \
			parsing/parsing.c \
			parsing/separators.c \
			parsing/quotes.c \
			parsing/check_syntax.c \
			parsing/expanding.c \
			parsing/expanding2.c \
			parsing/signals.c \
			parsing/utils.c \
			parsing/linked_list.c \
			 \
			parsing/builtins/env.c \
			parsing/builtins/reset_env.c\
			parsing/builtins/export.c \
			parsing/builtins/export2.c \
			parsing/builtins/unset.c \
			 \
			execution/builtins/echo_function.c \
			execution/builtins/pwd_function.c \
			execution/builtins/cd_function.c \
			execution/builtins/exit_function.c \
			execution/builtins/exit_function_utils.c \
			 \
			execution/execution.c \
			execution/executin_multiple_pipes.c \
			execution/executin_m_p_utils.c \
			execution/executin_m_p_util2.c \
			execution/executin_m_p_utils3.c \
			execution/executin_m_p_utils4.c \
			execution/executin_m_p_utils5.c \
			execution/executin_m_p_utils6.c \
			execution/executin_m_p_utils7.c \
			execution/executin_m_p_utils8.c

all : $(NAME)

$(NAME) : $(MOBJS)
	@make -C $(LIB_FT)
	@$(CC) $(CFLAGS) -lreadline  ${LDFLAGS} $(LIB_FT_A) $(MOBJS) -o $(NAME)
# @make clean

%.o: %.c minishell.h
	$(CC) ${CPPFLAGS} $(CFLAGS)  -c  $< -o $@
clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS) 

fclean:	clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)

re:	fclean all