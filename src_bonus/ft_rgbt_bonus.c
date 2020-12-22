/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:12:04 by aberry            #+#    #+#             */
/*   Updated: 2020/12/20 15:58:00 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16)) / (256 * 256);
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8)) / 256;
}

int		get_b(int trgb)
{
	return (trgb & (0xFF << 0));
}

int		get_trgb(int t, int r, int g, int b)
{
	return ((t << 24 | r << 16 | g << 8 | b));
}
