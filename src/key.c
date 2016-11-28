/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:38:52 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 00:39:35 by aviau            ###   ########.fr       */
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
		w_close(d);
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
	int	rx;
	int	ry;
	int	lx;
	int	ly;

	rx = (int)(d->rc.posx + d->rc.planex * 0.2);
	ry = (int)(d->rc.posy + d->rc.planey * 0.2);
	lx = (int)(d->rc.posx - d->rc.planex * 0.2);
	ly = (int)(d->rc.posy - d->rc.planey * 0.2);
	if (d->key & POS_XM)
	{
		if (d->grid[rx][(int)d->rc.posy] <= 0)
			d->rc.posx -= d->rc.planex * 0.2;
		if (d->grid[(int)d->rc.posx][ry] <= 0)
			d->rc.posy -= d->rc.planey * 0.2;
	}
	if (d->key & POS_XP)
	{
		if (d->grid[lx][(int)d->rc.posy] <= 0)
			d->rc.posx += d->rc.planex * 0.2;
		if (d->grid[(int)d->rc.posx][ly] <= 0)
			d->rc.posy += d->rc.planey * 0.2;
	}
}

void	movey(t_e *d)
{
	int fwx;
	int fwy;
	int	bwx;
	int	bwy;

	fwx = (int)(d->rc.posx + d->rc.dirx * 0.2);
	fwy = (int)(d->rc.posy + d->rc.diry * 0.2);
	bwx = (int)(d->rc.posx - d->rc.dirx * 0.2);
	bwy = (int)(d->rc.posy - d->rc.diry * 0.2);
	if (d->key & POS_YM)
	{
		if (d->grid[fwx][(int)d->rc.posy] <= 0)
			d->rc.posx += d->rc.dirx * 0.2;
		if (d->grid[(int)d->rc.posx][fwy] <= 0)
			d->rc.posy += d->rc.diry * 0.2;
	}
	if (d->key & POS_YP)
	{
		if (d->grid[bwx][(int)d->rc.posy] <= 0)
			d->rc.posx -= d->rc.dirx * 0.2;
		if (d->grid[(int)d->rc.posx][bwy] <= 0)
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
