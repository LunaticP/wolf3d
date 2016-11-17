/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:30:43 by aviau             #+#    #+#             */
/*   Updated: 2016/11/17 22:53:14 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	draw_col(t_e *d, int x, int drawstart, int drawend, int color)
{
	int y;

	y = 0;
	while (y < 1200)
	{
		if (y < drawstart)
			d->color = get_color(0xCD + y / 10, 0xF9 + y / 10, 255);
		else if (y >= drawstart && y <= drawend)
			d->color = color;
		else
			d->color = 0x007B0C;
		put_px(d, x, y);
		y++;
	}
}

void	init_wlf(t_e *d, int x)
{
	d->rc.camerax = 2 * x / 1200.0 - 1;
	d->rc.rayposx = d->rc.posx;
	d->rc.rayposy = d->rc.posy;
	d->rc.raydirx = d->rc.dirx + d->rc.planex * d->rc.camerax;
	d->rc.raydiry = d->rc.diry + d->rc.planey * d->rc.camerax;
	d->rc.deltadistx = sqrt(1 + (d->rc.raydiry * d->rc.raydiry) \
			/ (d->rc.raydirx * d->rc.raydirx));
	d->rc.deltadisty = sqrt(1 + (d->rc.raydirx * d->rc.raydirx) \
			/ (d->rc.raydiry * d->rc.raydiry));
}

void	init_step_side(t_e *d, t_wmap *w)
{
	if (d->rc.raydirx < 0)
	{
		w->stepx = -1;
		d->rc.sidedistx = (d->rc.rayposx - w->mapx) * d->rc.deltadistx;
	}
	else
	{
		w->stepx = 1;
		d->rc.sidedistx = (w->mapx + 1.0 - d->rc.rayposx) * d->rc.deltadistx;
	}
	if (d->rc.raydiry < 0)
	{
		w->stepy = -1;
		d->rc.sidedisty = (d->rc.rayposy - w->mapy) * d->rc.deltadisty;
	}
	else
	{
		w->stepy = 1;
		d->rc.sidedisty = (w->mapy + 1.0 - d->rc.rayposy) * d->rc.deltadisty;
	}
}

int		wall_color(int w_val, int side, int len)
{
	static int	col_p[3][12] = {
		{5, 120, 173, 114, 208, 255, 255, 255, 0, 0, 0, 255},
		{5, 100, 153, 92, 191, 0, 170, 255, 255, 255, 0, 0},
		{5, 70, 107, 41, 152, 0, 0, 0, 0, 255, 255, 255}};
	t_color		c;

	(void)w_val;
	if (w_val >= 11)
		c.color = 0xFFFFFF;
	else
	{
		c.r = col_p[0][w_val] - (side * 10) - len;
		c.g = col_p[1][w_val] - (side * 10) - len;
		c.b = col_p[2][w_val] - (side * 10) - len;
		c.r = c.r < 0 ? 0 : c.r;
		c.g = c.g < 0 ? 0 : c.g;
		c.b = c.b < 0 ? 0 : c.b;
		c.color = get_color(c.r, c.g, c.b);
	}
	return (c.color);
}

void	draw_map(t_e *d)
{
	int		x;
	t_wmap	w;

	x = 0;
	while (x < 1200)
	{
		init_wlf(d, x);
		w.mapx = (int)d->rc.rayposx;
		w.mapy = (int)d->rc.rayposy;
		w.hit = 0;
		init_step_side(d, &w);
		while (w.hit == 0)
		{
			if (d->rc.sidedistx < d->rc.sidedisty)
			{
				d->rc.sidedistx += d->rc.deltadisty;
				w.mapx += w.stepx;
				w.side = 0;
			}
			else
			{
				d->rc.sidedisty += d->rc.deltadisty;
				w.mapy += w.stepy;
				w.side = 1;
			}
			if (w.mapx < d->jmax || w.mapy < d->imax || w.mapx > 0 || w.mapy > 0)
				w.hit = (d->grid[w.mapx][w.mapy] > 0) ? 1 : 0;
			else
				w.hit = 1;
		}
		if (w.side == 0)
			d->rc.lenght = (w.mapx - d->rc.rayposx + (1 - w.stepx) / 2)
				/ d->rc.raydirx;
		else
			d->rc.lenght = (w.mapy - d->rc.rayposy + (1 - w.stepy) / 2)
				/ d->rc.raydiry;
		w.lineheight = (int)(1200 / d->rc.lenght);
		w.drawstart = -w.lineheight / 2 + 1200 / 2;
		if (w.drawstart < 0)
			w.drawstart = 0;
		w.drawend = w.lineheight / 2 + 1200 / 2;
		if (w.drawend >= 1200)
			w.drawend = 1200 - 1;
		d->color = wall_color(d->grid[w.mapx][w.mapy], w.side, d->rc.lenght);
//		if (d->grid[w.mapx][w.mapy] == 1)
		draw_col(d, x, w.drawstart, w.drawend, d->color);
		x++;
	}
}
