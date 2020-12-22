/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:20:06 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 17:27:20 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_choose_tex(t_game *game_prt, t_raycast *prt)
{
	if (prt->side)
		if (prt->map_x < game_prt->player.pos_x)
			game_prt->num_tex = 0;
		else
			game_prt->num_tex = 1;
	else if (prt->map_y < game_prt->player.pos_y)
		game_prt->num_tex = 2;
	else
		game_prt->num_tex = 3;
}

void	ft_swap_float(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swap_int(size_t *a, size_t *b)
{
	size_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_set_color_sprite(unsigned int color, t_game *game_prt, int i, int j)
{
	if ((color & 0x00FFFFFF) != 0)
		paint_pixel(&game_prt->screen, i, j, color);
}

void	ft_init_img_gun(t_game *game_prt)
{
	if (!(game_prt->gun[1].img = mlx_xpm_file_to_image(
	game_prt->mlx, "./textures/gun_fire.xpm",
	&game_prt->gun[1].img_width,
	&game_prt->gun[1].img_height)))
		exit(0);
	game_prt->gun[1].addr = mlx_get_data_addr(
	game_prt->gun[1].img,
	&game_prt->gun[1].bits_per_pixel,
	&game_prt->gun[1].line_length,
	&game_prt->gun[1].endian);
	if (!(game_prt->gun[0].img = mlx_xpm_file_to_image(
	game_prt->mlx, "./textures/gun_without_fire.xpm",
	&game_prt->gun[0].img_width,
	&game_prt->gun[0].img_height)))
		exit(0);
	game_prt->gun[0].addr = mlx_get_data_addr(
	game_prt->gun[0].img,
	&game_prt->gun[0].bits_per_pixel,
	&game_prt->gun[0].line_length,
	&game_prt->gun[0].endian);
}
