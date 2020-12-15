/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:05:22 by olebedev          #+#    #+#             */
/*   Updated: 2020/12/11 19:00:32 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int		ft_check_world_map(size_t prt)
{
	if (prt == 7 || prt == 2)
		return (0);
	return (1);
}

void	ft_forward(t_game *game_prt)
{
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y + 2 * game_prt->
	player.dir_y * game_prt->player.move_speed)][(int)(game_prt->player.pos_x)]))
		game_prt->player.pos_y += game_prt->player.dir_y * game_prt->player.move_speed;
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y)][(int)(game_prt->
	player.pos_x + 2 * game_prt->player.dir_x * game_prt->player.move_speed)]))
		game_prt->player.pos_x += game_prt->player.dir_x * game_prt->player.move_speed;
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}

void	ft_back(t_game *game_prt)
{
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y - 2 * game_prt->
	player.dir_y * game_prt->player.move_speed)][(int)(game_prt->player.pos_x)]))
		game_prt->player.pos_y -= game_prt->player.dir_y * game_prt->player.move_speed;
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y)][(int)(game_prt->
	player.pos_x - 2 * game_prt->player.dir_x * game_prt->player.move_speed)]))
		game_prt->player.pos_x -= game_prt->player.dir_x * game_prt->player.move_speed;
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}

void	ft_right(t_game *game_prt)
{
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y + 2 * game_prt->player.plane_y * game_prt->player.move_speed)][(int)(game_prt->player.pos_x)]))
		game_prt->player.pos_y += game_prt->player.plane_y * game_prt->player.move_speed;
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y)][(int)(game_prt->player.pos_x + 2 * game_prt->player.plane_x * game_prt->player.move_speed)]))
		game_prt->player.pos_x += game_prt->player.plane_x * game_prt->player.move_speed;
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}

void	ft_left(t_game *game_prt)
{
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y - 2 * game_prt->player.plane_y * game_prt->player.move_speed)][(int)(game_prt->player.pos_x)]))
		game_prt->player.pos_y -= game_prt->player.plane_y * game_prt->player.move_speed;
	if(ft_check_world_map(game_prt->map[(int)(game_prt->player.pos_y)][(int)(game_prt->player.pos_x - 2 * game_prt->player.plane_x * game_prt->player.move_speed)]))
		game_prt->player.pos_x -= game_prt->player.plane_x * game_prt->player.move_speed;
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}