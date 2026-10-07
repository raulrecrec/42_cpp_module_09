# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/07 14:57:13 by rexposit          #+#    #+#              #
#    Updated: 2026/10/07 14:57:39 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp	\
		RPN.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re