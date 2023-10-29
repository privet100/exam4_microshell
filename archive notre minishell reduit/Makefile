NAME	= microshell

SRC_DIR	= srcs/

OBJ_DIR	= objs/

FILES	=	1_prompt.c \
			2_executor.c \
			utils.c

SRCS	= $(addprefix $(SRC_DIR), $(FILES))

OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

FLAGS	= -Wall -Wextra -Werror -g3

LIB		= -lreadline

INCL	= -I .


objs/%.o : ./srcs/%.c
	mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(INCL) -c $< -o $@

all:		$(NAME)
	clear

$(NAME):	$(OBJS)
	cc $(OBJS) $(LIB)

clean:
	rm -rf ${OBJ_DIR}

fclean: 	clean
	rm -rf $(NAME)

re: fclean all

.PHONY : 	all clean fclean re
