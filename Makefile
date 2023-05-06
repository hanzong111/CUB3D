# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 20:26:19 by ojing-ha          #+#    #+#              #
#    Updated: 2023/05/06 15:57:38 by ojing-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR     = \033[0;39m
GRAY         = \033[0;90m
RED         = \033[0;91m
GREEN         = \033[0;92m
YELLOW         = \033[0;93m
BLUE         = \033[0;94m
MAGENTA     = \033[0;95m
CYAN         = \033[0;96m
WHITE         = \033[0;97m
NAME		= cub3d

CC			= gcc

LIBFT_DIR	= libft/
MLX_DIR	= mlx/
# MLX_DIR	= minilibx-linux/
SRCS_DIR	= srcs/
OBJS_DIR	= objs/

INCLUDES	= -I includes

CFLAGS	= -Wall -Werror -Wextra $(HEADER) -fsanitize=address -g3
LIBFTFLAGS	= -L$(LIBFT_DIR) -lft
MLXFLAGS	= -lmlx -framework OpenGL -framework Appkit

SRC_FILES	= cub3d_main\
				initialize\
				raytracer\
				raytracing_utils\
				ray_find_wall\

SRCS	= $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

all		:
		@mkdir -p $(OBJS_DIR)
		@echo "$(MAGENTA) --------------------------INSIDE LIBFT-------------------------- $(CYAN)"
		@echo "\n"
		@make -C ${LIBFT_DIR}
		@echo "$(MAGENTA) --------------------------INSIDE SO_LONG-------------------------- $(CYAN)"
		@echo "\n"
		make $(NAME)
		@echo "$(YELLOW)Done Creating ./so_long$(DEF_COLOR)"
		@echo "\n"
		@echo "$(GREEN) -------------$(RED)I $(CYAN)AM $(GREEN)DONE $(YELLOW)MADAFAKA$(GREEN)-------------------------- $(DEF_COLOR)"

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -c $^ -o $@
				@echo "$(GREEN)Compiling $<...$(DEF_COLOR)"
# $(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
# 				@$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_Linux -O3 -c $< -o $@
# 				@echo "$(GREEN)Compiling $<$(DEF_COLOR)"


$(NAME)	: ${OBJS}
		@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME)
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFTFLAGS) -L${MLX_DIR} -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean	:
		rm -rf $(OBJS_DIR)
		make clean -C ${LIBFT_DIR}

fclean	:	clean
		rm -f $(NAME)
		make fclean -C ${LIBFT_DIR}

re		:fclean all

.PHONY	:all clean fclean re
