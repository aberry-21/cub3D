/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:04:02 by aberry            #+#    #+#             */
/*   Updated: 2020/12/17 20:32:14 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_init_array_texture(int i, t_map *parse_data)
{
	if (i == 0)
		return (parse_data->ft_west);
	if (i == 1)
		return (parse_data->ft_east);
	if (i == 2)
		return (parse_data->ft_north);
	if (i == 3)
		return (parse_data->ft_south);
	return (parse_data->ft_t_sprite);
}

void	ft_init_img_sprite(t_game *game_prt, t_map *parse_data)
{
	if (!(game_prt->sprite_texture.img = mlx_xpm_file_to_image(
	game_prt->mlx, ft_init_array_texture(4, parse_data),
	&game_prt->sprite_texture.img_width,
	&game_prt->sprite_texture.img_height)))
		exit(0);
	game_prt->sprite_texture.addr = mlx_get_data_addr(
	game_prt->sprite_texture.img,
	&game_prt->sprite_texture.bits_per_pixel,
	&game_prt->sprite_texture.line_length,
	&game_prt->sprite_texture.endian);
}

void	ft_init_img(t_game *game_prt, t_map *parse_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(game_prt->wall_texture[i].img = mlx_xpm_file_to_image(
		game_prt->mlx, ft_init_array_texture(i, parse_data),
		&game_prt->wall_texture[i].img_width,
		&game_prt->wall_texture[i].img_height)))
			exit(0);
		game_prt->wall_texture[i].addr = mlx_get_data_addr(
		game_prt->wall_texture[i].img,
		&game_prt->wall_texture[i].bits_per_pixel,
		&game_prt->wall_texture[i].line_length,
		&game_prt->wall_texture[i].endian);
		i++;
	}
	ft_init_img_sprite(game_prt, parse_data);
}

void	ft_init_sprites(t_game *game_prt, t_map *parse_data)
{
	size_t	i;

	i = 0;
	game_prt->num_sprite = parse_data->ft_size_arr_sp;
	if (!(game_prt->sprites_num = malloc(sizeof(size_t)
	* game_prt->num_sprite)))
		exit(ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites_dist = malloc(sizeof(float)
	* game_prt->num_sprite)))
		exit(ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites = malloc(sizeof(t_coord)
	* game_prt->num_sprite)))
		exit(ft_error_massage("Malloc error\n", 13));
	while (i < game_prt->num_sprite)
	{
		game_prt->sprites_num[i] = i;
		game_prt->sprites[i].x = parse_data->ft_sprite[i].x + 0.5;
		game_prt->sprites[i].y = parse_data->ft_sprite[i].y + 0.5;
		i++;
	}
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


void	ft_mlx_init(t_map *parse_data, t_person *parse_person)
{
	t_game	game_prt;

	if (!(game_prt.mlx = mlx_init()))
		exit(1);
	ft_position_player(&game_prt, parse_person);
	ft_init_screen(&game_prt, parse_data);
	ft_init_sprites(&game_prt, parse_data);
	ft_init_img(&game_prt, parse_data);
	ft_init_img_gun(&game_prt);
	ft_raycasting(&game_prt);
	if (parse_data->bmp_bool)
		ft_creat_bmp(&game_prt);
	if (!(game_prt.mlx_win = mlx_new_window(game_prt.mlx, game_prt.screen_width,
	game_prt.screen_height, "Cub3D")))
		exit(0);
	system("afplay ./music/hyper-spoiler.mp3 -v 0.05 & ");
	mlx_put_image_to_window(game_prt.mlx, game_prt.mlx_win,
	game_prt.screen.img, 0, 0);
	mlx_hook(game_prt.mlx_win, 2, 1L << 0, ft_controller, &game_prt);
	mlx_hook(game_prt.mlx_win, 17, 0, &ft_close_window, &game_prt);
	mlx_loop(game_prt.mlx);
}
