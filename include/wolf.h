/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:00:04 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 06:40:25 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>

# define WSIZE	1100
# define HSIZE	900
# define SPEED	8

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				color;
	int				ratio;
}					t_color;

typedef struct		s_wmap
{
	int				side;
	int				stepx;
	int				stepy;
	int				mapx;
	int				mapy;
	int				lineheight;
	int				drawstart;
	int				drawend;
}					t_wmap;

typedef struct		s_wolfcalc
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	rposx;
	double	rposy;
	double	rdirx;
	double	rdiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	len;
}					t_wolfcalc;

typedef struct		s_e
{
	void			*mlx;
	void			*win;
	void			*image;
	char			*addr;
	char			*name;
	int				bpp;
	int				l_size;
	int				endian;
	int				ang;
	int				lc;
	int				color;
	int				lastx;
	int				lasty;
	int				**grid;
	unsigned int	key;
	float			imax;
	float			jmax;
	float			l;
	t_wolfcalc		rc;
	t_color			c;
}					t_e;

int					parse(char *file, t_e *data);
int					get_color(int r, int g, int b);
int					mouse(int x, int y, t_e *data);
int					keypress(int key, t_e *data);
int					keyrel(int key, t_e *data);
int					w_close(t_e *d);
char				*free_join(char *dst, char *src);
void				keyapply(t_e *d);
void				draw_map(t_e *d);
void				disp_data(t_e *d);
void				put_px(t_e *data, int x, int y);
void				draw_line(t_e *data, int x, int y, int x1, int y1);
void				w_reparse(t_e *data);
void				minimap(t_e *d);
void				init_step_side(t_e *d, t_wmap *w);

#endif
