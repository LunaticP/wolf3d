/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 08:22:12 by aviau             #+#    #+#             */
/*   Updated: 2016/11/13 04:17:31 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>

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
	int				x;
	int				y;
	int				ang;
	int				color;
	int				lastx;
	int				lasty;
	int				**grid;
	unsigned int	key;
	float			imax;
	float			jmax;
}					t_e;

int					parse(char *file, t_e *data);
int					mouse(int x, int y, t_e *data);
void				draw_map(t_e *d);
void				disp_data(t_e *d);
void				put_px(t_e *data, int x, int y);
void				draw_line(t_e *data, int x, int y, int x1, int y1);
char				*free_join(char *dst, char *src);

#endif
