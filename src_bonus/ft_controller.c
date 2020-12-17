/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:14:41 by olebedev          #+#    #+#             */
/*   Updated: 2020/12/17 20:30:56 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	game_prt->player.plane_y = game_prt->player.plane_y * cos(game_prt->player
.rot_speed) - game_prt->player.plane_x * sin(game_prt->player.rot_speed);
	game_prt->player.plane_x = old_plane_y * sin(game_prt->player.rot_speed)
	+ game_prt->player.plane_x * cos(game_prt->player.rot_speed);
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
.img, 0, 0);
	mlx_do_sync(game_prt->mlx);
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
	game_prt->player.plane_y = game_prt->player.plane_y * cos(-game_prt->player
.rot_speed) - game_prt->player.plane_x * sin(-game_prt->player.rot_speed);
	game_prt->player.plane_x = old_plane_y * sin(-game_prt->player.rot_speed)
	+ game_prt->player.plane_x * cos(-game_prt->player.rot_speed);
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
.img, 0, 0);
	mlx_do_sync(game_prt->mlx);
}

void	ft_gun(t_game *game_prt)
{
	system("afplay ./music/laser.mp3 & ");
	ft_raycasting(game_prt);
	ft_drawing_gun(game_prt, 1);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
.img, 0, 0);
	mlx_do_sync(game_prt->mlx);
	ft_raycasting(game_prt);
	mlx_put_image_to_window(game_prt->mlx, game_prt->mlx_win, game_prt->screen
.img, 0, 0);
	mlx_do_sync(game_prt->mlx);
}

int		ft_controller(int keycode, t_game *game_prt)
{
	if (keycode == 13)
		ft_forward(game_prt);
	if (keycode == 1)
		ft_back(game_prt);
	if (keycode == 2)
		ft_right(game_prt);
	if (keycode == 0)
		ft_left(game_prt);
	if (keycode == 124)
		ft_right_camera(game_prt);
	if (keycode == 123)
		ft_left_camera(game_prt);
	if (keycode == 49)
		ft_gun(game_prt);
	if (keycode == 53)
	{
		system ("killall afplay");
		exit(0);
	}
	return (0);
}
