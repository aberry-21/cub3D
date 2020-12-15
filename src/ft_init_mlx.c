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






void	ft_init_screen(t_game *game_prt,t_map *parse_data)
{
	int	screen_width;
	int	screen_height;
	game_prt->screen_width = parse_data->ft_width;
	game_prt->screen_height = parse_data->ft_height;
	mlx_get_screen_size(game_prt, &screen_width, &screen_height);
	if (game_prt->screen_width  > screen_width)
		game_prt->screen_width = screen_width;
	if (game_prt->screen_height  > screen_height)
		game_prt->screen_height = screen_height;
	game_prt->map = parse_data->ft_map;
	game_prt->color_celling = parse_data->ft_ceilling;
	game_prt->color_floor = parse_data->ft_floor;
	if (!(game_prt->screen.img = mlx_new_image(game_prt->mlx, game_prt->screen_width,
	game_prt->screen_height)))
		exit(0);
	game_prt->screen.addr = mlx_get_data_addr(game_prt->screen.img, &game_prt->
	screen.bits_per_pixel, &game_prt->screen.line_length,
	&game_prt->screen.endian);
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

void	ft_init_img_sprite(t_game *game_prt,t_map *parse_data)
{

	if (!(game_prt->sprite_texture.img = mlx_xpm_file_to_image(\
	game_prt->mlx, ft_init_array_texture(4, parse_data),\
	&game_prt->sprite_texture.img_width,\
	&game_prt->sprite_texture.img_height)))
		exit(0);
	game_prt->sprite_texture.addr = mlx_get_data_addr(\
	game_prt->sprite_texture.img,\
	&game_prt->sprite_texture.bits_per_pixel,\
	&game_prt->sprite_texture.line_length,\
	&game_prt->sprite_texture.endian);
}
void	ft_init_img(t_game *game_prt,t_map *parse_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(game_prt->wall_texture[i].img = mlx_xpm_file_to_image(\
		game_prt->mlx, ft_init_array_texture(i, parse_data),\
		&game_prt->wall_texture[i].img_width,\
		&game_prt->wall_texture[i].img_height)))
			exit(0);
		game_prt->wall_texture[i].addr = mlx_get_data_addr(\
		game_prt->wall_texture[i].img,\
		&game_prt->wall_texture[i].bits_per_pixel,\
		&game_prt->wall_texture[i].line_length,\
		&game_prt->wall_texture[i].endian);
		i++;
	}
	ft_init_img_sprite(game_prt, parse_data);
}



void	ft_init_sprites(t_game *game_prt, t_map *parse_data)
{
	int i;

	i = 0;
	game_prt->num_sprite = parse_data->ft_size_arr_sp;
	if (!(game_prt->sprites_num = malloc(sizeof(size_t) * game_prt->num_sprite)))
		exit (ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites_dist = malloc(sizeof(float) * game_prt->num_sprite)))
		exit (ft_error_massage("Malloc error\n", 13));
	if (!(game_prt->sprites = malloc(sizeof(t_coord) * game_prt->num_sprite)))
		exit (ft_error_massage("Malloc error\n", 13));
	while (i < game_prt->num_sprite)
	{
		game_prt->sprites_num[i] = i;
		game_prt->sprites[i].x = parse_data->ft_sprite[i].x + 0.5;
		game_prt->sprites[i].y = parse_data->ft_sprite[i].y + 0.5;
		i++;
	}
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
	ft_raycasting(&game_prt);
	//printf("%d\n", (game_prt.screen_width * game_prt.screen.bits_per_pixel / 8) * game_prt.screen_height);
	// printf("%d\n", (game_prt.screen_width + game_prt.screen.bits_per_pixel % 8));
	// printf("%d\n", (game_prt.screen_width * game_prt.screen.bits_per_pixel / 8));
	// //printf("%d\n", (4 - (game_prt.screen_width * game_prt.screen.bits_per_pixel / 8) % 4) % 4);
	// exit(0);
	// //0000 0101 0000 0000
	// //0000 0000 0000 0101
	// printf("%lu\n", sizeof(int));
	// printf("%d\n", 2147483647>>  8);
	// printf("%d\n", 2147483647>> 16);
	// printf("%d\n", 2147483647>> 24);
	exit(0);
	if (!(game_prt.mlx_win = mlx_new_window(game_prt.mlx, game_prt.screen_width,\
	game_prt.screen_height, "Cub3D")))
		exit(0);
	mlx_put_image_to_window(game_prt.mlx, game_prt.mlx_win, game_prt.screen.img, 0, 0);
	mlx_hook(game_prt.mlx_win, 2, 1L<<0, ft_controller, &game_prt);
	mlx_loop(game_prt.mlx);
}


