/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:07:57 by aberry            #+#    #+#             */
/*   Updated: 2020/12/16 18:41:06 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_param_player(t_game *game_prt, t_person *parse_person)
{
	if (parse_person->ft_view == 'E')
	{
		game_prt->player.dir_y = 0;
		game_prt->player.dir_x = 1;
		game_prt->player.plane_y = 0.66;
		game_prt->player.plane_x = 0;
	}
	if (parse_person->ft_view == 'W')
	{
		game_prt->player.dir_y = 0;
		game_prt->player.dir_x = -1;
		game_prt->player.plane_y = -0.66;
		game_prt->player.plane_x = 0;
	}
	game_prt->player.pos_x = parse_person->x + 0.5;
	game_prt->player.pos_y = parse_person->y + 0.5;
	game_prt->player.move_speed = 0.20;
	game_prt->player.rot_speed = 0.20;
}

void	ft_position_player(t_game *game_prt, t_person *parse_person)
{
	if (parse_person->ft_view == 'N')
	{
		game_prt->player.dir_y = -1;
		game_prt->player.dir_x = 0;
		game_prt->player.plane_y = 0;
		game_prt->player.plane_x = 0.66;
	}
	if (parse_person->ft_view == 'S')
	{
		game_prt->player.dir_y = 1;
		game_prt->player.dir_x = 0;
		game_prt->player.plane_y = 0;
		game_prt->player.plane_x = -0.66;
	}
	ft_param_player(game_prt, parse_person);
}

void	ft_init_screen(t_game *game_prt, t_map *parse_data)
{
	int	screen_width;
	int	screen_height;

	game_prt->screen_width = parse_data->ft_width;
	game_prt->screen_height = parse_data->ft_height;
	mlx_get_screen_size(game_prt, &screen_width, &screen_height);
	if (game_prt->screen_width > screen_width)
		game_prt->screen_width = screen_width;
	if (game_prt->screen_height > screen_height)
		game_prt->screen_height = screen_height;
	game_prt->map = parse_data->ft_map;
	game_prt->color_celling = parse_data->ft_ceilling;
	game_prt->color_floor = parse_data->ft_floor;
	if (!(game_prt->screen.img = mlx_new_image(game_prt->mlx,
	game_prt->screen_width, game_prt->screen_height)))
		exit(0);
	game_prt->screen.addr = mlx_get_data_addr(game_prt->screen.img, &game_prt->
	screen.bits_per_pixel, &game_prt->screen.line_length,
	&game_prt->screen.endian);
}

int		ft_close_window(int keycode, t_game *game_prt)
{
	(void)keycode;
	(void)game_prt;
	exit(0);
	return (0);
}
