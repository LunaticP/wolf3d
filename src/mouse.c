/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:28:14 by aviau             #+#    #+#             */
/*   Updated: 2016/11/17 22:50:45 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse(int x, int y, t_e *d)
{
	float	rsp;
	double	olddirx;
	double	oldplanex;

	olddirx = d->rc.dirx;
	oldplanex = d->rc.planex;
	rsp = (float)abs(d->lastx - x) / 50;
	if (d->lastx < x)
	{
		d->rc.dirx = d->rc.dirx * cos(-rsp) - d->rc.diry * sin(-rsp);
		d->rc.diry = olddirx * sin(-rsp) + d->rc.diry * cos(-rsp);
		d->rc.planex = d->rc.planex * cos(-rsp) - d->rc.planey * sin(-rsp);
		d->rc.planey = oldplanex * sin(-rsp) + d->rc.planey * cos(-rsp);
	}
	else
	{
		d->rc.dirx = d->rc.dirx * cos(rsp) - d->rc.diry * sin(rsp);
		d->rc.diry = olddirx * sin(rsp) + d->rc.diry * cos(rsp);
		d->rc.planex = d->rc.planex * cos(rsp) - d->rc.planey * sin(rsp);
		d->rc.planey = oldplanex * sin(rsp) + d->rc.planey * cos(rsp);
	}
	d->lastx = x;
	d->lasty = y;
	return (0);
}
