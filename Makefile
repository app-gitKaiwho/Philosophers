# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:52:50 by lvon-war          #+#    #+#              #
#    Updated: 2023/12/18 11:05:40 by lvon-war         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
ENAME	=	philo
NAME	=	philo.a
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar -rsc
FILES	=	pthread.c philoaction.c utils.c minilib.c

# Path for .c , .h and .o Files 
SRC_PATH := ./SRC/
OBJ_PATH := ./OBJ/
RESULT_PATH := ./result/

# Compliation under Mac OS
ifeq ($(shell uname),Darwin)
INC_PATH := 
LINKER :=
FRAMEWORK := -lpthread
# Compliation under anything else (but only work under linux)
else
INC_PATH := 
LINKER := 
FRAMEWORK := -lpthread
endif

all : $(NAME)
OBJ1 := $(FILES:.c=.o)
OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJ1))

# Build .o first
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)     

# Build final Binary
$(NAME): $(OBJ) $(MLX)
	@echo [INFO] Creating $(Shell uname) Binary Executable [$(NAME)]
	$(AR) $(NAME) $(OBJ) $(LINKFLAGS)
	$(CC) $(CFLAGS) $(NAME) $(INC_PATH) $(FRAMEWORK) $(LINKER) -o $(ENAME)

# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@echo "Object..."
	@$(RM) -rfv $(OBJ_PATH)*
	@echo "Result..."
	@$(RM) -rfv $(RESULT_PATH)*

fclean: clean
		@echo "Archive..."
		@$(RM) -rfv $(NAME)
		@echo "Executable..."
		@$(RM) -rfv $(ENAME)

deepclean : fclean
	@echo "libft..."
		@make fclean -C ./include/libft

re: fclean all

san: all
	$(CC) $(CFLAGS) $(NAME) $(INC_PATH) $(FRAMEWORK) $(LINKER) -fsanitize=address -o $(ENAME)

test: all
	clear
	./script/test.sh

.PHONY : clean fclean re