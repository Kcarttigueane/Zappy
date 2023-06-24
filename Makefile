##
## EPITECH PROJECT, 2022
## B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
## File description:
## Makefile
##

SERVER	=	server/
AI =	ai/
GUI =	gui/

COLOR_RESET   = \033[0m
COLOR_TITLE   = \033[01;31m

all: server

server:
	@printf "$(COLOR_TITLE)[COMPILING SERVER...]$(COLOR_RESET)\n"
	@make -C $(SERVER) -s

ai:
	@printf "$(COLOR_TITLE)[COMPILING AI...]$(COLOR_RESET)\n"
	@make -C $(AI) -s

gui:
	@printf "$(COLOR_TITLE)[COMPILING GUI...]$(COLOR_RESET)\n"
	@make -C $(GUI) -s

clean:
	@printf "$(COLOR_TITLE)[CLEANING FCLEAN SERVER-AI-GUI...]$(COLOR_RESET)\n"
	@make clean -C $(SERVER) -s
	@make clean -C $(AI) -s
	@make clean -C $(GUI) -s

fclean:
	@printf "$(COLOR_TITLE)[FCLEAN SERVER-AI-GUI...]$(COLOR_RESET)\n"
	@make fclean -C $(SERVER) -s
	@make fclean -C $(AI) -s
	@make fclean -C $(GUI) -s

re:
	@printf "$(COLOR_TITLE)[RE SERVER...]$(COLOR_RESET)\n"
	@make re -C $(SERVER) -s
	@printf "$(COLOR_TITLE)[RE AI...]$(COLOR_RESET)\n"
	@make re -C $(AI) -s
	@printf "$(COLOR_TITLE)[RE GUI...]$(COLOR_RESET)\n"
	@make re -C $(GUI) -s

.PHONY: all server ai clean fclean re
