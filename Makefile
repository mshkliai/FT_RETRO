# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 12:35:39 by mshkliai          #+#    #+#              #
#    Updated: 2018/10/06 12:35:41 by mshkliai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_retro

CLASS = Batya.cpp Game.cpp Ship.cpp Boss.cpp

SRC = ncurse_menu.cpp main.cpp

S_CLASS = $(addprefix ./Classes/, $(CLASS))

S_SRC = $(addprefix ./Sources/, $(SRC))

OBJ = $(S_SRC:.cpp=.o) $(S_CLASS:.cpp=.o)

FLAGS = -Wall -Wextra -Werror

END = \033[0m

GREEN = \033[0;32m

RED = \033[0;31m

ARR = \033[1;34m

YELLOW = \033[1;33m

all: $(NAME)

$(NAME): $(OBJ)
	@clang++ $(FLAGS) $(OBJ) -lncurses -o $@ && \
	echo "\n$(YELLOW)FT_RETRO compiled, good luck!$(END)"

$(OBJ): %.o: %.cpp
	@clang++ $(FLAGS) -c $< -o $@ && \
	echo "$(GREEN)$<$(ARR) -> $(RED)$@$(END)$(END)$(END)"

clean:
	@rm -f $(OBJ) && echo "\033[0;35mobjective files removed$(END)"

fclean: clean
	@rm -f $(NAME) && echo "\033[1;31mFT_RETRO deleted$(END)"

re: fclean all

.PHONY: all clean fclean all
