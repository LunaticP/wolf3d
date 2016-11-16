/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:38:52 by aviau             #+#    #+#             */
/*   Updated: 2016/11/16 09:49:03 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int	keypress(int key, t_e *d)
{
	if (LEFT && !(d->key & POS_XM))
		d->key += POS_XM;
	if (RIGHT && !(d->key & POS_XP))
		d->key += POS_XP;
	if (UP && !(d->key & POS_YM))
		d->key += POS_YM;
	if (DOWN && !(d->key & POS_YP))
		d->key += POS_YP;
	if (!(d->key & DRAW))
		d->key += DRAW;
	return (0);
}

int	keyrel(int key, t_e *d)
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
	if (!(d->key & DRAW))
		d->key += DRAW;
	return (0);
}

void	keyapply(t_e *d)
{
	float moveSpeed = 0.005;
	if (d->key & POS_YM)
	{
		if(d->grid[(int)(d->rc.posX + d->rc.dirX * moveSpeed)][(int)d->rc.posY] == 0)
			d->rc.posX += d->rc.dirX * moveSpeed;
		if(d->grid[(int)d->rc.posX][(int)(d->rc.posY + d->rc.dirY * moveSpeed)] == 0)
			d->rc.posY += d->rc.dirY * moveSpeed;
	}
	if (d->key & POS_YP)
	{
		if(d->grid[(int)(d->rc.posX - d->rc.dirX * moveSpeed)][(int)d->rc.posY] == 0)
			d->rc.posX -= d->rc.dirX * moveSpeed;
		if(d->grid[(int)d->rc.posX][(int)(d->rc.posY - d->rc.dirY * moveSpeed)] == 0)
			d->rc.posY -= d->rc.dirY * moveSpeed;
	}
	float rotSpeed = 0.0005;
	//rotate to the right
	if (d->key & POS_XP)
	{
		double oldDirX = d->rc.dirX;
		d->rc.dirX = d->rc.dirX * cos(-rotSpeed) - d->rc.dirY * sin(-rotSpeed);
		d->rc.dirY = oldDirX * sin(-rotSpeed) + d->rc.dirY * cos(-rotSpeed);
		double oldPlaneX = d->rc.planeX;
		d->rc.planeX = d->rc.planeX * cos(-rotSpeed) - d->rc.planeY * sin(-rotSpeed);
		d->rc.planeY = oldPlaneX * sin(-rotSpeed) + d->rc.planeY * cos(-rotSpeed);
	}
	if (d->key & POS_XM)
	{
		double oldDirX = d->rc.dirX;
		d->rc.dirX = d->rc.dirX * cos(rotSpeed) - d->rc.dirY * sin(rotSpeed);
		d->rc.dirY = oldDirX * sin(rotSpeed) + d->rc.dirY * cos(rotSpeed);
		double oldPlaneX = d->rc.planeX;
		d->rc.planeX = d->rc.planeX * cos(rotSpeed) - d->rc.planeY * sin(rotSpeed);
		d->rc.planeY = oldPlaneX * sin(rotSpeed) + d->rc.planeY * cos(rotSpeed);
	}
}
