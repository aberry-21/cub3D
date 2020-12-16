/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:13:38 by aberry            #+#    #+#             */
/*   Updated: 2020/12/16 20:46:31 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_color(t_img tex, int x, int y)
{
	unsigned int	trgb;

	trgb = (tex.addr[tex.line_length * y + 4 * x] + \
	tex.addr[tex.line_length * y + 4 * x + 1] * 256 + \
	tex.addr[tex.line_length * y + 4 * x + 2] * 256 * 256 + \
	tex.addr[tex.line_length * y + 4 * x + 3] * 256 * 256 * 256);
	return (trgb);
}

void			paint_pixel(t_img *image, int x, int y, unsigned int color)
{
	if (image->dark_cf < 1)
		image->dark_cf = 1;
	image->addr[y * image->line_length + x * 4] = \
	get_b(color) / image->dark_cf;
	image->addr[y * image->line_length + x * 4 + 1] = \
	get_g(color) / image->dark_cf;
	image->addr[y * image->line_length + x * 4 + 2] = \
	get_r(color) / image->dark_cf;
	image->addr[y * image->line_length + x * 4 + 3] = \
	get_t(color);
}

void			my_mlx_pixel_put(t_img *screen, int x, int y, int color)
{
	char			*dst;

	dst = screen->addr + (y * screen->line_length + x *
	(screen->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float			ft_start_end(int *draw_start, int *draw_end, t_game *game_prt,
int line_height)
{
	int				skip;
	float			j;

	skip = 0;
	j = 0;
	*draw_start = -line_height / 2 + game_prt->screen_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + game_prt->screen_height / 2;
	if (*draw_end < 0)
		*draw_end = 0;
	if (line_height > game_prt->screen_height)
		skip = (line_height - game_prt->screen_height) / 2;
	j += skip * ((float)game_prt->wall_texture[game_prt->num_tex]
.img_height / (float)(line_height));
	game_prt->screen.dark_cf = (line_height > game_prt->screen_height) ? 1
	: game_prt->screen.dark_cf;
	game_prt->screen.dark_cf *= 0.5;
	return (j);
}

void			paint(t_game *game_prt, int line_height, int x)
{
	int				y;
	float			j;
	int				draw_start;
	int				draw_end;

	j = ft_start_end(&draw_start, &draw_end, game_prt, line_height);
	y = 0;
	while (y < game_prt->screen_height)
	{
		if (y <= draw_start)
			my_mlx_pixel_put(&game_prt->screen, x, y, game_prt->color_celling);
		if (y > draw_start && y < draw_end)
		{
			j += (float)game_prt->wall_texture[game_prt->num_tex].img_height\
			/ (float)(line_height);
			paint_pixel(&game_prt->screen, x, y, get_color(game_prt->\
			wall_texture[game_prt->num_tex], (int)game_prt->wall_texture\
			[game_prt->num_tex].img_width * game_prt->x_texture, (int)(j)));
		}
		if (game_prt->screen.dark_cf < 1)
			game_prt->screen.dark_cf = 1;
		if (y >= draw_end)
			my_mlx_pixel_put(&game_prt->screen, x, y, game_prt->color_floor);
		y++;
	}
}
