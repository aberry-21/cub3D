/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:43:29 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 17:28:15 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdarg.h>
# include "../libft/libft.h"
# include "../mlx_mms/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/stat.h>
# define BASE_DEC "0123456789"
# define BASE_HEX "0123456789ABCDEF"

typedef struct		s_person
{
	char			ft_view;
	int				x;
	int				y;
}					t_person;

typedef struct		s_icoord
{
	int				x;
	int				y;
}					t_icoord;

typedef struct		s_map
{
	char			*ft_t_sprite;
	char			*ft_north;
	char			*ft_south;
	char			*ft_east;
	char			*ft_west;
	int				ft_floor;
	int				ft_ceilling;
	size_t			**ft_map;
	t_icoord		*ft_sprite;
	int				ft_width;
	int				ft_height;
	size_t			ft_width_mp;
	size_t			ft_height_mp;
	size_t			ft_size_arr_sp;
	int				bmp_bool;
}					t_map;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
	float			dark_cf;
}					t_img;

typedef struct		s_player
{
	float			pos_y;
	float			pos_x;
	float			dir_x;
	float			dir_y;
	float			plane_y;
	float			plane_x;
	float			move_speed;
	float			rot_speed;
}					t_player;

typedef struct		s_coord
{
	float			x;
	float			y;
}					t_coord;

typedef struct		s_raycast
{
	float			camera;
	t_coord			ray_dir;
	size_t			map_x;
	size_t			map_y;
	t_coord			dist;
	t_coord			delta_dist;
	float			dist_to_wall;
	t_icoord		step;
	int				side;
	float			*array_dist;
}					t_raycast;

typedef struct		s_game
{
	void			*mlx;
	void			*mlx_win;
	int				screen_width;
	int				screen_height;
	int				num_tex;
	int				color_floor;
	int				color_celling;
	float			x_texture;
	float			*sprites_dist;
	t_coord			*sprites;
	size_t			*sprites_num;
	size_t			num_sprite;
	t_img			screen;
	t_img			gun[2];
	t_img			sky_texture;
	t_img			sprite_texture;
	t_img			wall_texture[4];
	t_player		player;
	float			sky_offset;
	size_t			**map;
}					t_game;

typedef struct		s_raycast_sprite
{
	t_coord			sprite;
	float			proj_cf;
	int				sprite_screen;
	t_coord			transform;
	int				sprite_height;
	int				sprite_width;
	t_icoord		draw_start;
	t_icoord		draw_end;
}					t_raycast_sprite;

int					ft_error_massage(char *str, int count);
size_t				ft_size_width(char *line);
int					ft_counter_sprite(char *line);
int					ft_check_struct(t_map *map);
int					ft_cub_texture(char **str, char **map);
int					ft_create_hex(int t, int r, int g, int b);
int					ft_cub_color(char **str, int *map);
int					ft_atoi_cub(const char *str);
int					ft_check_value(char **str, int num);
int					ft_cub_resolution(char **str, t_map *map);
int					ft_cub_parse(char *line, t_map *map);
int					ft_cub_parse_1(char **str, t_map *map);
int					ft_cub_parse_2(char *line, t_map *map);
int					ft_cub_parse_3(char *line, t_map *map);
int					ft_cub_parse_valid(char *line);
int					ft_create_map(t_map *map);
int					ft_free_and_close(char *line, int fd, int error);
int					ft_parse_param(int *i, t_map *map, const char *argv);
int					ft_u_nums(int x, int y);
int					ft_greater(int x, int y);
int					ft_check_pr(t_map *map, int i, int j);
int					ft_check_char(t_map *map, int i, int j);
int					ft_check_map(t_map *map);
void				ft_init_map(t_map *map);
int					ft_valid_str_map(char *line);
int					ft_parse_map_support(char *line, t_map *map, t_person
*person, int ct[3]);
int					ft_parse_map(char *line, t_map *map, t_person *person);
int					ft_parse_map_full(int j, t_map *map, const char *argv,
t_person *person);
void				ft_mlx_init(t_map *parse_data, t_person *parse_person);
void				ft_init_img(t_game *game_prt, t_map *parse_data);
void				ft_init_img_sprite(t_game *game_prt, t_map *parse_data);
char				*ft_init_array_texture(int i, t_map *parse_data);
void				ft_position_player(t_game *game_prt, t_person
*parse_person);
void				ft_init_raycasting(t_game *game_prt, t_raycast *prt, int x);
void				ft_calc_step(t_game *game_prt, t_raycast *prt);
void				ft_calc_dist(t_game *game_prt, t_raycast *prt);
void				ft_dda_algorithm(t_game *game_prt, t_raycast *prt);
void				ft_choose_tex(t_game *game_prt, t_raycast *prt);
void				ft_raycasting(t_game *game_prt);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					get_trgb(int t, int r, int g, int b);
void				paint(t_game *game_prt, int line_height, int x);
float				ft_start_end(int *draw_start, int *draw_end, t_game
*game_prt, int line_height);
void				my_mlx_pixel_put(t_img *screen, int x, int y, int color);
void				paint_pixel(t_img *image, int x, int y, unsigned int color);
unsigned int		get_color(t_img tex, int x, int y);
void				ft_print_map(t_map *map);
void				ft_right_camera(t_game *game_prt);
void				ft_left_camera(t_game *game_prt);
int					ft_controller(int keycode, t_game *game_prt);
int					ft_check_world_map(size_t prt);
void				ft_forward(t_game *game_prt);
void				ft_back(t_game *game_prt);
void				ft_right(t_game *game_prt);
void				ft_left(t_game *game_prt);
void				ft_creat_bmp_file_header(int fd, t_game *game_prt);
void				ft_creat_bmp_info_header(int fd, t_game *game_prt);
void				ft_write_image_to_bmp(int fd, t_game *game_prt);
void				ft_creat_bmp(t_game *game_prt);
void				ft_param_player(t_game *game_prt, t_person *parse_person);
void				ft_position_player(t_game *game_prt,
t_person *parse_person);
void				ft_init_screen(t_game *game_prt, t_map *parse_data);
void				ft_swap_float(float *a, float *b);
void				ft_swap_int(size_t *a, size_t *b);
void				ft_sort_sprites(size_t *num, float *dist,
size_t size_array);
void				ft_sprite_x(t_raycast_sprite *prt, t_game *game_prt);
void				ft_sprites(t_raycast_sprite *prt, t_game *game_prt,
t_raycast *prt_wall);
void				ft_drawing_sprite(t_raycast_sprite *prt, t_game *game_prt,
t_raycast *prt_wall);
void				ft_drawing_sprites(t_game *game_prt, t_raycast *prt_wall);
void				ft_choose_tex(t_game *game_prt, t_raycast *prt);
void				ft_set_color_sprite(unsigned int color, t_game *game_prt,
int i, int j);
int					ft_close_window(int keycode, t_game *game_prt);
void				ft_drawing_gun(t_game *game_prt, int index);
void				paint_wall(t_game *game_prt, int x, int y, int j);
int					ft_create_rgb(int color, float cf);
void				ft_drawing_sky(t_game *game_prt, int x, int *y,
int draw_start);
void				ft_init_img_skybox(t_game *game_prt);
void				ft_init_img_gun(t_game *game_prt);
#endif
