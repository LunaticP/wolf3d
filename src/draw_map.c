/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:30:43 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 02:29:32 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	draw_col(t_e *d, int x, int drawstart, int drawend)
{
	int y;
	int	color;
	int	r;
	int	g;
	int	b;

	y = 0;
	color = d->color;
	while (y < HSIZE)
	{
		r = 0xCD + y / 10 - (d->l - 50) * 5;
		g = 0xF9 + y / 10 - d->l * 3;
		b = 0xFF - d->l * 2;
		if (y < drawstart)
			d->color = get_color(r, g, b);
		else if (y >= drawstart && y <= drawend)
			d->color = color;
		else
			d->color = get_color(0, 0x7B * ((y - HSIZE / 4) - (d->l * (1 -
			sinf(x * M_PI / WSIZE)) * 2) - d->l) / 700, 12);
		put_px(d, x, y++);
	}
	d->color = 0xFFFFFF;
}

void	init_wlf(t_e *d, int x)
{
	d->rc.camerax = 2 * x / (float)WSIZE - 1;
	d->rc.rposx = d->rc.posx;
	d->rc.rposy = d->rc.posy;
	d->rc.rdirx = d->rc.dirx + d->rc.planex * d->rc.camerax;
	d->rc.rdiry = d->rc.diry + d->rc.planey * d->rc.camerax;
	d->rc.deltadistx = sqrt(1 + (d->rc.rdiry * d->rc.rdiry) \
			/ (d->rc.rdirx * d->rc.rdirx));
	d->rc.deltadisty = sqrt(1 + (d->rc.rdirx * d->rc.rdirx) \
			/ (d->rc.rdiry * d->rc.rdiry));
}

int		wall_color(t_e *d, int w_val, int side, int x)
{
	static int	col_p[3][13] = {
		{0, 120, 173, 114, 208, 255, 255, 255, 0, 0, 0, 255, 255},
		{0, 100, 153, 92, 191, 0, 170, 255, 255, 255, 0, 0, 255},
		{0, 70, 107, 41, 152, 0, 0, 0, 0, 255, 255, 255, 255}};
	t_color		c;

	w_val = abs(w_val);
	if (w_val >= 13)
		c.color = 0xFFFFFF;
	else
	{
		c.r = col_p[0][w_val] - (side * 10) - (d->rc.len * (d->l / 25.0)) \
			- (d->l * (1 - sinf(x * M_PI / WSIZE)) / 2);
		c.g = col_p[1][w_val] - (side * 10) - (d->rc.len * (d->l / 25.0)) \
			- (d->l * (1 - sinf(x * M_PI / WSIZE)) / 2);
		c.b = col_p[2][w_val] - (side * 10) - (d->rc.len * (d->l / 25.0)) \
			- (d->l * (1 - sinf(x * M_PI / WSIZE)) / 2);
		c.r = c.r < 0 ? 0 : c.r;
		c.g = c.g < 0 ? 0 : c.g;
		c.b = c.b < 0 ? 0 : c.b;
		c.color = get_color(c.r, c.g, c.b);
	}
	return (c.color);
}

void	ray_len(t_e *d, t_wmap *w)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (d->rc.sidedistx < d->rc.sidedisty)
		{
			d->rc.sidedistx += d->rc.deltadistx;
			w->mapx += w->stepx;
			w->side = 0;
		}
		else
		{
			d->rc.sidedisty += d->rc.deltadisty;
			w->mapy += w->stepy;
			w->side = 1;
		}
		if (d->grid[w->mapx][w->mapy] != 0 && d->grid[w->mapx][w->mapy] != 99)
			hit = 1;
	}
	if (w->side == 0)
		d->rc.len = (w->mapx - d->rc.rposx + (1 - w->stepx) / 2) / d->rc.rdirx;
	else
		d->rc.len = (w->mapy - d->rc.rposy + (1 - w->stepy) / 2) / d->rc.rdiry;
}

void	draw_map(t_e *d)
{
	int		x;
	t_wmap	w;

	x = 0;
	while (x < WSIZE)
	{
		init_wlf(d, x);
		w.mapx = (int)d->rc.rposx;
		w.mapy = (int)d->rc.rposy;
		init_step_side(d, &w);
		ray_len(d, &w);
		w.lineheight = (int)(HSIZE / d->rc.len);
		w.drawstart = -(w.lineheight) / 2 + HSIZE / 2;
		if (w.drawstart < 0)
			w.drawstart = 0;
		w.drawend = w.lineheight / 2 + HSIZE / 2;
		if (w.drawend >= HSIZE)
			w.drawend = HSIZE - 1;
		d->color = wall_color(d, d->grid[w.mapx][w.mapy], w.side, x);
		draw_col(d, x, w.drawstart, w.drawend);
		x++;
	}
	minimap(d);
	d->color = 0xFF00;
}
