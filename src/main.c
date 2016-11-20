/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 06:22:00 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 06:47:51 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	print_map(t_e d)
{
	int j;
	int i;

	j = 0;
	ft_putchar('\n');
	while (j < d.jmax)
	{
		i = 0;
		while (i < d.imax)
		{
			ft_putnbr(d.grid[j][i]);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}

int		wolf_loop(t_e *d)
{
	keyapply(d);
	draw_map(d);
	mlx_put_image_to_window(d->mlx, d->win, d->image, 0, 0);
	if (d->lc > 5000 && d->lc <= 10000)
		d->l += 0.03;
	if (d->lc > 25000 && d->lc <= 30000)
		d->l -= 0.03;
	d->lc = (d->lc < 30000) ? d->lc + 1 : 0;
	return (0);
}

t_e		init(void)
{
	t_e	d;

	d.ang = 0;
	d.imax = 0;
	d.jmax = 0;
	d.key = 0;
	d.rc.posx = -1;
	d.rc.posy = -1;
	d.rc.dirx = -1;
	d.rc.diry = 0;
	d.rc.planex = 0;
	d.rc.planey = 0.66;
	d.lc = 4990;
	d.l = 1;
	return (d);
}

int		main(int ac, char **av)
{
	t_e	d;

	(ac != 2) ? parse(NULL, &d) : 0;
	d = init();
	parse(av[1], &d);
	if (d.rc.posx == -1 || d.rc.posy == -1)
	{
		ft_putstr("\n\e[31mMissing start point \e[0m: \
				\e[33mPut 'S' in the map\e[0m\n");
		exit(1);
	}
	w_reparse(&d);
	d.rc.posx += 0.05;
	d.rc.posy += 0.05;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WSIZE, HSIZE, "wolf3d");
	d.image = mlx_new_image(d.mlx, WSIZE, HSIZE);
	d.addr = mlx_get_data_addr(d.image, &d.bpp, &d.l_size, &d.endian);
	mlx_hook(d.win, 2, (1L << 0), &keypress, &d);
	mlx_hook(d.win, 3, (1L << 1), &keyrel, &d);
	mlx_hook(d.win, 6, (1L << 13), &mouse, &d);
	mlx_hook(d.win, 17, (1L << 17), w_close, &d);
	mlx_loop_hook(d.mlx, &wolf_loop, &d);
	mlx_loop(d.mlx);
	w_close(&d);
}
