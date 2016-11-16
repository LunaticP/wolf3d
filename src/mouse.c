/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:28:14 by aviau             #+#    #+#             */
/*   Updated: 2016/11/16 10:01:22 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse(int x, int y, t_e *d)
{
	float rotSpeed;

	rotSpeed = (float)abs(d->lastx - x) / 50;
	if (d->lastx < x)
	{
		double oldDirX = d->rc.dirX;
		d->rc.dirX = d->rc.dirX * cos(-rotSpeed) - d->rc.dirY * sin(-rotSpeed);
		d->rc.dirY = oldDirX * sin(-rotSpeed) + d->rc.dirY * cos(-rotSpeed);
		double oldPlaneX = d->rc.planeX;
		d->rc.planeX = d->rc.planeX * cos(-rotSpeed) - d->rc.planeY * sin(-rotSpeed);
		d->rc.planeY = oldPlaneX * sin(-rotSpeed) + d->rc.planeY * cos(-rotSpeed);
	}
	else
	{
		double oldDirX = d->rc.dirX;
		d->rc.dirX = d->rc.dirX * cos(rotSpeed) - d->rc.dirY * sin(rotSpeed);
		d->rc.dirY = oldDirX * sin(rotSpeed) + d->rc.dirY * cos(rotSpeed);
		double oldPlaneX = d->rc.planeX;
		d->rc.planeX = d->rc.planeX * cos(rotSpeed) - d->rc.planeY * sin(rotSpeed);
		d->rc.planeY = oldPlaneX * sin(rotSpeed) + d->rc.planeY * cos(rotSpeed);
	}
	d->lastx = x;
	d->lasty = y;
	if (!(d->key & DRAW))
		d->key += DRAW;
	return (0);
}
