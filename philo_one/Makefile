SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
FLAGS = -Wall -Werror -Wextra -pthread -g
RM = rm -rf

NAME = philo_one

SRC = main.c \
	  libft.c \
	  check.c  \
	  init.c \
	  free.c  \
	  print.c  \
	  philosophers.c

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo "$(GREEN)  Executable $(PURPLE)philo_one $(GREEN)created  $(B&W)"

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"


clean:
	$(RM) $(OBJDIR) $(NAME)

fclean:
	$(RM) $(OBJDIR) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re