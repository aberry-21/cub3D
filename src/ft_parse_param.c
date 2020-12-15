/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:23:54 by aberry            #+#    #+#             */
/*   Updated: 2020/12/11 18:58:56 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
**--------------------------->>>>ft_parse_param<<<<----------------------------
** " > " - Вход в функцию
**-----------------------------------------------------------------------------
** Открываем файл и читаем построчно пока файл не будет считан полностью или
** в процессе валидации не возникла ошибка.
**-----------------------------------------------------------------------------
** После цикла очищаем память под последнюю считанную строку и или выходим в
** случае ошибки или парсим эту строку
**-----------------------------------------------------------------------------
** Далее проверяем была ли вообще дана картра, если да, то алоцируем память под
** двумерный массив инт (для карты) и алоцируем память под массив айтомов
**-----------------------------------------------------------------------------
** PS i - количество строк - 1
**-----------------------------------------------------------------------------
*/

void	ft_init_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->ft_height_mp + 1)
	{
		j = 0;
		while (j < map->ft_width_mp + 1)
		{
			map->ft_map[i][j] = 0;
			j++;
		}
		i++;
	}
}

int		ft_create_map(t_map *map)
{
	size_t	i;

	i = 0;
	if (!(map->ft_sprite = malloc(sizeof(t_icoord) * map->ft_size_arr_sp)))
		return (ft_error_massage("Malloc error\n", 13));
	if (!(map->ft_map = malloc(sizeof(size_t) * (map->ft_height_mp + 1))))
		return (ft_error_massage("Malloc error\n", 13));
	while (i < map->ft_height_mp + 1)
	{
		if (!(map->ft_map[i] = malloc(sizeof(size_t) * (map->ft_width_mp + 1))))
			return (ft_error_massage("Malloc error\n", 13));
		i++;
	}
	ft_init_map(map);
	return (0);
}

int	ft_free_and_close(char *line, int fd, int error)
{
	free(line);
	close(fd);
	return (error);
}

int		ft_parse_param(int *i, t_map *map, const char *argv)
{
	char		*line;
	int			error;
	int			fd;

	if ((fd = open(argv, O_RDONLY)) == -1)
		return(ft_error_massage("Open error\n", 11));
	while ((get_next_line(fd, &line)) > 0 && (error = ft_cub_parse(line, map))
	!= -1)
	{
		(*i)++;
		free(line);
		//printf("%lu", map->ft_height_mp);
	}
	if (error == -1 || (error = ft_cub_parse(line, map)) == -1)
		return (ft_free_and_close(line, fd, error));
	if (!map->ft_width_mp || !map->ft_height_mp)
		error = (ft_error_massage("No valid map\n", 13));
	else
		error = ft_create_map(map);
	if (error == -1)
	{
		printf("parse_map");
		ft_print_map(map);
	}
	return (ft_free_and_close(line, fd, error));
}
