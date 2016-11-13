/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 08:07:59 by aviau             #+#    #+#             */
/*   Updated: 2016/11/13 11:22:09 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#define X xy[0]
#define Y xy[1]
#define X2 xy[2]
#define Y2 xy[3]

float		ft_abs(float num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	draw_col(t_e *d, double lenght, int x, int or)
{
	int y;

	y = 0;
	while (y < 500)
	{
		if (ft_abs(y - 250) > lenght && y - 250 < 0)
			d->color = 0;
		else if (ft_abs(y - 250) > lenght && y - 250 >= 0)
		{
			d->color = (0x010101 * lenght);
		}
		else
			d->color = or ? 0xAAAAAA : 0xCCCCCC;
		put_px(d, x, y);
		y++;
	}
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
			put_px(d, x, y);
			x++;
		}
		y++;
	}
	d->color = 0xFFFFFF;
	put_px(d, sx, sy);
	put_px(d, sx, y);
	put_px(d, x, sy);
	put_px(d, x, y);
}

void	draw_map(t_e *d)
{
	int j;
	int i;
	int x;

	j = 0;
	while (j < d->jmax)
	{
		i = 0;
		while (i < d->imax)
		{
			if (d->grid[j][i] == 0)
				d->color = 0x222222;
			else
				d->color = 0x225522;
			draw_square(d, i * 50, j * 50 + 500, 50);
			i++;
		}
		j++;
	}
	float	angle;
	float	rad;
	int	 	lenght;
	int		Rx;
	int		Ry;
	int 	endX;
	int 	endY;

	angle = d->ang;
	d->color = 0xFFFF00;
	x = 0;
	while (x < 1200)
	{
		Rx = d->x;
		Ry = d->y;
		lenght = 1;
		rad = angle / 360.0f * (2.0f * 3.14159f);
		endX = (float)lenght * cos(rad) + (float)Rx;
		endY = (float)lenght * sin(rad) + (float)Ry;
		while (d->grid[endY / 50][endX / 50] == 0)
		{
			endX = (float)lenght * cos(rad) + (float)Rx;
			endY = (float)lenght * sin(rad) + (float)Ry;
  			put_px(d, endX, endY + 500);
			lenght++;
		}
		if (abs(endX - Rx) > abs(endY - Ry))
		{
//			lenght = abs(endY - Ry / 2);
			draw_col(d, 200 - lenght / 2, x, 0);
		}
		else
		{
//			lenght = abs(endX - Rx / 2);
			draw_col(d, 200 - lenght / 2, x, 1);
		}
		angle += 0.05;
		x++;
	}
	d->color = 0xFF0000;
	put_px(d, d->x, d->y + 500);
	put_px(d, d->x + 1, d->y + 500);
	put_px(d, d->x, d->y + 1 + 500);
	put_px(d, d->x - 1, d->y + 500);
	put_px(d, d->x, d->y - 1 + 500);
}
