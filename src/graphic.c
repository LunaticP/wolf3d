/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:11:13 by aviau             #+#    #+#             */
/*   Updated: 2016/11/19 14:29:45 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

int		get_color(int r, int g, int b)
{
	int color;

	if (r > 255 || g > 255 || b > 255)
	{
		r = (r > 255) ? 255 : r;
		g = (g > 255) ? 255 : g;
		b = (b > 255) ? 255 : b;
	}
	else if (r < 0 || g < 0 || b < 0)
	{
		r = (r < 0) ? 0 : r;
		g = (g < 0) ? 0 : g;
		b = (b < 0) ? 0 : b;
	}
	color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

void	put_px(t_e *data, int x, int y)
{
	int	pos;

	if (x <= 0 || x >= WSIZE || y <= 0 || y >= HSIZE)
		return ;
	pos = (x * data->bpp / 8) + (y * data->l_size);
	data->addr[pos] = data->color;
	data->addr[pos + 1] = (data->color >> 8);
	data->addr[pos + 2] = data->color >> 16;
}
