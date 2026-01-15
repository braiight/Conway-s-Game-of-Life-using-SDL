# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gumallet <gumallet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 20:44:33 by gumallet          #+#    #+#              #
#    Updated: 2026/01/15 12:56:34 by gumallet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.cpp life.cpp
OBJS    = $(SRCS:.cpp=.o)

CXX     = g++
CXXFLAGS = -Wall -Wextra -Werror $(shell sdl2-config --cflags)
LDFLAGS  = $(shell sdl2-config --libs)

NAME    = life

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
