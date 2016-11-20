/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 05:30:31 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 07:30:35 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	init_step_side(t_e *d, t_wmap *w)
{
	if (d->rc.rdirx < 0)
	{
		w->stepx = -1;
		d->rc.sidedistx = (d->rc.rposx - w->mapx) * d->rc.deltadistx;
	}
	else
	{
		w->stepx = 1;
		d->rc.sidedistx = (w->mapx + 1.0 - d->rc.rposx) * d->rc.deltadistx;
	}
	if (d->rc.rdiry < 0)
	{
		w->stepy = -1;
		d->rc.sidedisty = (d->rc.rposy - w->mapy) * d->rc.deltadisty;
	}
	else
	{
		w->stepy = 1;
		d->rc.sidedisty = (w->mapy + 1.0 - d->rc.rposy) * d->rc.deltadisty;
	}
}

void	w_reparse(t_e *d)
{
	int	i;
	int	j;

	j = 0;
	while (j < d->jmax)
	{
		i = 0;
		while (i < d->imax)
		{
			if ((j == 0 || i == 0 || j == d->jmax - 1 || i == d->imax - 1)
					&& (d->grid[j][i] <= 0 || d->grid[j][i] == 99))
				d->grid[j][i] = 1;
			i++;
		}
		j++;
	}
}

int		w_close(t_e *d)
{
	int	i;

	i = 0;
	while (i < d->jmax)
		ft_memdel((void**)&(d->grid[i++]));
	ft_memdel((void**)d->grid);
	exit(0);
	return (666);
}
