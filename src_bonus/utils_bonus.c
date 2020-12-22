/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:20:32 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 17:26:27 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void		ft_drawing_gun(t_game *game_prt, int index)
{
	int		x;
	int		y;
	float	j;
	float	i;
	int		color;

	x = game_prt->screen_width - game_prt->screen_width / 2;
	i = 0;
	while (x < game_prt->screen_width)
	{
		y = game_prt->screen_height - game_prt->screen_height / 2;
		j = 0;
		while (y < game_prt->screen_height)
		{
			j += (float)game_prt->gun[index].img_height / (float)(game_prt->
			screen_height / 2);
			color = get_color(game_prt->gun[index], (int)(i), (int)(j));
			if ((color & 0x00FFFFFF) != 0)
				paint_pixel(&game_prt->screen, x, y, color);
			y++;
		}
		i += (float)game_prt->gun[index].img_width / (float)(game_prt->
		screen_width / 2);
		x++;
	}
}

int			ft_create_rgb(int color, float cf)
{
	int	rgb[4];

	rgb[0] = color & 255;
	rgb[1] = color >> 8 & 255;
	rgb[2] = color >> 16 & 255;
	rgb[3] = color >> 24 & 255;
	return (ft_create_hex(rgb[3], rgb[2] / cf, rgb[1] / cf, rgb[0] / cf));
}

void		ft_drawing_sky(t_game *game_prt, int x, int *y, int draw_start)
{
	float	x_sky;
	float	y_sky;
	float	h_proj;
	float	tmp;

	tmp = game_prt->screen.dark_cf;
	game_prt->screen.dark_cf = 1;
	h_proj = (float)game_prt->sky_texture.img_height /
	(float)(game_prt->screen_height) * 2;
	x_sky = ((float)game_prt->sky_texture.img_width / (float)(game_prt
->screen_width)) * x + fabs(game_prt->sky_offset);
	while (x_sky > game_prt->sky_texture.img_width)
		x_sky -= game_prt->sky_texture.img_width;
	y_sky = 0;
	while (*y < draw_start)
	{
		paint_pixel(&game_prt->screen, x, *y, get_color(game_prt->sky_texture,
		(int)(x_sky), (int)(y_sky)));
		y_sky += h_proj;
		(*y)++;
	}
	game_prt->screen.dark_cf = tmp;
}

void		paint_wall(t_game *game_prt, int x, int y, int j)
{
	paint_pixel(&game_prt->screen, x, y, get_color(game_prt->\
	wall_texture[game_prt->num_tex], (int)game_prt->wall_texture\
	[game_prt->num_tex].img_width * game_prt->x_texture, (int)(j)));
}

void		ft_init_img_skybox(t_game *game_prt)
{
	game_prt->sky_offset = 0;
	if (!(game_prt->sky_texture.img = mlx_xpm_file_to_image(
	game_prt->mlx, "./textures/star_sky.xpm",
	&game_prt->sky_texture.img_width,
	&game_prt->sky_texture.img_height)))
		exit(0);
	game_prt->sky_texture.addr = mlx_get_data_addr(
	game_prt->sky_texture.img,
	&game_prt->sky_texture.bits_per_pixel,
	&game_prt->sky_texture.line_length,
	&game_prt->sky_texture.endian);
}
