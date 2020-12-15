/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_support_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:00:16 by aberry            #+#    #+#             */
/*   Updated: 2020/12/12 16:33:37 by olebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int		ft_init_mp_pr(t_map **map, t_person **person)
{
	if (!(*map = malloc(sizeof(t_map))))
		return (0);
	if (!(*person = malloc(sizeof(t_person))))
		return (0);
	ft_bzero((*map), sizeof(t_map));
	(*map)->ft_width = -1;
	(*map)->ft_height = -1;
	(*map)->ft_floor = -1;
	(*map)->ft_ceilling = -1;
	(*map)->ft_map = NULL;
	(*person)->x = -1;
	(*person)->y = -1;
	(*person)->ft_view = 0;
	return (1);
}

void	ft_clear_int(t_map *map, t_person *person)
{
	unsigned int	i;

	i = 0;
	while (i < map->ft_height_mp)
		free(map->ft_map[i++]);
	free(map->ft_map);
	if (person)
		free(person);
}

int		ft_free_exit(t_map *map, t_person *person)
{
	if (map)
	{
		if (map->ft_t_sprite)
			free(map->ft_t_sprite);
		if (map->ft_north)
			free(map->ft_north);
		if (map->ft_south)
			free(map->ft_south);
		if (map->ft_east)
			free(map->ft_east);
		if (map->ft_west)
			free(map->ft_west);
		if (map->ft_sprite)
			free(map->ft_sprite);
		if (map->ft_map)
			ft_clear_int(map, person);
		free(map);
	}
	return (0);
}
