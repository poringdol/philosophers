SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
FLAGS = -Wall -Werror -Wextra -pthread -g
RM = rm -rf

NAME = philo_two

SRC = main.c \
	  libft.c \
	  check.c  \
	  init.c \
	  print.c \
	  philosophers.c

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo "$(GREEN)  Executable $(PURPLE)philo_two $(GREEN)created  $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -MMD -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"


clean:
	$(RM) $(OBJDIR) $(NAME)

fclean:
	$(RM) $(OBJDIR) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re