/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:11:13 by aviau             #+#    #+#             */
/*   Updated: 2016/11/13 08:35:46 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
	if (r < 0 || g < 0 || b < 0)
		color = 0x000000;
	else
		color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

void	put_px(t_e *data, int x, int y)
{
	int	pos;

	if (x <= 0 || x >= 1200 || y <= 0 || y >= 1200)
		return ;
	pos = (x * data->bpp / 8) + (y * data->l_size);
	data->addr[pos] = data->color;
	data->addr[pos + 1] = (data->color >> 8);
	data->addr[pos + 2] = data->color >> 16;
}

/*t_color	col(t_draw *x, int i, t_e *d, int dd)
{
	t_color	c;

	c.start = d->r_e - ((d->r_e - d->r_s) / d->zmax * x->c);
	c.end = d->r_e - ((d->r_e - d->r_s) / d->zmax * x->c2);
	c.step = (c.end - c.start) / dd;
	c.r = c.start + i * c.step;
	c.start = d->g_e - ((d->g_e - d->g_s) / d->zmax * x->c);
	c.end = d->g_e - ((d->g_e - d->g_s) / d->zmax * x->c2);
	c.step = (c.end - c.start) / dd;
	c.g = c.start + i * c.step;
	c.start = d->b_e - ((d->b_e - d->b_s) / d->zmax * x->c);
	c.end = d->b_e - ((d->b_e - d->b_s) / d->zmax * x->c2);
	c.step = (c.end - c.start) / dd;
	c.b = c.start + i * c.step;
	return (c);
}*/


void	draw_line(t_e *data, int x, int y, int xx, int yy)
{
	float			dx;
	float			dy;
	unsigned int	dd;
	unsigned int	i;

	i = 0;
	dx = ((float)x < (float)xx) ? (float)xx - (float)x : (float)x - (float)xx;
	dy = ((float)y < (float)yy) ? (float)yy - (float)y : (float)y - (float)yy;
	dd = (dx > dy) ? dx : dy;
	dx = dd != 0 ? ((float)xx - (float)x) / dd : 1;
	dy = dd != 0 ? ((float)yy - (float)y) / dd : 1;
	data->color = 0x555555;
	while (i < dd)
	{
		put_px(data, x + (dx * i), y + (dy * i));
		i++;
	}
}
