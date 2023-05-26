##
## EPITECH PROJECT, 2022
## B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
## File description:
## Makefile
##

SERVER	=	server/

COLOR_RESET   = \033[0m
COLOR_TITLE   = \033[01;31m

all: server

server:
	@printf "$(COLOR_TITLE)[COMPILING SERVER...]$(COLOR_RESET)\n"
	@make -C $(SERVER) -s

clean:
	@printf "$(COLOR_TITLE)[CLEANING SERVER...]$(COLOR_RESET)\n"
	@make clean -C $(SERVER) -s

fclean:
	@printf "$(COLOR_TITLE)[FCLEAN SERVER...]$(COLOR_RESET)\n"
	@make fclean -C $(SERVER) -s

re:
	@printf "$(COLOR_TITLE)[RE SERVER...]$(COLOR_RESET)\n"
	@make re -C $(SERVER) -s

.PHONY: all server clean fclean re
