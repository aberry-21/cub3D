/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:14:41 by olebedev          #+#    #+#             */
/*   Updated: 2020/12/11 18:58:32 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_left_camera(t_game *game_prt)
{
	float old_dir_d;
	float old_plane_y;

	old_dir_d = game_prt->player.dir_y;
	game_prt->player.dir_y = game_prt->player.dir_y * cos(game_prt->player.
	rot_speed) - game_prt->player.dir_x * sin(game_prt->player.rot_speed);
	game_prt->player.dir_x = old_dir_d * sin(game_prt->player.rot_speed) + 
	game_prt->player.dir_x * cos(game_prt->player.rot_speed);
	old_plane_y = game_prt->player.plane_y;
	game_prt->player.plane_y= game_prt->player.plane_y * cos(game_prt->player
	.rot_speed) - game_prt->player.plane_x * sin(game_prt->player.rot_speed);
	game_prt->player.plane_x = old_plane_y * sin(game_prt->player.rot_speed) 
	+ game_prt->player.plane_x * cos(game_prt->player.rot_speed);
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}

void	ft_right_camera(t_game *game_prt)
{
	float old_dir_d;
	float old_plane_y;

	old_dir_d = game_prt->player.dir_y;
	game_prt->player.dir_y = game_prt->player.dir_y * cos(-game_prt->player.
	rot_speed) - game_prt->player.dir_x * sin(-game_prt->player.rot_speed);
	game_prt->player.dir_x = old_dir_d * sin(-game_prt->player.rot_speed) + 
	game_prt->player.dir_x * cos(-game_prt->player.rot_speed);
	old_plane_y = game_prt->player.plane_y;
	game_prt->player.plane_y= game_prt->player.plane_y * cos(-game_prt->player
	.rot_speed) - game_prt->player.plane_x * sin(-game_prt->player.rot_speed);
	game_prt->player.plane_x = old_plane_y * sin(-game_prt->player.rot_speed) 
	+ game_prt->player.plane_x * cos(-game_prt->player.rot_speed);
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
	.img, 0, 0);
}

int		ft_controller(int keycode, t_game *game_prt)
{
	if (keycode == 13)//w
		ft_forward(game_prt);
	if (keycode == 1)//s
		ft_back(game_prt);
	if (keycode == 2)//d
		ft_right(game_prt);
	if (keycode == 0)//a
		ft_left(game_prt);
	if (keycode == 124)//->
		ft_right_camera(game_prt);
	if (keycode == 123)//<-
		ft_left_camera(game_prt);
	if (keycode == 53)//esc 
	{
		mlx_destroy_window(game_prt->mlx, game_prt->mlx_win);
		exit(0);
	}
	return (0);
}