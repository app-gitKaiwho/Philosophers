# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 16:52:50 by lvon-war          #+#    #+#              #
#    Updated: 2023/05/26 18:26:05 by lvon-war         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
ENAME	=	fdf
NAME	=	FdF.a
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar -rsc
FILES	=	

# Path for .c , .h and .o Files 
LIBFT	=	./include/libft/lib.a
SRC_PATH := ./SRC/
OBJ_PATH := ./OBJ/

# Compliation under Mac OS
ifeq ($(shell uname),Darwin)
INC_PATH := -I ./include/libft/include -I ./include
LINKER := -L 
FRAMEWORK := 
# Compliation under anything else (but only work under linux)
else
INC_PATH := -I ./include/libft/include -I ./include
LINKER := -L
FRAMEWORK :=
endif

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo [INFO] Compliling libft
	@make -C ./include/libft

# Files to compile
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
	$(CC) $(CFLAGS) $(NAME) $(LIBFT) $(INC_PATH) $(FRAMEWORK) $(LINKER) -o $(ENAME)

# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*

fclean: clean
		@$(RM) -rfv $(NAME)
		@$(RM) -rfv $(ENAME)
deepclean : fclean
		@make fclean -C ./include/libft
re: fclean all

san: all
	$(CC) $(CFLAGS) $(NAME) $(LIBFT) $(INC_PATH) $(FRAMEWORK) $(LINKER) -fsanitize=address -o $(ENAME)

test: all

.PHONY : clean fclean re