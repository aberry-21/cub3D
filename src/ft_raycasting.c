/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:51:28 by aberry            #+#    #+#             */
/*   Updated: 2020/12/12 15:18:00 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_raycasting(t_game *game_prt, t_raycast *prt, int x)
{
	prt->camera = 2 * x / (float)game_prt->screen_width - 1;
	prt->ray_dir.x = game_prt->player.dir_x + game_prt->player.plane_x * prt->camera;
	prt->ray_dir.y = game_prt->player.dir_y + game_prt->player.plane_y * prt->camera;
	prt->map_x = (int)game_prt->player.pos_x;
	prt->map_y = (int)game_prt->player.pos_y;
	prt->delta_dist.x = fabs((1 / prt->ray_dir.x));
	prt->delta_dist.y = fabs((1 / prt->ray_dir.y));
}
void	ft_calc_step(t_game *game_prt, t_raycast *prt)
{
	if(prt->ray_dir.y < 0)
	{
		prt->step.y = -1;
		prt->dist.y = (game_prt->player.pos_y - prt->map_y) * prt->delta_dist.y;
	}
	else
	{
		prt->step.y = 1;
		prt->dist.y = (prt->map_y + 1.0 - game_prt->player.pos_y) * prt->delta_dist.y;
	}
	if(prt->ray_dir.x < 0)
	{
		prt->step.x = -1;
		prt->dist.x = (game_prt->player.pos_x - prt->map_x) * prt->delta_dist.x;
	}
	else
	{
		prt->step.x = 1;
		prt->dist.x = (prt->map_x + 1.0 - game_prt->player.pos_x) * prt->delta_dist.x;
	}
}

void	ft_calc_dist(t_game *game_prt, t_raycast *prt)
{
	if (prt->side)
	{
		prt->dist_to_wall = (prt->map_x - game_prt->player.pos_x + (1 - prt->step.x) / 2) / prt->ray_dir.x;
		game_prt->x_texture = (game_prt->player.pos_y + prt->dist_to_wall * prt->ray_dir.y)\
		- (int)(game_prt->player.pos_y + prt->dist_to_wall * prt->ray_dir.y);
	}
	else
	{
		prt->dist_to_wall = (prt->map_y - game_prt->player.pos_y + (1 - prt->step.y) / 2) / prt->ray_dir.y;
		game_prt->x_texture = (game_prt->player.pos_x + prt->dist_to_wall * prt->ray_dir.x)\
		- (int)(game_prt->player.pos_x + prt->dist_to_wall * prt->ray_dir.x);
	}
}
void	ft_dda_algorithm(t_game *game_prt, t_raycast *prt)
{
	while (game_prt->map[prt->map_y][prt->map_x] == 2 || game_prt->map[prt->map_y][prt->map_x] == 9 || game_prt->map[prt->map_y][prt->map_x] == 8)
	{
		if(prt->dist.y < prt->dist.x)
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
void	ft_choose_tex(t_game *game_prt, t_raycast *prt)//!!!
{
	if (prt->side)
		if (prt->map_x < game_prt->player.pos_x)
			game_prt->num_tex = 0;
		else
			game_prt->num_tex = 1;
	else
		if (prt->map_y < game_prt->player.pos_y)
			game_prt->num_tex = 2;
		else
			game_prt->num_tex = 3;
}

#define swap(temp, a,b) temp=a;a=b;b=temp;
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



typedef struct	s_coords
{
	float		x;
	int			y;
}				t_coords;

void	sort(t_coords *sprites, int size_array)
{
	size_t	i;
	size_t	j;
	t_coords tmp;

	i = 0;
	while (i < size_array)
	{
		j = 0;
		while (i + j < size_array)
		{
			if (sprites[i].x > sprites[i + j].x)
			{
				tmp = sprites[i];
				sprites[i] = sprites[i + j];
				sprites[i + j] = tmp; 
			}
			j++;
		}
		i++;
	}
}
void ft_sort_sprites(size_t *num, float *dist, int size_array)
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
typedef struct	s_raycast_sprite
{
	t_coord		sprite;
	float		proj_cf;
	int			sprite_screen;
	t_coord		transform;
	int			sprite_height;
	int			sprite_width;
	t_icoord	draw_start;
	t_icoord	draw_end;
}				t_raycast_sprite;

void	ft_sprite_x(t_raycast_sprite *prt, t_game *game_prt)
{
	prt->draw_start.y = -prt->sprite_height / 2 + game_prt->screen_height / 2;
	prt->draw_end.y = prt->sprite_height / 2 + game_prt->screen_height / 2;
	prt->draw_start.x = -prt->sprite_width / 2 + prt->sprite_screen;
	prt->draw_end.x = prt->sprite_width / 2 + prt->sprite_screen;
	if(prt->draw_start.y < 0)
		prt->draw_start.y = 0;
	if(prt->draw_start.x < 0)
	{
		prt->draw_start.x = 0;
	}

	if(prt->draw_end.y >= game_prt->screen_height)
	{
		prt->draw_end.y = game_prt->screen_height - 1;

	}
	if(prt->draw_end.x >= game_prt->screen_width)
		prt->draw_end.x = game_prt->screen_width - 1;
}

void	ft_drawing_sprite(t_raycast_sprite *prt, t_game *game_prt, t_raycast *prt_wall)
{
	int		i;
	int		j;
	t_icoord	t;
	int			color;
	int			cf;

	i = prt->draw_start.x;
	while (i < prt->draw_end.x)
	{
		j = prt->draw_start.y;
		t.x = (int)(256 * (i - (-prt->sprite_width / 2 + prt->sprite_screen)) * game_prt->sprite_texture.img_width / prt->sprite_width) / 256;
		if(prt->transform.y > 0 && i > 0 && i < game_prt->screen_width && prt->transform.y < prt_wall->array_dist[i])
		{
			while (j < prt->draw_end.y)
			{
				cf = (j) * 256 - game_prt->screen_height * 128 + prt->sprite_height * 128;
				t.y = ((cf * game_prt->sprite_texture.img_height) / prt->sprite_height) / 256;
				color =  get_color(game_prt->sprite_texture, t.x, t.y);
				if ((color & 0x00FFFFFF) != 0)
					paint_pixel(&game_prt->screen, i, j, color);
				j++;
			}
		}
		i++;
	}
	
}
void	ft_sprites(t_raycast_sprite *prt, t_game *game_prt, t_raycast *prt_wall)
{
	size_t	i;

	i = 0;
	while (i < game_prt->num_sprite)//?
	{
		prt->sprite.x = game_prt->sprites[game_prt->sprites_num[i]].x - game_prt->player.pos_x;
		prt->sprite.y = game_prt->sprites[game_prt->sprites_num[i]].y - game_prt->player.pos_y;
		prt->proj_cf = 1.0 / (game_prt->player.plane_x * game_prt->player.dir_y- game_prt->player.plane_y * game_prt->player.dir_x);
		prt->transform.x = prt->proj_cf * (game_prt->player.dir_y * prt->sprite.x - game_prt->player.dir_x * prt->sprite.y);
		prt->transform.y = prt->proj_cf * (game_prt->player.plane_x * prt->sprite.y - game_prt->player.plane_y * prt->sprite.x);
		prt->sprite_screen = (int)((game_prt->screen_width / 2) * (1 + prt->transform.x / prt->transform.y));
		prt->sprite_height = abs((int)(game_prt->screen_height / (prt->transform.y)));
		prt->sprite_width = abs((int)(game_prt->screen_height / (prt->transform.y)));
		ft_sprite_x(prt, game_prt);
		ft_drawing_sprite(prt, game_prt, prt_wall);
		i++;
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
		game_prt->sprites_dist[i] = powf((game_prt->player.pos_x - game_prt->sprites[i].x), 2)
		+ powf((game_prt->player.pos_y - game_prt->sprites[i].y), 2);
		i++;
	}
	ft_sort_sprites(game_prt->sprites_num, game_prt->sprites_dist, game_prt->num_sprite);
	ft_sprites(&prt, game_prt, prt_wall);
}

void	ft_raycasting(t_game *game_prt)
{
	int			x;
	t_raycast	prt;

	x = 0;
	if (!(prt.array_dist = malloc(sizeof(float) * game_prt->screen_width)))
	{
		ft_error_massage("Malloc error\n", 13);
		return ;//free
	}
	while (x < game_prt->screen_width)
	{
		ft_init_raycasting(game_prt, &prt, x);
		ft_calc_step(game_prt, &prt);
		ft_dda_algorithm(game_prt, &prt);
		ft_choose_tex(game_prt, &prt);
		paint(game_prt, (int)(game_prt->screen_height / prt.dist_to_wall), x);
		prt.array_dist[x] = prt.dist_to_wall;
		x++;
	}
	ft_drawing_sprites(game_prt, &prt);
	free(prt.array_dist);
}