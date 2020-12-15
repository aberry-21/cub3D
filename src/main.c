/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:14:34 by aberry            #+#    #+#             */
/*   Updated: 2020/12/15 19:15:05 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->ft_height_mp)
	{
		j = 0;
		while (j < map->ft_width_mp)
		{
			printf("%lu",map->ft_map[i][j]);
			j++;

		}
		printf("\n");
		i++;
	}
}

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

int main(int argc, char const *argv[])
{
	(void)argc;
	t_map		*map;
	t_person	*person;
	int			i;
	int			error;


	error = 0;
	i = 0;
	if (!(ft_init_mp_pr(&map, &person)) || argc < 2 || argc > 3)
		exit(0);
	if (argc == 3)
	{
		if (ft_strncmp("--save",argv[2], 7))
			exit(0);
		
	}
	error = ft_parse_param(&i, map, argv[1]);
	if (error == -1 || (error = ft_parse_map_full((i - map->ft_height_mp),
	map, argv[1], person)) == -1)
		exit(0);
	ft_mlx_init(map, person);
	return (0);
}
