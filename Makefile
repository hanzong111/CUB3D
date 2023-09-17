# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 20:26:19 by ojing-ha          #+#    #+#              #
#    Updated: 2023/09/17 14:13:10 by ojing-ha         ###   ########.fr        #
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
# MLX_DIR	= mlx/
MLX_DIR	= minilibx_linux/
SRCS_DIR	= srcs/
OBJS_DIR	= objs/

INCLUDES	= -I includes/

CFLAGS	= -Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -g3
LIBFTFLAGS	= -L$(LIBFT_DIR) -lft
MLXFLAGS	= -lmlx -framework OpenGL -framework Appkit

SRC_FILES	= cub3d_main\
				initialize\
				raytracer\
				ray_find_wall\
				vector_operations_1\
				print_functions\
				fill_wall_info\
				sprites\
				texture\
				check_map_utils\
				check_map\
				check_texture_utils\
				check_textures\
				error_and_quit\
				move_player\

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
		@echo "$(YELLOW)Done Creating ./cub3d$(DEF_COLOR)"
		@echo "\n"
		@echo "$(GREEN) -------------$(RED)I $(CYAN)AM $(GREEN)DONE $(YELLOW)MADAFAKA$(GREEN)-------------------------- $(DEF_COLOR)"

# $(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
# 				@$(CC) $(CFLAGS) -c $^ -o $@
# 				@echo "$(GREEN)Compiling $<...$(DEF_COLOR)"
$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -Wall -Wextra -Werror -Imlx_Linux -O3 -c $< -o $@
				@echo "$(GREEN)Compiling $<$(DEF_COLOR)"


# $(NAME)	: ${OBJS}
# 		@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTFLAGS) -L${MLX_DIR} -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean	:
		rm -rf $(OBJS_DIR)
		make clean -C ${LIBFT_DIR}

fclean	:	clean
		rm -f $(NAME)
		make fclean -C ${LIBFT_DIR}

re		:fclean all

.PHONY	:all clean fclean re
