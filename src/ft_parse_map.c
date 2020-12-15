/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:53:44 by aberry            #+#    #+#             */
/*   Updated: 2020/12/10 00:01:02 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
**--------------------------->>>>ft_parse_map<<<<------------------------------
** " > " - Вход в функцию
** empty = 0;
** wall = 7;
** pool = 8;
** person = 9;
** sprite = 2;
** ----------------------------------------------------------------------------
** Открываем файл и читаем построчно, как только мы дошли до начала карты
** вызывается ft_parse_map()
** ----------------------------------------------------------------------------
** > Создаем одномерный статический массив счетчиков
** > i = ct[0]
** > k = ct[1]
** > j = ct[2]
** > Статические тк функция вызывается каждый раз при считывании функции
** > Вызывается ft_valid_str_map() результат которой присваивается j
** > j = 0 если валидацию строка прошла и -1 если не прошла
** ----------------------------------------------------------------------------
** >> Функция проверят первый символ отличный от пробела
** >> Если это не единица то карта не валидна
** ----------------------------------------------------------------------------
** > Далее если встретились символы "NSWE02" (игрока, пола, спрайтов)
** > вызывается ft_parse_map_support()
** ----------------------------------------------------------------------------
** >> Если встретили 0(пол) то заполняем элемент карты 8
** >> Если встретили 2(спрайт) то заполняем элемент карты 2 и заполняем массив
** >> спрайтов (первому элементу прописываем х и у а передвигаем счетчик на 1)
** >> Если встретили "NSWE"(игрок) то заполняем элемент карты 9 и структуру
** >> person
** >> И проверяем что игрок встретился один раз
** ----------------------------------------------------------------------------
** > Если встретили стену(1) то аполняем элемент карты 7
** > Если встретили символ отличный от пробела то карта невалидна
** Проверяем на ошибки и если их нет вызываем ft_check_map()
** ----------------------------------------------------------------------------
*/

int	ft_valid_str_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (ft_error_massage("No valid map\n", 13));
	return (0);
}

int	ft_parse_map_support(char *line, t_map *map, t_person *person, int ct[3])
{
	if (line[ct[2]] == '0')
		map->ft_map[ct[0]][ct[2]] = 8;
	else if (line[ct[2]] == '2')
	{
		map->ft_map[ct[0]][ct[2]] = 2;
		map->ft_sprite[ct[1]].x = ct[2];
		map->ft_sprite[ct[1]++].y = ct[0];
	}
	else
	{
		map->ft_map[ct[0]][ct[2]] = 9;
		if (person->ft_view)
			return (ft_error_massage("No valid map\n", 13));
		person->ft_view = line[ct[2]];
		person->x = ct[2];
		person->y = ct[0];
	}
	return (0);
}

int	ft_parse_map(char *line, t_map *map, t_person *person)
{
	static int	ct[3];

	if ((ct[2] = ft_valid_str_map(line)) == -1)
		return (-1);
	while (line[ct[2]])
	{
		if (ft_strchr("NSWE02", line[ct[2]]))
		{
			if (ft_parse_map_support(line, map, person, ct) == -1)
				return (-1);
		}
		else if (line[ct[2]] == '1')
			map->ft_map[ct[0]][ct[2]] = 7;
		else if (line[ct[2]] != ' ')
			return (ft_error_massage("No valid map\n", 13));
		ct[2]++;
	}
	ct[0]++;
	return (0);
}

int	ft_parse_map_full(int j, t_map *map, const char *argv, t_person *person)
{
	int			fd;
	int			i;
	int			error;
	char		*line;

	i = 0;
	fd = open(argv, O_RDONLY);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (i > j)
			if ((error = ft_parse_map(line, map, person)) == -1)
				break ;
		i++;
		free(line);
	}
	if (error == -1 || (error = ft_parse_map(line, map, person)) == -1)
		return (ft_free_and_close(line, fd, error));
	if (!person->ft_view)
		error = (ft_error_massage("No valid map\n", 13));
	else
		error = ft_check_map(map);
	if (error == -1)
	{
		printf("parse_map");
		ft_print_map(map);
	}
	return (ft_free_and_close(line, fd, error));
}
