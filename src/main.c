/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olebedev <olebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:14:34 by aberry            #+#    #+#             */
/*   Updated: 2020/12/11 18:59:11 by olebedev         ###   ########.fr       */
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

int main(int argc, char const *argv[])
{
	(void)argc;
	t_map		*map;
	t_person	*person;
	int			i;
	int			error;


	error = 0;
	i = 0;
	if (!(ft_init_mp_pr(&map, &person)))
		exit((-ft_error_massage("Malloc error\n", 13)));
	error = ft_parse_param(&i, map, argv[1]);
	if (error == -1 || (error = ft_parse_map_full((i - map->ft_height_mp),
	map, argv[1], person)) == -1)
		return(ft_free_exit(map, person));//and free!!
	// printf("%d\n", map->ft_height);
	// printf("%d\n", map->ft_width);
	// printf("%s\n", map->ft_north);
	// printf("%s\n", map->ft_south);
	// printf("%s\n", map->ft_west);
	// printf("%s\n", map->ft_east);
	// printf("%s\n", map->ft_t_sprite);
	// printf("%d\n", map->ft_floor);
	// printf("%d\n", map->ft_ceilling);
	// printf("%lu\n", map->ft_height_mp);
	// printf("%lu\n", map->ft_width_mp);
	// printf("%lu\n", map->ft_size_arr_sp);
	// printf("%d\n", person->x);
	// printf("%d\n", person->y);
	// printf("|%c|\n", person->ft_view);
	// ft_print_map(map);
	ft_mlx_init(map, person);
	return (ft_free_exit(map, person));
}
