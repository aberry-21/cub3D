/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_parse_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:19:36 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 15:57:33 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int		ft_error_massage(char *str, int count)
{
	char	*error;

	error = "Error\n";
	write(2, error, 6);
	write(2, str, count);
	exit(0);
}

size_t	ft_size_width(char *line)
{
	size_t		size;
	size_t		i;
	char		*str;

	size = ft_strlen(line);
	i = 0;
	str = ft_strrchr(line, '1');
	str++;
	while (str[i])
	{
		if (str[i++] != ' ')
			return (ft_error_massage("No valid map\n", 13));
	}
	return (size - i);
}

int		ft_counter_sprite(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == '2')
			i++;
		line++;
	}
	return (i);
}

int		ft_check_struct(t_map *map)
{
	if (!map->ft_t_sprite || map->ft_width == -1 || map->ft_height == -1)
		return (1);
	if ((!map->ft_north) || (!map->ft_east) || (!map->ft_south))
		return (1);
	if ((map->ft_floor == -1) || (map->ft_ceilling == -1) || (!map->ft_west))
		return (1);
	return (0);
}
