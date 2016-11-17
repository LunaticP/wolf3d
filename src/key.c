/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:38:52 by aviau             #+#    #+#             */
/*   Updated: 2016/11/17 22:50:08 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		keypress(int key, t_e *d)
{
	if (LEFT && !(d->key & POS_XM))
		d->key += POS_XM;
	if (RIGHT && !(d->key & POS_XP))
		d->key += POS_XP;
	if (UP && !(d->key & POS_YM))
		d->key += POS_YM;
	if (DOWN && !(d->key & POS_YP))
		d->key += POS_YP;
	return (0);
}

int		keyrel(int key, t_e *d)
{
	if (ESC)
	{
		mlx_destroy_image(d->mlx, d->image);
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	if (LEFT && (d->key & POS_XM))
		d->key -= POS_XM;
	if (RIGHT && (d->key & POS_XP))
		d->key -= POS_XP;
	if (UP && (d->key & POS_YM))
		d->key -= POS_YM;
	if (DOWN && (d->key & POS_YP))
		d->key -= POS_YP;
	return (0);
}

void	movex(t_e *d)
{
	if (d->key & POS_XM)
	{
		if (d->grid[(int)(d->rc.posx + d->rc.diry * 0.2)][(int)d->rc.posx] == 0)
			d->rc.posx += d->rc.diry * 0.2;
		if (d->grid[(int)d->rc.posx][(int)(d->rc.posy + d->rc.dirx * 0.2)] == 0)
			d->rc.posy += d->rc.dirx * 0.2;
	}
	if (d->key & POS_XP)
	{
		if (d->grid[(int)(d->rc.posx - d->rc.diry * 0.2)][(int)d->rc.posy] == 0)
			d->rc.posx -= d->rc.diry * 0.2;
		if (d->grid[(int)d->rc.posx][(int)(d->rc.posy - d->rc.dirx * 0.2)] == 0)
			d->rc.posy -= d->rc.dirx * 0.2;
	}
}

void	movey(t_e *d)
{
	if (d->key & POS_YM)
	{
		if (d->grid[(int)(d->rc.posx + d->rc.dirx * 0.2)][(int)d->rc.posy] == 0)
			d->rc.posx += d->rc.dirx * 0.2;
		if (d->grid[(int)d->rc.posx][(int)(d->rc.posy + d->rc.diry * 0.2)] == 0)
			d->rc.posy += d->rc.diry * 0.2;
	}
	if (d->key & POS_YP)
	{
		if (d->grid[(int)(d->rc.posx - d->rc.dirx * 0.2)][(int)d->rc.posy] == 0)
			d->rc.posx -= d->rc.dirx * 0.2;
		if (d->grid[(int)d->rc.posx][(int)(d->rc.posy - d->rc.diry * 0.2)] == 0)
			d->rc.posy -= d->rc.diry * 0.2;
	}
}

void	keyapply(t_e *d)
{
	if (d->key & (POS_XP | POS_XM))
		movex(d);
	if (d->key & (POS_YP | POS_YM))
		movey(d);
}
