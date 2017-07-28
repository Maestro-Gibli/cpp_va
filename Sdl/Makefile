##
## Makefile for shootandrun in /home/melot_g/rendu/cpp_va/Sdl
## 
## Made by gautier melot
## Login   <melot_g@epitech.net>
## 
## Started on  Mon Jul 21 18:02:18 2014 gautier melot
## Last update Thu Jul 24 16:02:22 2014 gautier melot
##

CC=		g++

RM=		rm -f

GFLAGS=		-fPIC -shared

SFLAGS=		-lSDL -lSDLmain -lSDL_image -lSDL_ttf /usr/include/fmod/lib/libfmodex64.so
SFLAGS +=	$(GFLAGS)

CPPFLAGS=	-I../include -Iresources/fmod/inc `sdl-config --cflags`
CPPFLAGS +=	$(GFLAGS)

NAME=		lib_va_sdl.so

SRC=		Sdl.cpp
SRC +=		Music.cpp

OBJ=		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(SFLAGS) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
