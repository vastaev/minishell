SHELL		=	/bin/bash

NAME = minishell

S = sources/
L = libfun/
I =	includes/
O = objects/

CC = gcc

USER = $(shell whoami)
COMP = $(CC) $(FLAGS) $(SRC) $(HEADER) $(LIBS) -o $(NAME)
COMPO = $(CC) $(FLAGS) -c $< $(HEADER) -o $@
OS = $(shell uname)

LIBS = -lreadline

ifeq ($(OS), Darwin)
	LIBS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
	COMP = $(CC) $(FLAGS) $(SRC) $(HEADER) $(RDLH) $(LIBS) -o $(NAME)
	COMPO = $(CC) $(FLAGS) -c $< $(HEADER) $(RDLH) -o $@
endif

SRC =  $Smain.c $Sshell.c $S$Lfunctions.c $S$Lfunctions2.c $Spp.c \
		$Sparser.c $Spars_utils.c $Slist_utils.c $Serrors.c $Sfrees.c \
		$Sget_next_line.c $Senv_utils.c $S$Lfunctions3.c $S$Lfunctions4.c \
		$Slexer.c $Slex_utils.c $Slex_states.c $Slex_expand.c

OBJS = $(SRC:$S%.c=$O%.o)

RED			=	\033[1;31m
GRN			=	\033[1;32m
NOCOL		=	\033[0m

HEADER	=	-I $I 

RDLH = -I /Users/$(USER)/.brew/opt/readline/include

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