# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 11:57:39 by atamer            #+#    #+#              #
#    Updated: 2025/05/05 16:32:22 by mguerri-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			 = cc
CFLAGS		 = -Wall -Wextra -Werror
RL			 = -lreadline
NAME		 =	minishell
SRC_DIR     := ./
SRCS        :=  main.c \
				$(addprefix src/, \
				\
				parsing/data_prepare.c \
				parsing/lexer.c \
				parsing/parser.c \
				parsing/quotes_helper.c \
				parsing/quotes.c \
				parsing/stringbuilding.c \
				parsing/tokens.c \
				parsing/word.c \
				\
				utils/free.c \
				utils/ft_split.c \
				utils/ft_strtrim.c \
				utils/is_it.c \
				utils/len.c \
				utils/list.c \
				utils/numbers.c \
				utils/string_parse.c \
				utils/strings.c \
				\
				execution/assign.c \
				execution/build_in.c \
				execution/command.c \
				execution/heredoc.c \
				execution/heredoc_utils.c \
				execution/lone.c \
				execution/path.c \
				execution/pipes.c \
				execution/redirect.c \
				execution/output.c \
				execution/wait.c \
				\
				signals/signals.c \
				\
				build_ins/env.c \
				build_ins/exit.c \
				build_ins/export.c \
				build_ins/export_utils.c \
				build_ins/unset.c \
				build_ins/echo.c \
				build_ins/cd_utils.c \
				build_ins/cd.c \
				build_ins/pwd.c \
				\
				error_managing/error.c \
				)

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
BUILD_DIR   := .obj
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)
DIR_DUP      = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ ${RL}

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all
