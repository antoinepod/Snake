##
## EPITECH PROJECT, 2022
## Snake
## File description:
## Makefile
##

SRC =	src/Main.cpp	\
		src/Snake.cpp	\
		src/GameStatus/Menu.cpp	\
		src/GameStatus/Game.cpp	\
		src/GameStatus/End.cpp	\

W_FLAGS	=	-W -Wall -Wextra

SFML	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

INCLUDE	=

CPPFLAGS	=	$(INCLUDE) $(SFML) $(W_FLAGS)

OBJ	=	$(SRC:.cpp=.o)

NAME	=	snake

all:	$(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(INCLUDE) $(SFML) $(W_FLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.o
	rm -f *~
	rm -f *#

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:	CPPFLAGS += -g
debug:	all

.PHONY: all clean fclean re debug