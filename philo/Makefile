# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 11:46:49 by juanantonio       #+#    #+#              #
#    Updated: 2024/01/09 16:43:24 by juan-anm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror -MMD 
##LIBS = -lpthread

SRC = main.c \

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(SRC:.c=.d))

$(shell mkdir -p $(OBJ_DIR))

RM = rm -rf

GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(HEADER)
	@$(CC) $(LIBS) $(CFLAGS) -g -I./ -c $< -o $@

all:
	@$(MAKE) $(NAME) --no-print-directory
	
$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)Philosophers compiled$(NC)"

$(NAME)::
	@echo -n

clean:
	@if [ -f "$(OBJS)" ] || [ -f "$(DEPS)" ]; then \
        $(RM) $(OBJS) $(DEPS); \
        echo "$(GREEN)All Files Deleted Successfully$(NC)"; \
		$(RM) $(OBJ_DIR); \
		echo "$(GREEN)Object Directory Deleted$(NC)"; \
    else \
        echo "$(RED)No Files to Clean$(NC)"; \
    fi
	

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)