##
## EPITECH PROJECT, 2023
## server
## File description:
## Makefile
##

CC ?=gcc
RM = rm -f

NAME = ../zappy_server

SRCS  = ./src/are_program_args_valid.c	\
		./src/signals/signal_handler.c	\
		./src/initialize_server.c	\
		./src/server_loop.c	\
		./src/commands/commands_data.c	\
		./src/commands/msz.c	\
		./src/commands/bct.c	\
		./src/commands/tna.c	\
		./src/commands/pnw.c	\
		./src/commands/ppo.c	\
		./src/commands/plv.c	\
		./src/commands/pin.c	\
		./src/commands/pex.c	\
		./src/commands/pbc.c	\
		./src/commands/pic.c	\
		./src/commands/pie.c	\
		./src/commands/pfk.c	\
		./src/commands/pdr.c	\
		./src/commands/pgt.c	\
		./src/commands/pdi.c	\
		./src/commands/enw.c	\
		./src/commands/ebo.c	\
		./src/commands/edi.c	\
		./src/commands/sgt.c	\
		./src/commands/sst.c	\
		./src/commands/seg.c	\
		./src/commands/smg.c	\
		./src/commands/suc.c	\
		./src/commands/sbp.c	\
		./lib/debug/debug_word_array.c	\
		./lib/regex/regex_match.c	\
		./lib/free_word_array.c	\
		./lib/get_size_word_array.c	\
		./lib/open_file.c	\
		./lib/read_file_contents.c	\
		./lib/return_error.c	\
		./lib/split_str.c	\
		./lib/timestamp.c	\
		./lib/my_strcat.c	\
		./main.c	\


OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -Wall -Wextra -I ./include -g3
LDFLAGS += -luuid

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

# tests_run:
# 	make -C ./tests all

.PHONY: all clean fclean re tests_run
