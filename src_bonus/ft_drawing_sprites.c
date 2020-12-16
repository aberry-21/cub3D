/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:18:14 by aberry            #+#    #+#             */
/*   Updated: 2020/12/16 20:05:49 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_sort_sprites(size_t *num, float *dist, size_t size_array)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size_array)
	{
		j = 0;
		while (i + j < size_array)
		{
			if (dist[i] < dist[i + j])
			{
				ft_swap_float(&dist[i], &dist[i + j]);
				ft_swap_int(&num[i], &num[i + j]);
			}
			j++;
		}
		i++;
	}
}

void	ft_sprite_x(t_raycast_sprite *prt, t_game *game_prt)
{
	prt->draw_start.y = -prt->sprite_height / 2 + game_prt->screen_height / 2;
	prt->draw_end.y = prt->sprite_height / 2 + game_prt->screen_height / 2;
	prt->draw_start.x = -prt->sprite_width / 2 + prt->sprite_screen;
	prt->draw_end.x = prt->sprite_width / 2 + prt->sprite_screen;
	if (prt->draw_start.y < 0)
		prt->draw_start.y = 0;
	if (prt->draw_start.x < 0)
		prt->draw_start.x = 0;
	if (prt->draw_end.y >= game_prt->screen_height)
		prt->draw_end.y = game_prt->screen_height - 1;
	if (prt->draw_end.x >= game_prt->screen_width)
		prt->draw_end.x = game_prt->screen_width - 1;
}

void	ft_drawing_sprite(t_raycast_sprite *prt, t_game *game_prt,
t_raycast *prt_wall)
{
	int			i;
	int			j;
	t_icoord	t;
	int			cf;

	i = prt->draw_start.x;
	while (i < prt->draw_end.x)
	{
		j = prt->draw_start.y;
		t.x = (int)(256 * (i - (-prt->sprite_width / 2 + prt->sprite_screen))
		* game_prt->sprite_texture.img_width / prt->sprite_width) / 256;
		if (prt->transform.y > 0 && i > 0 && i < game_prt->screen_width
		&& prt->transform.y < prt_wall->array_dist[i])
			while (j < prt->draw_end.y)
			{
				cf = (j) * 256 - game_prt->screen_height * 128 +
				prt->sprite_height * 128;
				t.y = ((cf * game_prt->sprite_texture.img_height)
				/ prt->sprite_height) / 256;
				ft_set_color_sprite(get_color(game_prt->sprite_texture,
				t.x, t.y), game_prt, i, j);
				j++;
			}
		i++;
	}
}

void	ft_sprites(t_raycast_sprite *prt, t_game *game_prt, t_raycast *prt_wall)
{
	size_t	i;

	i = -1;
	while (++i < game_prt->num_sprite)
	{
		prt->sprite.x = game_prt->sprites[game_prt->sprites_num[i]].x
		- game_prt->player.pos_x;
		prt->sprite.y = game_prt->sprites[game_prt->sprites_num[i]].y
		- game_prt->player.pos_y;
		prt->proj_cf = 1.0 / (game_prt->player.plane_x * game_prt->player.dir_y
		- game_prt->player.plane_y * game_prt->player.dir_x);
		prt->transform.x = prt->proj_cf * (game_prt->player.dir_y * prt
->sprite.x - game_prt->player.dir_x * prt->sprite.y);
		prt->transform.y = prt->proj_cf * (game_prt->player.plane_x * prt
->sprite.y - game_prt->player.plane_y * prt->sprite.x);
		prt->sprite_screen = (int)((game_prt->screen_width / 2)
		* (1 + prt->transform.x / prt->transform.y));
		prt->sprite_height = abs((int)(game_prt->screen_height
		/ (prt->transform.y)));
		prt->sprite_width = abs((int)(game_prt->screen_height
		/ (prt->transform.y)));
		game_prt->screen.dark_cf = prt->transform.y * 0.5;
		ft_sprite_x(prt, game_prt);
		ft_drawing_sprite(prt, game_prt, prt_wall);
	}
}

void	ft_drawing_sprites(t_game *game_prt, t_raycast *prt_wall)
{
	size_t				i;
	t_raycast_sprite	prt;

	i = 0;
	while (i < game_prt->num_sprite)
	{
		game_prt->sprites_num[i] = i;
		game_prt->sprites_dist[i] = powf((game_prt->player.pos_x
		- game_prt->sprites[i].x), 2)
		+ powf((game_prt->player.pos_y - game_prt->sprites[i].y), 2);
		i++;
	}
	ft_sort_sprites(game_prt->sprites_num, game_prt->sprites_dist,
	game_prt->num_sprite);
	ft_sprites(&prt, game_prt, prt_wall);
}
