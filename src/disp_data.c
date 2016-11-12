/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 08:15:47 by aviau             #+#    #+#             */
/*   Updated: 2016/11/10 17:35:04 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*freejoin(char *dst, char *src)
{
	char	*tmp;

	tmp = src;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}

static void	disp_xy(t_e *d)
{
	char	*str1;
	char	*str2;
	char	*xy;

	str1 = freejoin("x: ", ft_itoa((int)d->x * 10));
	str2 = freejoin("   y: ", ft_itoa((int)d->y * 10));
	xy = free_join(str1, str2);
	free(str2);
	mlx_string_put(d->mlx, d->win, 10, 35, 0xFF0000, xy);
	free(xy);
}

void		disp_data(t_e *d)
{
	char	*name;

	name = ft_strjoin("map: ", d->name);
	mlx_string_put(d->mlx, d->win, 10, 10, 0x7777FF, name);
	free(name);
	disp_xy(d);
}
