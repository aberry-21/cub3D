# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberry <aberry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 18:05:43 by aberry            #+#    #+#              #
#    Updated: 2020/12/22 12:54:06 by aberry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS	= -g -Ofast -mprefer-vector-width=512 -Wall -Wextra -Werror
COMP = $(CC) $(CFLAGS) $(INCLUDES)
#libft connect
LIBFT_DIR = libft/
LIBFT_H = -I $(LIBFT_DIR)
LIBFT_A = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_A)
#headers connect
HEAD_DIR = include/
CUB_H = -I $(HEAD_DIR)
HEAD = $(HEAD_DIR)cub3d.h
HEAD_BONUS= $(HEAD_DIR)cub3d_bonus.h
INCLUDES = $(LIBFT_H) $(CUB_H)
#src connect
SRC_DIR = src/
SRC_FILES = main.c \
			ft_check_map.c \
			ft_parse_map.c \
			ft_cub_cl_tex_for_parse.c \
			ft_parse_param.c \
			ft_cub_parse.c \
			ft_cub_parse_utils.c \
			ft_cub_resolution_for_parse.c\
			ft_init_mlx.c\
			ft_raycasting.c\
			ft_rgbt.c\
			ft_drawing.c\
			ft_controller_player.c\
			ft_controller.c\
			ft_bmp_screen.c\
			ft_init_mlx_utils.c\
			ft_drawing_sprites.c\
			ft_raycasting_utils.c
#src bonus connect
SRC_DIR_BONUS = src_bonus/
SRC_FILES_BONUS = main_bonus.c \
			ft_check_map_bonus.c \
			ft_parse_map_bonus.c \
			ft_cub_cl_tex_for_parse_bonus.c \
			ft_parse_param_bonus.c \
			ft_cub_parse_bonus.c \
			ft_cub_parse_utils_bonus.c \
			ft_cub_resolution_for_parse_bonus.c\
			ft_init_mlx_bonus.c\
			ft_raycasting_bonus.c\
			ft_rgbt_bonus.c\
			ft_drawing_bonus.c\
			ft_controller_player_bonus.c\
			ft_controller_bonus.c\
			ft_bmp_screen_bonus.c\
			ft_init_mlx_utils_bonus.c\
			ft_drawing_sprites_bonus.c\
			ft_raycasting_utils_bonus.c\
			utils_bonus.c
#obj connect
OBJ_DIR = obj/
OBJ_FILE =  $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILE))
#obj bonus connect
OBJ_DIR_BONUS = obj_bonus/
OBJ_FILE_BONUS =  $(SRC_FILES_BONUS:.c=.o)
OBJ_BONUS  = $(addprefix $(OBJ_DIR_BONUS), $(OBJ_FILE_BONUS))
#make connect
all: lib $(NAME)
lib:
	@make -C $(LIBFT_DIR)
$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) $(HEAD)
	@make -C mlx_mms
	@mv mlx_mms/libmlx.dylib .
	@gcc $(CFLAGS) -L. -lmlx -framework OpenGL -framework Appkit $(LIBFT) $(OBJ) -o $(NAME)
	@echo "\033[32m \tcompiled \t cub3D \t\t finish \033[0m"
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\033[36m \tmkdir \t\t objects \t finish \033[0m"
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD)
	@$(COMP) -c $< -o $@
#make bonus connect
bonus: lib $(LIBFT) $(OBJ_DIR_BONUS) $(OBJ_BONUS) $(HEAD_BONUS)
	@make -C mlx_mms
	@mv mlx_mms/libmlx.dylib .
	@gcc $(CFLAGS) -L. -lmlx -framework OpenGL -framework Appkit $(LIBFT) $(OBJ_BONUS) -o $(NAME)
	@echo "\033[32m \tcompiled \t cub3D \t\t finish \033[0m"
$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)
	@echo "\033[36m \tmkdir \t\t objects \t finish \033[0m"
$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c $(HEAD_BONUS)
	@$(COMP) -c $< -o $@
clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@make -C mlx_mms clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "\033[35m \tclean \t\t\t\t finish \033[0m"
	@rm -f ./Screenshot.bmp
fclean: clean
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@rm -f $(LIBFT_A)
	@rm -f $(NAME)
	@rm -f libmlx.dylib
	@echo "\033[35m \tfclean \t\t\t\t finish \033[0m"
	@echo	 "-----------------------------------------------"
	@echo	 "                   /\_____/\                   "
	@echo	 "                  /  \033[36mo   o\033[0m  \                  "
	@echo	 "                 ( ==  ^  == )                 "
	@echo	 "                  )         (                  "
	@echo	 "                 (           )                 "
	@echo	 "                ( (  )   (  ) )                "
	@echo	 "               (__(__)___(__)__)               "
	@echo	 "-----------------------------------------------"
re: fclean all
	@echo "\033[35m \tfclean \t\t all \t\t finish \033[0m"
.PHONY: all clean fclean re bonus