/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:14:34 by aberry            #+#    #+#             */
/*   Updated: 2020/12/16 18:30:12 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_init_mp_pr(t_map **map, t_person **person)
{
	if (!(*map = malloc(sizeof(t_map))))
		ft_error_massage("Malloc error\n", 13);
	if (!(*person = malloc(sizeof(t_person))))
		ft_error_massage("Malloc error\n", 13);
	ft_bzero((*map), sizeof(t_map));
	(*map)->ft_width = -1;
	(*map)->ft_height = -1;
	(*map)->ft_floor = -1;
	(*map)->ft_ceilling = -1;
	(*map)->ft_map = NULL;
	(*person)->x = -1;
	(*person)->y = -1;
	(*person)->ft_view = 0;
}

int			main(int argc, char const *argv[])
{
	t_map		*map;
	t_person	*person;
	int			i;
	int			error;

	error = 0;
	i = 0;
	ft_init_mp_pr(&map, &person);
	if (argc < 2 || argc > 3)
		ft_error_massage("No valid argc\n", 14);
	if (argc == 3)
	{
		if (ft_strncmp("--save", argv[2], 7))
			ft_error_massage("No valid \"save\"\n", 16);
		map->bmp_bool = 1;
	}
	error = ft_parse_param(&i, map, argv[1]);
	if (error == -1 || (error = ft_parse_map_full((i - map->ft_height_mp),
	map, argv[1], person)) == -1)
		exit(0);
	ft_mlx_init(map, person);
	return (0);
}
