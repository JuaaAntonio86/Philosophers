# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 11:46:49 by juanantonio       #+#    #+#              #
#    Updated: 2024/01/09 12:33:01 by juan-anm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -MMD

SRC = main.c \

OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

RM = rm -rf
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@$(CC) $(CFLAGS) -g -I./ -c $< -o $@

all:
	@$(MAKE) $(NAME) --no-print-directory
	
$(NAME):: $(OBJS)
	
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)Philosophers compiled$(NC)"

$(NAME)::
	@echo -n

clean:
	@$(RM) $(OBJS) $(DEPS) --no-print-directory
	@echo "$(GREEN)All Files Deleted Successfully$(NC)"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)