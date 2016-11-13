/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 06:22:00 by aviau             #+#    #+#             */
/*   Updated: 2016/11/13 06:50:05 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		wolf_loop(t_e *d)
{
	draw_map(d);
	mlx_put_image_to_window(d->mlx, d->win, d->image, 0, 0);
	disp_data(d);
	return (0);
}

t_e		init(void)
{
	t_e	d;

	d.x = 625;
	d.y = 380;
	d.ang = 0;
	d.imax = 0;
	d.jmax = 0;
	d.key = 0;
	return (d);
}

static int	keypress(int key, t_e *d)
{
	if (ESC)
	{
		mlx_destroy_image(d->mlx, d->image);
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	if (LEFT && d->x > 0)
		d->x -= 1;
	if (RIGHT && d->x < 1200)
		d->x += 1;
	if (UP && d->y > 0)
		d->y -= 1;
	if (DOWN && d->y < 1200)
		d->y += 1;
	if (KEY_R)
	{
		d->ang = (d->ang == 359) ? 0 : d->ang + 1;
		ft_putnbr(d->ang);
		ft_putchar('\n');
	}
	return (0);
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
//	mlx_hook(d.win, 3, (1L << 1), &keyrel, &d);
//	mlx_hook(d.win, 6, (1L << 13), &mouse, &d);
	mlx_loop_hook(d.mlx, &wolf_loop, &d);
	mlx_loop(d.mlx);
}
