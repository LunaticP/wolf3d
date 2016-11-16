/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:30:43 by aviau             #+#    #+#             */
/*   Updated: 2016/11/16 09:42:37 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

#define mapWidth d->imax
#define mapHeight d->jmax

void	draw_col(t_e *d, int x, int drawStart, int drawEnd, int color)
{
	int y;

	y = 0;
	while (y < 1200)
	{
		if (y < drawStart)
			d->color = get_color(0xCD + y / 10, 0xF9 + y / 10, 255);
		else if (y >= drawStart && y <= drawEnd)
			d->color = color;
		else
			d->color = 0xBB6666;
		put_px(d, x, y);
		y++;
	}
}

void	draw_map(t_e *d)
{

	int x;

	x = 0;
	while (x < 1200)
	{
		d->rc.cameraX = 2 * x / 1200.0 - 1;
		d->rc.rayPosX = d->rc.posX;
		d->rc.rayPosY = d->rc.posY;
		d->rc.rayDirX = d->rc.dirX + d->rc.planeX * d->rc.cameraX;
		d->rc.rayDirY = d->rc.dirY + d->rc.planeY * d->rc.cameraX;
		int mapX = (int)d->rc.rayPosX;
		int mapY = (int)d->rc.rayPosY;

		d->rc.deltaDistX = sqrt(1 + (d->rc.rayDirY * d->rc.rayDirY) / (d->rc.rayDirX * d->rc.rayDirX));
		d->rc.deltaDistY = sqrt(1 + (d->rc.rayDirX * d->rc.rayDirX) / (d->rc.rayDirY * d->rc.rayDirY));
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (d->rc.rayDirX < 0)
		{
			stepX = -1;
			d->rc.sideDistX = (d->rc.rayPosX - mapX) * d->rc.deltaDistX;
		}
		else
		{
			stepX = 1;
			d->rc.sideDistX = (mapX + 1.0 - d->rc.rayPosX) * d->rc.deltaDistX;
		}
		if (d->rc.rayDirY < 0)
		{
			stepY = -1;
			d->rc.sideDistY = (d->rc.rayPosY - mapY) * d->rc.deltaDistY;
		}
		else
		{
			stepY = 1;
			d->rc.sideDistY = (mapY + 1.0 - d->rc.rayPosY) * d->rc.deltaDistY;
		}
		while (hit == 0)
		{
			if (d->rc.sideDistX < d->rc.sideDistY)
			{
				d->rc.sideDistX += d->rc.deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				d->rc.sideDistY += d->rc.deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (d->grid[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0) d->rc.lenght = (mapX - d->rc.rayPosX + (1 - stepX) / 2) / d->rc.rayDirX;
		else           d->rc.lenght = (mapY - d->rc.rayPosY + (1 - stepY) / 2) / d->rc.rayDirY;
		int lineHeight = (int)(1200 / d->rc.lenght);
		int drawStart = -lineHeight / 2 + 1200 / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + 1200 / 2;
		if(drawEnd >= 1200)drawEnd = 1200 - 1;
		switch(d->grid[mapX][mapY])
		{
			case 1:  d->color = 0xFF0000;  break;
			case 2:  d->color = 0x00FF00;  break;
			case 3:  d->color = 0x0000FF;   break;
			case 4:  d->color = 0xFFFFFF;  break;
			default: d->color = 0xFFFF00; break;
		}
		if (side == 1) {d->color = d->color / 2;}
		draw_col(d, x, drawStart, drawEnd, d->color);
		x++;
	}
	/************************************************************************\
	int moveSpeed = 1;
	if (d->key & POS_YM)
	{
		ft_putstr("front\n");
		if(d->grid[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
		if(d->grid[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	}
	if (d->key & POS_YP)
	{
		ft_putstr("back\n");
		if(d->grid[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
		if(d->grid[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
	}
	int rotSpeed = 1;
	//rotate to the right
	if (d->key & POS_XP)
	{
		ft_putstr("right\n");
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (d->key & POS_XM)
	{
		ft_putstr("left\n");
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	\************************************************************************/
}
