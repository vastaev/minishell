
NAME = minishell

S = sources/
L = libfun/
I =	includes/

O = objects/

SRC =  $Smain.c $Sshell.c $S$Lfunctions.c $S$Lfunctions2.c $Spp.c \
		$Sparser.c $Spars_utils.c $Slist_utils.c $Serrors.c $Sfrees.c \
		$Sget_next_line.c $Senv_utils.c $S$Lfunctions3.c $S$Lfunctions4.c
OBJS = $(SRCS:$S%.c=$O%.o)

RED			=	\033[1;31m
GRN			=	\033[1;32m
NOCOL		=	\033[0m

HEADER	=	-I $I 

RDLH = -I /Users/uterese/.brew/opt/readline/include

LIBS	= -lreadline  -L/Users/uterese/.brew/opt/readline/lib

FLAGS		=	-Wall -Wextra -Werror

start:
	@[ -f "minishell" ] || echo -e -n "$(GRN)[Compiling]: ["
	@make -s all

all:			$(NAME)

$(NAME):		$(OBJS)
	@echo -e "$(GRN)]100% ==> Success!$(NOCOL)"
	@gcc $(CFLAGS) $(SRC) $(HEADER) $(RDLH) $(LIBS) -o $(NAME)

$O%.o: 			$S%.c
	@[ -d $(O) ] || mkdir -p $(O)
	@[ -d $(O)$(L) ] || mkdir -p $(O)$(L)
	@echo -e -n "$(GRN)#$(NOCOL)"
	@gcc $(CFLAGS) -c $< $(HEADER) $(RDLH) -o $@

clean:
	@rm -rf $(O)
	@echo -e "$(RED)Delete obj files!"

fclean:			clean
	@echo -e "$(RED)Delete $(NAME)!"
	@rm -f $(NAME)
	@find . -name ".DS_Store" -delete

re:				fclean start all

.PHONY:			all clean fclean re 