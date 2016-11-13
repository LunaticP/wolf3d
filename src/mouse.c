/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:28:14 by aviau             #+#    #+#             */
/*   Updated: 2016/11/10 08:02:18 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	y_rot_mouse(int x, t_e *data)
{
	float	a;

	if (x < data->lastx)
	{
		data->lastx = x;
	}
	if (x > data->lastx)
	{
		data->lastx = x;
	}
}

void	x_rot_mouse(int y, t_e *data)
{
	float	a;

	if (y < data->lasty)
	{
		data->lasty = y;
	}
	if (y > data->lasty)
	{
		data->lasty = y;
	}
}

int		mouse(int x, int y, t_e *data)
{
	if (data->do_move)
		;
	return (0);
}
