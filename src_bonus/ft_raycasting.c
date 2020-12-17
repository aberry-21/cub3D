/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:51:28 by aberry            #+#    #+#             */
/*   Updated: 2020/12/17 19:53:35 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_raycasting(t_game *game_prt, t_raycast *prt, int x)
{
	prt->camera = 2 * x / (float)game_prt->screen_width - 1;
	prt->ray_dir.x = game_prt->player.dir_x + game_prt->player.plane_x
	* prt->camera;
	prt->ray_dir.y = game_prt->player.dir_y + game_prt->player.plane_y
	* prt->camera;
	prt->map_x = (int)game_prt->player.pos_x;
	prt->map_y = (int)game_prt->player.pos_y;
	prt->delta_dist.x = fabs((1 / prt->ray_dir.x));
	prt->delta_dist.y = fabs((1 / prt->ray_dir.y));
}

void	ft_calc_step(t_game *game_prt, t_raycast *prt)
{
	if (prt->ray_dir.y < 0)
	{
		prt->step.y = -1;
		prt->dist.y = (game_prt->player.pos_y - prt->map_y) * prt->delta_dist.y;
	}
	else
	{
		prt->step.y = 1;
		prt->dist.y = (prt->map_y + 1.0 - game_prt->player.pos_y)
		* prt->delta_dist.y;
	}
	if (prt->ray_dir.x < 0)
	{
		prt->step.x = -1;
		prt->dist.x = (game_prt->player.pos_x - prt->map_x) * prt->delta_dist.x;
	}
	else
	{
		prt->step.x = 1;
		prt->dist.x = (prt->map_x + 1.0 - game_prt->player.pos_x)
		* prt->delta_dist.x;
	}
}

void	ft_calc_dist(t_game *game_prt, t_raycast *prt)
{
	if (prt->side)
	{
		prt->dist_to_wall = (prt->map_x - game_prt->player.pos_x
		+ (1 - prt->step.x) / 2) / prt->ray_dir.x;
		game_prt->x_texture = (game_prt->player.pos_y + prt->dist_to_wall
		* prt->ray_dir.y) - (int)(game_prt->player.pos_y + prt->dist_to_wall
		* prt->ray_dir.y);
	}
	else
	{
		prt->dist_to_wall = (prt->map_y - game_prt->player.pos_y
		+ (1 - prt->step.y) / 2) / prt->ray_dir.y;
		game_prt->x_texture = (game_prt->player.pos_x
		+ prt->dist_to_wall * prt->ray_dir.x)
		- (int)(game_prt->player.pos_x + prt->dist_to_wall * prt->ray_dir.x);
	}
}

void	ft_dda_algorithm(t_game *game_prt, t_raycast *prt)
{
	while (game_prt->map[prt->map_y][prt->map_x] == 2 || game_prt->map[prt
->map_y][prt->map_x] == 9 || game_prt->map[prt->map_y][prt->map_x] == 8)
	{
		if (prt->dist.y < prt->dist.x)
		{
			prt->dist.y += prt->delta_dist.y;
			prt->map_y += prt->step.y;
			prt->side = 0;
		}
		else
		{
			prt->dist.x += prt->delta_dist.x;
			prt->map_x += prt->step.x;
			prt->side = 1;
		}
	}
	ft_calc_dist(game_prt, prt);
}


void	ft_drawing_gun(t_game *game_prt, int index)
{
	int x = 0;
	int y = 0;
	
	float w_proj = (float)game_prt->gun[index].img_width / (float)(game_prt->screen_width);
	float h_proj = (float)game_prt->gun[index].img_height / (float)(game_prt->screen_height);
	float j = 0;
	float i = 0;
	int color;
	int proj_height = game_prt->screen_height / 2;
	int proj_width = game_prt->screen_width / 2;
	x = game_prt->screen_width - proj_width;
	while (x < game_prt->screen_width)
	{
		y = game_prt->screen_height- proj_height;
		w_proj = (float)game_prt->gun[index].img_width / (float)(proj_width);
		j = 0;
		while (y < game_prt->screen_height)
		{
			h_proj = (float)game_prt->gun[index].img_height / (float)(proj_height);
			j += h_proj;
			color = get_color(game_prt->gun[index], (int)(i), (int)(j));
			if ((color & 0x00FFFFFF) != 0)
				paint_pixel(&game_prt->screen, x, y, color);
			y++;
		}
		i += w_proj;
		x++;
	}
	
}

void	ft_raycasting(t_game *game_prt)
{
	int			x;
	t_raycast	prt;

	x = 0;
	if (!(prt.array_dist = malloc(sizeof(float) * game_prt->screen_width)))
		exit(0);
	while (x < game_prt->screen_width)
	{
		ft_init_raycasting(game_prt, &prt, x);
		ft_calc_step(game_prt, &prt);
		ft_dda_algorithm(game_prt, &prt);
		ft_choose_tex(game_prt, &prt);
		game_prt->screen.dark_cf = prt.dist_to_wall;
		paint(game_prt, (int)(game_prt->screen_height / prt.dist_to_wall), x);
		prt.array_dist[x] = prt.dist_to_wall;
		x++;
	}
	ft_drawing_sprites(game_prt, &prt);
	game_prt->screen.dark_cf = 1;
	ft_drawing_gun(game_prt, 0);
	free(prt.array_dist);
}
