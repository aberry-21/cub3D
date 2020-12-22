/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_resolution_for_parse_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:24:35 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 15:57:36 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*
**--------------------------->>>>ft_cub_resolution<<<<-------------------------
** " > " - Вход в функцию
**-----------------------------------------------------------------------------
** Вызываем ft_check_value и проверяем что данные map еще не были заполнены.
** > Проверяет сколько подстрок в строке и возвращает 0 в случае невалидности.
** ----------------------------------------------------------------------------
** Вызываем ft_atoi_cub и заполняем поля структуры.
** > Если после числа не стоит \0 значит число невалидное.
** ----------------------------------------------------------------------------
** С помощью макроса проверяем что размеры окна больше чем 50 на 50.
** ----------------------------------------------------------------------------
*/

int	ft_atoi_cub(const char *str)
{
	int		num;
	int		i;

	num = ft_atoi(str);
	i = 0;
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	if (str[i])
		return (-1);
	return (num);
}

int	ft_check_value(char **str, int num)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	num = (i != num) ? 0 : 1;
	return (num);
}

int	ft_cub_resolution(char **str, t_map *map)
{
	if (!ft_check_value(str, 3) || map->ft_width != -1 || map->ft_height != -1)
		return (ft_error_massage("No valid resolution\n", 20));
	if (((map->ft_width = ft_atoi_cub(str[1])) == -1)
	|| ((map->ft_height = ft_atoi_cub(str[2])) == -1))
		return (ft_error_massage("No valid resolution\n", 20));
	if (!ft_u_nums(map->ft_width, map->ft_height))
		return (ft_error_massage("Window <= 500x500\n", 18));
	return (0);
}
