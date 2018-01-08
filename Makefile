# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/09 01:59:12 by ede-sous          #+#    #+#              #
#    Updated: 2017/09/29 03:05:28 by ede-sous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_select
GCC_FLAGS	= gcc -Wall -Werror -Wextra -Weverything -g -ltermcap
LIB			= ./Libft/libft.a
INCLUDES	= -I./includes

SRCS_DIR	= ./sources/
SRCS_BEG	= beginning/ft_error.c beginning/main_select.c \
			  beginning/mor_terminal.c beginning/print_intro.c \
			  beginning/start_selecting.c
SRCS_LIST	= list_work/list_work_1.c list_work/print_list.c \
			  list_work/stock_list.c list_work/ft_dellist.c
SRCS_KEY	= key_work/go_arrows.c key_work/go_selectwork.c key_work/go_move.c \
			  key_work/go_delete_or_insert.c key_work/go_inverse.c
SRCS_PAD	= padding/define_padding.c
SRCS_SIGNAL	= signals/handler.c signals/ft_sounds.c
SRCS_FILES	= $(SRCS_BEG) $(SRCS_LIST) $(SRCS_KEY) $(SRCS_PAD) $(SRCS_SIGNAL)

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		= $(SRCS:.c=.o)

all : lib $(NAME) logo

lib :
	@make -C ./Libft/

$(NAME): $(OBJS)
	@$(GCC_FLAGS) -o $(NAME) $(OBJS) $(INCLUDES) -L./Libft/ -lft
	@echo "        \033[42m $(NAME) claiming for PoWa !\033[0m"

%.o : %.c
	@gcc -c -o $@ $< $(INCLUDES)

clean :
	@make -C ./Libft/ clean
	@rm -rf $(OBJS)
	@echo "            \033[92m Mission completed."
	@echo "            All Objects are dead.\033[0m"

fclean : clean
	@make -C ./Libft/ fclean
	@rm -rf $(NAME)
	@echo " \033[95m Ups... My fluffy weapon killed $(NAME) :x\033[0m"

logo:
	@sh .scripts/professor.sh

re: fclean all
