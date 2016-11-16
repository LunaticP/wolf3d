/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 06:22:00 by aviau             #+#    #+#             */
/*   Updated: 2016/11/16 09:53:00 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wolf_loop(t_e *d)
{
	if (d->key & DRAW)
	{
		draw_map(d);
		mlx_put_image_to_window(d->mlx, d->win, d->image, 0, 0);
		d->key -= DRAW;
	}
	keyapply(d);
	return (0);
}

t_e		init(void)
{
	t_e	d;

	d.ang = 0;
	d.imax = 0;
	d.jmax = 0;
	d.key = DRAW;
	d.rc.posX = 10;
	d.rc.posY = 5;
	d.rc.dirX = -1;
	d.rc.dirY = 0;
	d.rc.planeX = 0;
	d.rc.planeY = 0.66;
	return (d);
}

int		main(int ac, char **av)
{
	t_e	d;

	if (ac != 2)
		parse(NULL, &d);
	d = init();
	d.name = ft_strdup(av[1]);
	ft_putstr("\e[33mparsing...\t\t\e[0m");
	parse(av[1], &d);
	ft_putstr("\e[32m[done]\n\e[33mwindows creation...\t\e[0m");
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, 1200, 1200, "fdf");
	d.image = mlx_new_image(d.mlx, 1200, 1200);
	d.addr = mlx_get_data_addr(d.image, &d.bpp, &d.l_size, &d.endian);
	ft_putstr("\e[32m[done]\e[0m\n");
	mlx_hook(d.win, 2, (1L << 0), &keypress, &d);
	mlx_hook(d.win, 3, (1L << 1), &keyrel, &d);
	mlx_hook(d.win, 6, (1L << 13), &mouse, &d);
	mlx_loop_hook(d.mlx, &wolf_loop, &d);
	mlx_loop(d.mlx);
}
