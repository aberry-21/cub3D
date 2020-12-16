/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:03:45 by aberry            #+#    #+#             */
/*   Updated: 2020/12/16 18:30:12 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_creat_bmp_file_header(int fd, t_game *game_prt)
{
	unsigned char	file_header[14];
	int				size;

	ft_bzero(file_header, 14);
	size = 54 + 4 * game_prt->screen_height * game_prt->screen_width;
	file_header[0] = 'B';
	file_header[1] = 'M';
	file_header[2] = size;
	file_header[3] = size >> 8;
	file_header[4] = size >> 16;
	file_header[5] = size >> 24;
	file_header[10] = 54;
	if ((write(fd, file_header, 14)) == -1)
		exit(0);
}

void	ft_creat_bmp_info_header(int fd, t_game *game_prt)
{
	unsigned char	info_header[40];
	int				size_image;

	ft_bzero(info_header, 40);
	size_image = 4 * game_prt->screen_height * game_prt->screen_width;
	info_header[0] = 40;
	info_header[4] = game_prt->screen_width;
	info_header[5] = game_prt->screen_width >> 8;
	info_header[6] = game_prt->screen_width >> 16;
	info_header[7] = game_prt->screen_width >> 24;
	info_header[8] = game_prt->screen_height;
	info_header[9] = game_prt->screen_height >> 8;
	info_header[10] = game_prt->screen_height >> 16;
	info_header[11] = game_prt->screen_height >> 24;
	info_header[12] = 1;
	info_header[14] = game_prt->screen.bits_per_pixel;
	info_header[20] = size_image;
	if ((write(fd, info_header, 40)) == -1)
		exit(0);
}

void	ft_write_image_to_bmp(int fd, t_game *game_prt)
{
	int				y;
	int				x;
	unsigned char	byte[4];

	y = game_prt->screen_height;
	while (--y >= 0)
	{
		x = -1;
		while (++x < game_prt->screen_width)
		{
			byte[0] = (unsigned char)get_b(get_color(game_prt->screen, x, y));
			byte[1] = (unsigned char)get_g(get_color(game_prt->screen, x, y));
			byte[2] = (unsigned char)get_r(get_color(game_prt->screen, x, y));
			byte[3] = (unsigned char)get_t(get_color(game_prt->screen, x, y));
			if ((write(fd, byte, 4)) == -1)
				exit(0);
		}
	}
}

void	ft_creat_bmp(t_game *game_prt)
{
	int	fd;

	fd = open("Screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_error_massage("Open error\n", 11);
		exit(0);
	}
	ft_creat_bmp_file_header(fd, game_prt);
	ft_creat_bmp_info_header(fd, game_prt);
	ft_write_image_to_bmp(fd, game_prt);
	close(fd);
	exit(0);
}
