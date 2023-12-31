##
## EPITECH PROJECT, 2023
## server
## File description:
## Makefile
##

CC ?=gcc
RM = rm -f

NAME = ../zappy_server

SRCS  =	$(shell find . -type f -name "*.c")

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS +=  -lm -Wall -Wextra -I ./include -g3

# ! Add color to output
COLOR_RESET   = \033[0m
COLOR_PENDING = \033[01;33m
COLOR_SUCCESS = \033[01;32m
COLOR_DEFAULT = \033[01;36m
COLOR_CYAN    = \033[0;36m
GREEN         = \033[0;32m
COLOR_BLUE    = \033[0;34m
COLOR_YELLOW  = \033[0;33m


all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(COLOR_CYAN)server $(COLOR_YELLOW)➜  $(COLOR_PENDING)Linking...\
	$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)
	@printf "$(COLOR_CYAN)server $(COLOR_BLUE)➜  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

-include $(DEPS)

%.o: %.c
	@printf "$(COLOR_CYAN)server $(COLOR_BLUE)➜  $(GREEN)「✔」 $(COLOR_DEFAULT)\
	Compiling $<...$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	@printf "$(COLOR_CYAN)server $(COLOR_YELLOW)➜  $(COLOR_PENDING)Cleaning...\
	$(COLOR_RESET)\n"
	@$(RM) $(OBJS)
	@$(RM) $(DEPS)
	@make -C ./tests fclean
	@printf "$(COLOR_CYAN)server \033[0;32m➜  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

fclean: clean
	@printf "$(COLOR_CYAN)server $(COLOR_YELLOW)➜  $(COLOR_PENDING)\
	Full cleaning...$(COLOR_RESET)\n"
	@$(RM) $(NAME)
	@$(RM) $(wildcard vgcore*)
	@printf "$(COLOR_CYAN)server \033[0;32m➜  $(COLOR_SUCCESS)Done.\
	$(COLOR_RESET)\n"

re: fclean all

.PHONY: all clean fclean re
