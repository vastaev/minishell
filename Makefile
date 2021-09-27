# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 12:26:24 by uterese           #+#    #+#              #
#    Updated: 2021/09/27 17:38:50 by nephilister      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		=	/bin/bash

NAME = minishell

S = sources/
L = libfun/
B = built-in/
E = export/
C = cd/
I =	includes/
O = objects/

CC = gcc

USER = $(shell whoami)
COMP = $(CC) $(CFLAGS) $(SRC) $(HEADER) $(LIBS) -o $(NAME)
COMPO = $(CC) $(CFLAGS) -c $< $(HEADER) -o $@
OS = $(shell uname)

LIBS = -lreadline

ifeq ($(OS), Darwin)
 	# LIBS = -lreadline -L/opt/homebrew/opt/readline/lib
	LIBS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
	COMP = $(CC) $(CFLAGS) $(SRC) $(HEADER) $(RDLH) $(LIBS) -o $(NAME)
	COMPO = $(CC) $(CFLAGS) -c $< $(HEADER) $(RDLH) -o $@
endif

SRC =  $Smain.c $Sshell.c $S$Lfunctions.c $S$Lfunctions2.c $Spp.c \
		$Sparser.c $Spars_utils.c $Slist_utils.c $Serrors.c $Sfrees.c \
		$Sget_next_line.c $Senv_utils.c $S$Lfunctions3.c $S$Lfunctions4.c \
		$Slexer.c $Slex_utils.c $Slex_states.c $Slex_expand.c \
		$Sinitialization.c $S$B$Eexport_utils.c $S$Benv.c $S$B$Eexport.c \
		$S$Lfuncs.c $S$Becho.c $S$Bpwd.c $Serror_management.c $S$Lfuncs2.c \
		$S$B$Eexport_make_list.c $Sbin.c $Sexec.c $Sredir.c $S$Bexit.c \
		$S$Bunset.c $S$B$Ccd.c $S$B$Ccd_utils.c

OBJS = $(SRC:$S%.c=$O%.o)

RED			=	\033[1;31m
GRN			=	\033[1;32m
NOCOL		=	\033[0m

HEADER	=	-I $I 

RDLH = -I /Users/$(USER)/.brew/opt/readline/include
# RDLH = -I /opt/homebrew/opt/readline/include

FLAGS		=	-Wall -Wextra -Werror

start:
	@[ -f "minishell" ] || echo -e -n "$(GRN)[Compiling]: ["
	@make -s all

all:			$(NAME)

$(NAME):		$(OBJS)
	@echo -e "$(GRN)]100% ==> Success!$(NOCOL)"
	@$(COMP)

$O%.o: 			$S%.c
	@[ -d $(O) ] || mkdir -p $(O)
	@[ -d $(O)$(L) ] || mkdir -p $(O)$(L)
	@[ -d $(O)$(B) ] || mkdir -p $(O)$(B)
	@[ -d $(O)$(B)$(E) ] || mkdir -p $(O)$(B)$(E)
	@[ -d $(O)$(B)$(C) ] || mkdir -p $(O)$(B)$(C)
	@echo -e -n "$(GRN)#$(NOCOL)"
	@$(COMPO)

clean:
	@rm -rf $(O)
	@echo -e "$(RED)Delete obj files!"

fclean:			clean
	@echo -e "$(RED)Delete $(NAME)!"
	@rm -f $(NAME)
	@find . -name ".DS_Store" -delete

re:				fclean start all

.PHONY:			all clean fclean re 