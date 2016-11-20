/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:07:28 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 07:58:53 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
#include <stdio.h>

void	put_px_t(t_e *d, int x, int y)
{
	int	pos;

	if (x <= 0 || x >= WSIZE || y <= 0 || y >= HSIZE)
		return ;
	pos = (x * d->bpp / 8) + (y * d->l_size);
	d->addr[pos + 0] = (char)((uint8_t)d->addr[pos + 0] + \
		(d->c.b - (uint8_t)d->addr[pos + 0]) * (d->c.ratio / 100.0f));
	d->addr[pos + 1] = (char)((uint8_t)d->addr[pos + 1] + \
		(d->c.g - (uint8_t)d->addr[pos + 1]) * (d->c.ratio / 100.0f));
	d->addr[pos + 2] = (char)((uint8_t)d->addr[pos + 2] + \
		(d->c.r - (uint8_t)d->addr[pos + 2]) * (d->c.ratio / 100.0f));
}

void	draw_square(t_e *d, int sx, int sy, int size)
{
	int x;
	int y;

	y = sy;
	while (y < sy + size)
	{
		x = sx;
		while (x < sx + size)
		{
			put_px_t(d, x, y);
			x++;
		}
		y++;
	}
}

t_color	give_col(int wall, int light)
{
	static int	col[3][13] = {
		{0, 120, 173, 114, 208, 255, 255, 255, 0, 0, 0, 255, 255},
		{123, 100, 153, 92, 191, 0, 170, 255, 255, 255, 0, 0, 255},
		{12, 70, 107, 41, 152, 0, 0, 0, 0, 255, 255, 255, 255}};
	t_color		c;

	c.r = 255;
	c.g = 255;
	c.b = 255;
	if (abs(wall) < 13)
	{
		c.r = col[0][abs(wall)];
		c.g = col[1][abs(wall)];
		c.b = col[2][abs(wall)];
	}
	if (wall == 0)
		c.ratio = (25 - light / 2) > 0 ? 25 - light / 2 : 0;
	else
		c.ratio = (75 - light / 2) > 0 ? 75 - light / 2 : 0;
	return (c);
}

void	minimap(t_e *d)
{
	int			i;
	int			j;

	j = -1;
	while (++j < d->jmax)
	{
		i = -1;
		while (++i < d->imax)
		{
			d->c = give_col(d->grid[j][i], d->l);
			draw_square(d, i * 5, j * 5, 5);
		}
	}
	d->c.r = 0;
	d->c.ratio = 100;
	draw_square(d, (d->rc.posy) * 5 - 1.5, (d->rc.posx) * 5 - 1.5, 3);
	d->c.r = 255;
	draw_square(d, (d->rc.posy - 0.25 + d->rc.diry) * 5, \
		(d->rc.posx - 0.25 + d->rc.dirx) * 5, 2);
}
