/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 05:30:31 by aviau             #+#    #+#             */
/*   Updated: 2016/11/18 05:37:38 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	w_reparse(t_e *d)
{
	int 	i;
	int		j;

	j = 0;
	while (j < d->jmax)
	{
		i = 0;
		while (i < d->imax)
		{
			if ((j == 0 || i == 0 || j == d->jmax - 1 || i == d->imax - 1) && d->grid[j][i] <= 0)
				d->grid[j][i] = 1;
			i++;
		}
		j++;
	}
}
