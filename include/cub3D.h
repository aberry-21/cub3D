/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:43:29 by aberry            #+#    #+#             */
/*   Updated: 2020/12/15 18:57:03 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdarg.h>
# include "../libft/libft.h"
# include "../mlx_mms/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <sys/stat.h>
#define BASE_DEC "0123456789"
#define BASE_HEX "0123456789ABCDEF"
typedef struct	s_person
{
	char		ft_view;
	int			x;
	int			y;
}				t_person;

typedef struct	s_icoord
{
	int			x;
	int			y;
}				t_icoord;

typedef struct	s_map
{
	char		*ft_t_sprite;
	char		*ft_north;
	char		*ft_south;
	char		*ft_east;
	char		*ft_west;
	int			ft_floor;
	int			ft_ceilling;
	size_t		**ft_map;
	t_icoord	*ft_sprite;
	int			ft_width;
	int			ft_height;
	size_t		ft_width_mp;
	size_t		ft_height_mp;
	size_t		ft_size_arr_sp;
}				t_map;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;

}				t_img;


typedef struct	s_player
{
	float		pos_y;
	float		pos_x;
	float		dir_x;
	float		dir_y;
	float		plane_y;
	float		plane_x;
	float		move_speed;
	float		rot_speed;
}				t_player;

typedef struct	s_sprites
{

}				t_sprites;

typedef struct	s_coord
{
	float		x;
	float		y;
}				t_coord;

typedef struct	s_raycast
{
	float		camera;
	t_coord		ray_dir;
	size_t		map_x;
	size_t		map_y;
	t_coord		dist;
	t_coord		delta_dist;
	float		dist_to_wall;
	t_icoord	step;
	int			side;
	float		*array_dist;
}				t_raycast;

typedef struct	s_game
{
	void		*mlx;
	void		*mlx_win;
	int			screen_width;
	int			screen_height;
	int			num_tex;
	int			color_floor;
	int			color_celling;
	float		x_texture;
	float		*sprites_dist;
	t_coord		*sprites;
	size_t		*sprites_num;
	size_t		num_sprite;
	t_img		screen;
	t_img		sky_texture;
	t_img		sprite_texture;
	t_img		wall_texture[4];
	t_player	player;
	size_t		**map;
}				t_game;



/*
**--------------------------->>>>Parse_param<<<<-------------------------------
**
** ft_cub_parse_utils.c
*/
int		ft_error_massage(char *str, int count);
size_t	ft_size_width(char *line);
int		ft_counter_sprite(char *line);
int		ft_check_struct(t_map *map);
/*
** ft_cub_cl_tex_for_parse.c
*/
int		ft_cub_texture(char **str, char **map);
int		ft_create_hex(int t, int r, int g, int b);
int		ft_cub_color(char **str, int *map);
/*
** ft_cub_resolution_for_parse.c
*/
int		ft_atoi_cub(const char *str);
int		ft_check_value(char **str, int num);
int		ft_cub_resolution(char **str, t_map *map);
/*
** ft_cub_parse.c
*/
int		ft_cub_parse(char *line, t_map *map);
int		ft_cub_parse_1(char **str, t_map *map);
int		ft_cub_parse_2(char *line, t_map *map);
int		ft_cub_parse_3(char *line, t_map *map);
int		ft_cub_parse_valid(char *line);
/*
** ft_parse_param.c 
*/
int		ft_create_map(t_map *map);
int		ft_free_and_close(char *line, int fd, int error);
int		ft_parse_param(int *i, t_map *map, const char *argv);
/*
**-----------------------------------------------------------------------------
*/

/*
**---------------------------->>>>Parse_map<<<<--------------------------------
**
** ft_check_map.c
*/
int		ft_u_nums(int x, int y);
int		ft_greater(int x, int y);
int		ft_check_pr(t_map *map, int i, int j);
int		ft_check_char(t_map *map, int i, int j);
int		ft_check_map(t_map *map);

/*
** ft_parse_param.c
*/
void	ft_init_map(t_map *map);
int		ft_valid_str_map(char *line);
int		ft_parse_map_support(char *line, t_map *map, t_person *person, int ct[3]);
int		ft_parse_map(char *line, t_map *map, t_person *person);
int		ft_parse_map_full(int j, t_map *map, const char *argv, t_person *person);
/*
**-----------------------------------------------------------------------------
*/


/*
** ft_init_mlx.c
*/
void 	ft_mlx_init(t_map *parse_data, t_person *parse_person);
void	ft_init_img(t_game *game_prt,t_map *parse_data);
void	ft_init_img_sprite(t_game *game_prt,t_map *parse_data);
char	*ft_init_array_texture(int i, t_map *parse_data);
void	ft_position_player(t_game *game_prt, t_person *parse_person);
/*
**-----------------------------------------------------------------------------
*/
void	ft_init_raycasting(t_game *game_prt, t_raycast *prt, int x);
void	ft_calc_step(t_game *game_prt, t_raycast *prt);
void	ft_calc_dist(t_game *game_prt, t_raycast *prt);
void	ft_dda_algorithm(t_game *game_prt, t_raycast *prt);
void	ft_choose_tex(t_game *game_prt, t_raycast *prt);//!!!;
void	ft_raycasting(t_game *game_prt);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		get_trgb(int t, int r, int g, int b);
void	paint(t_game *game_prt, int line_height, int x);
float			ft_start_end(int *draw_start, int *draw_end, t_game *game_prt, int line_height);
void	my_mlx_pixel_put(t_img *screen, int x, int y, int color);
void				paint_pixel(t_img *image, int x, int y, unsigned int color);
unsigned int		get_color(t_img tex, int x, int y);
void	ft_print_map(t_map *map);



/*
** ft_controller.c
*/
void	ft_right_camera(t_game *game_prt);
void	ft_left_camera(t_game *game_prt);
int		ft_controller(int keycode, t_game *game_prt);
/*
**-----------------------------------------------------------------------------
*/


/*
** ft_controller_player.c
*/
int		ft_check_world_map(size_t prt);
void	ft_forward(t_game *game_prt);
void	ft_back(t_game *game_prt);
void	ft_right(t_game *game_prt);
void	ft_left(t_game *game_prt);
/*
**-----------------------------------------------------------------------------
*/
#endif