// // 4 * game_prt.screen_width * game_prt.screen_height;
// const int BYTES_PER_PIXEL = 3; /// red, green, & blue
// const int FILE_HEADER_SIZE = 14;
// const int INFO_HEADER_SIZE = 40;

// void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
// unsigned char* createBitmapFileHeader(int height, int stride);
// unsigned char* createBitmapInfoHeader(int height, int width);


// int main ()
// {
//     int height = 361;
//     int width = 867;
//     unsigned char image[height][width][BYTES_PER_PIXEL];
//     char* imageFileName = (char*) "bitmapImage.bmp";

//     int i, j;
//     for (i = 0; i < height; i++) {
//         for (j = 0; j < width; j++) {
//             image[i][j][2] = (unsigned char) ( i * 255 / height );             ///red
//             image[i][j][1] = (unsigned char) ( j * 255 / width );              ///green
//             image[i][j][0] = (unsigned char) ( (i+j) * 255 / (height+width) ); ///blue
//         }
//     }

//     generateBitmapImage((unsigned char*) image, height, width, imageFileName);
//     printf("Image generated!!");
// }

// void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
// {
//     int widthInBytes = width * BYTES_PER_PIXEL;

//     unsigned char padding[3] = {0, 0, 0};
//     int paddingSize = (4 - (widthInBytes) % 4) % 4;

//     int stride = (widthInBytes) + paddingSize;

//     FILE* imageFile = fopen(imageFileName, "wb");

//     unsigned char* fileHeader = createBitmapFileHeader(height, stride);
//     fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

//     unsigned char* infoHeader = createBitmapInfoHeader(height, width);
//     fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

//     int i;
//     for (i = 0; i < height; i++) {
//         fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
//         fwrite(padding, 1, paddingSize, imageFile);
//     }

//     fclose(imageFile);
// }

// unsigned char* createBitmapFileHeader (int height, int stride)
// {
//     int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

//     static unsigned char fileHeader[] = {
//         0,0,     /// signature
//         0,0,0,0, /// image file size in bytes
//         0,0,0,0, /// reserved
//         0,0,0,0, /// start of pixel array
//     };

//     fileHeader[ 0] = (unsigned char)('B');
//     fileHeader[ 1] = (unsigned char)('M');
//     fileHeader[ 2] = (unsigned char)(fileSize      );
//     fileHeader[ 3] = (unsigned char)(fileSize >>  8);
//     fileHeader[ 4] = (unsigned char)(fileSize >> 16);
//     fileHeader[ 5] = (unsigned char)(fileSize >> 24);
//     fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

//     return fileHeader;
// }

// unsigned char* createBitmapInfoHeader (int height, int width)
// {
//     static unsigned char infoHeader[] = {
//         0,0,0,0, /// header size
//         0,0,0,0, /// image width
//         0,0,0,0, /// image height
//         0,0,     /// number of color planes
//         0,0,     /// bits per pixel
//         0,0,0,0, /// compression
//         0,0,0,0, /// image size
//         0,0,0,0, /// horizontal resolution
//         0,0,0,0, /// vertical resolution
//         0,0,0,0, /// colors in color table
//         0,0,0,0, /// important color count
//     };

//     infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
//     infoHeader[ 4] = (unsigned char)(width      );
//     infoHeader[ 5] = (unsigned char)(width >>  8);
//     infoHeader[ 6] = (unsigned char)(width >> 16);
//     infoHeader[ 7] = (unsigned char)(width >> 24);
//     infoHeader[ 8] = (unsigned char)(height      );
//     infoHeader[ 9] = (unsigned char)(height >>  8);
//     infoHeader[10] = (unsigned char)(height >> 16);
//     infoHeader[11] = (unsigned char)(height >> 24);
//     infoHeader[12] = (unsigned char)(1);
//     infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

//     return infoHeader;
// }