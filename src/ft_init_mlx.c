/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:49:57 by aberry            #+#    #+#             */
/*   Updated: 2020/12/08 19:27:04 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_param_player(t_game *game_prt, t_person *parse_person)
{
	game_prt->player.pos_x = parse_person->x + 0.5;
	game_prt->player.pos_y = parse_person->y + 0.5;
	game_prt->player.move_speed = 0.20;
	game_prt->player.rot_speed = 0.20; 
}
void	ft_position_player(t_game *game_prt, t_person *parse_person)
{
	if (parse_person->ft_view == 'N')
	{
		game_prt->player.dir_y = -1, game_prt->player.dir_x = 0;
		game_prt->player.plane_y = 0, game_prt->player.plane_x = 0.66;
	}
	if (parse_person->ft_view == 'S')
	{
		game_prt->player.dir_y = 1, game_prt->player.dir_x = 0;
		game_prt->player.plane_y = 0, game_prt->player.plane_x = -0.66;
	}
	if (parse_person->ft_view == 'E')
	{
		game_prt->player.dir_y = 0, game_prt->player.dir_x = 1;
		game_prt->player.plane_y = 0.66, game_prt->player.plane_x = 0;
	}
	if (parse_person->ft_view == 'W')
	{
		game_prt->player.dir_y = 0, game_prt->player.dir_x = -1;
		game_prt->player.plane_y = -0.66, game_prt->player.plane_x = 0;
	}
	ft_param_player(game_prt, parse_person);
}


char	*ft_init_array_texture(int i, t_map *parse_data)
{
	if (i == 0)
		return (parse_data->ft_west);
	if (i == 1)
		return (parse_data->ft_east);
	if (i == 2)
		return (parse_data->ft_north);
	if (i == 3)
		return (parse_data->ft_south);//+
	return (parse_data->ft_t_sprite);
}

void	ft_init_img_sprite(t_game *game_prt,t_map *parse_data,\
t_person *parse_person)
{

	if (!(game_prt->sprite_texture.img = mlx_xpm_file_to_image(\
	game_prt->mlx, ft_init_array_texture(4, parse_data),\
	&game_prt->sprite_texture.img_width,\
	&game_prt->sprite_texture.img_height)))
		exit(-ft_free_exit(parse_data, parse_person));
	game_prt->sprite_texture.addr = mlx_get_data_addr(\
	game_prt->sprite_texture.img,\
	&game_prt->sprite_texture.bits_per_pixel,\
	&game_prt->sprite_texture.line_length,\
	&game_prt->sprite_texture.endian);
}
void	ft_init_img(t_game *game_prt,t_map *parse_data, t_person *parse_person)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(game_prt->wall_texture[i].img = mlx_xpm_file_to_image(\
		game_prt->mlx, ft_init_array_texture(i, parse_data),\
		&game_prt->wall_texture[i].img_width,\
		&game_prt->wall_texture[i].img_height)))
			exit(-ft_free_exit(parse_data, parse_person));
		game_prt->wall_texture[i].addr = mlx_get_data_addr(\
		game_prt->wall_texture[i].img,\
		&game_prt->wall_texture[i].bits_per_pixel,\
		&game_prt->wall_texture[i].line_length,\
		&game_prt->wall_texture[i].endian);
		i++;
	}
	ft_init_img_sprite(game_prt, parse_data, parse_person);
}
void	ft_init_screen(t_game *game_prt,t_map *parse_data)
{
	int	screen_width = 0;
	int	screen_height = 0;
	game_prt->screen_width = parse_data->ft_width;
	game_prt->screen_height = parse_data->ft_height;
	//mlx_get_screen_size(game_prt, &screen_width, &screen_height);
	// if (game_prt->screen_width  > screen_width)
	// 	game_prt->screen_width = screen_width;
	// if (game_prt->screen_height  > screen_height)
	// 	game_prt->screen_height = screen_height;
	game_prt->mlx_win = mlx_new_window(game_prt->mlx, game_prt->screen_width,\
	game_prt->screen_height, "Cub3D");
	game_prt->map = parse_data->ft_map;
	game_prt->color_celling = parse_data->ft_ceilling;
	game_prt->color_floor = parse_data->ft_floor;
}

void	ft_print_map_p(t_map *map, t_game *game_prt)
{
	size_t	i;
	size_t	j;
	i = 0;
	while (i < map->ft_height_mp)
	{
		j = 0;
		while (j < map->ft_width_mp)
		{
			printf("%lu", game_prt->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int		ft_init_sprites(t_game *game_prt, t_map *parse_data)
{
	int i;

	i = 0;
	game_prt->num_sprite = parse_data->ft_size_arr_sp;
	if (!(game_prt->sprites_num = malloc(sizeof(size_t) * game_prt->num_sprite)))
		return (ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites_dist = malloc(sizeof(float) * game_prt->num_sprite)))
		return (ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites = malloc(sizeof(t_coord) * game_prt->num_sprite)))
		return (ft_error_massage("Malloc error\n", 13));
	while (i < game_prt->num_sprite)
	{
		game_prt->sprites_num[i] = i;
		game_prt->sprites[i].x = parse_data->ft_sprite[i].x + 0.5;
		game_prt->sprites[i].y = parse_data->ft_sprite[i].y + 0.5;
		i++;
	}
	return (1);
}
void	ft_mlx_init(t_map *parse_data, t_person *parse_person)
{
	t_game	game_prt;

	game_prt.mlx = mlx_init();
	ft_position_player(&game_prt, parse_person);
	ft_init_img(&game_prt, parse_data, parse_person);
	ft_init_screen(&game_prt, parse_data);
	ft_print_map_p(parse_data, &game_prt);
	if (ft_init_sprites(&game_prt, parse_data) == -1)
		return;
	game_prt.screen.img = mlx_new_image(game_prt.mlx, game_prt.screen_width,
	 game_prt.screen_height);
	game_prt.screen.addr = mlx_get_data_addr(game_prt.screen.img, &game_prt.
	screen.bits_per_pixel, &game_prt.screen.line_length,
	&game_prt.screen.endian);
	ft_raycasting(&game_prt);
	mlx_put_image_to_window(game_prt.mlx, game_prt.mlx_win, game_prt.screen.img, 0, 0);
	mlx_hook(game_prt.mlx_win, 2, 1L<<0, ft_controller, &game_prt);
	mlx_loop(game_prt.mlx);
}
