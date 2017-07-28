##
## Makefile for shootandrun in /home/melot_g/rendu/cpp_va
## 
## Made by gautier melot
## Login   <melot_g@epitech.net>
## 
## Started on  Mon Jul 21 10:46:39 2014 gautier melot
## Last update Thu Jul 24 11:06:46 2014 gautier melot
##

CC=		g++

RM=		rm -f

GFLAGS=		-ldl

CPPFLAGS=	-W -Wall -Werror -Wextra -Iinclude

NAME=		VanguardArmy

SRC=		src/main.cpp
SRC +=		src/Cell.cpp
SRC +=		src/CellFactory.cpp
SRC +=		src/Unit.cpp
SRC +=		src/UnitFactory.cpp
SRC +=		src/Cursor.cpp

OBJ=		$(SRC:.cpp=.o)

all:		$(NAME)
		$(MAKE) -C Sdl

$(NAME):	$(OBJ)
		$(CC) $(GFLAGS) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)
		$(MAKE) clean -C Sdl

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)
		$(MAKE) fclean -C Sdl

re:		fclean all
		$(MAKE) re -C Sdl

.PHONY:		all clean fclean re
