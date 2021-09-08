
NAME = minishell

S = sources/
L = libfun/
I =	includes/

O = objects/

SRC =  $Smain.c $Sshell.c $S$Lfunction.c $S$Lfunction2.c

OBJS = $(SRCS:$S%.c=$O%.o)

RED			=	\033[1;31m
GRN			=	\033[1;32m
NOCOL		=	\033[0m

HEADER	=	-I $I

LIBS	=	-lreadline

FLAGS		=	-Wall -Wextra -Werror

start:
	@[ -f "minishell" ] || echo -e -n "$(GRN)[Compiling]: ["
	@make -s all

all:			$(NAME)

$(NAME):		$(OBJS)
	@echo -e "$(GRN)]100% ==> Success!$(NOCOL)"
	@gcc $(CFLAGS) $(SRC) $(HEADER) $(LIBS) -o $(NAME)

$O%.o: 			$S%.c
	@[ -d $(O) ] || mkdir -p $(O)
	@[ -d $(O)$(L) ] || mkdir -p $(O)$(L)
	@echo -e -n "$(GRN)#$(NOCOL)"
	@gcc $(CFLAGS) -c $< $(HEADER) -o $@

clean:
	@rm -rf $(O)
	@echo -e "$(RED)Delete obj files!"

fclean:			clean
	@echo -e "$(RED)Delete $(NAME)!"
	@rm -f $(NAME)
	@find . -name ".DS_Store" -delete

re:				fclean start all

.PHONY:			all clean fclean re 