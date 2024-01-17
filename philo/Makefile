# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-anm <juan-anm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 11:46:49 by juanantonio       #+#    #+#              #
#    Updated: 2024/01/17 17:00:32 by juan-anm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror -MMD ##-fsanitize=address
LIBS = -pthread

SRC = main.c utils.c initializer.c philive.c\

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRC:.c=.d))

RM = rm -rf

GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(HEADER)
	@$(CC) $(LIBS) $(CFLAGS) -g -I./ -c $< -o $@

all:
	@$(MAKE) $(NAME) --no-print-directory
	$(shell mkdir -p $(OBJ_DIR))
	
$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)Philosophers compiled$(NC)"

$(NAME)::
	@echo -n

clean:
	
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(GREEN)Object Directory Deleted Successfully$(NC)"; \
	fi
	@if [ -n "$(wildcard $(OBJS) $(DEPS))" ]; then \
		$(RM) $(OBJS) $(DEPS); \
		echo "$(GREEN)Object Files Deleted Successfully$(NC)"; \
	else \
		echo "$(RED)No Object Files to Clean$(NC)"; \
	fi


fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)