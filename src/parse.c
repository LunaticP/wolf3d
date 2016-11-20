/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 07:01:53 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 08:18:44 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		lenght(char *line)
{
	int	i;
	int c;

	i = 0;
	c = 0;
	while (line[i] == ' ' && line[i])
		i++;
	while (line[i])
	{
		while ((ft_isdigit(line[i] || line[i] == 'S')) && line[i])
			i++;
		c++;
		while (line[i] != ' ' && line[i] && ft_isprint(line[i]))
			i++;
		if (!ft_isprint(line[i]) && line[i] != '\0')
		{
			ft_putstr("./wolf3d : file error\n");
			exit(1);
		}
		while (line[i] == ' ' && line[i])
			i++;
	}
	return (c);
}

void	conv(t_e *d, char *line, int size, int x)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	d->grid[x] = (int *)ft_memalloc(sizeof(int) * size);
	while (line[i])
	{
		if (line[i] == ',')
			while (line[i] != ' ' && line[i])
				i++;
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == 'S' && !(d->grid[x][c] = 0))
		{
			d->rc.posx = x + 0.5;
			d->rc.posy = c + 0.5;
		}
		else if (line[i])
			d->grid[x][c] = ft_atoi(&line[i]);
		c++;
		while (line[i] && line[i] != ' ' && line[i] != ',')
			i++;
	}
}

void	ex_err(char *file)
{
	if (file == NULL)
		ft_putstr("usage : ./wolf3d <file>\n");
	else
	{
		ft_putstr("./wolf3d : file \"");
		ft_putstr(file);
		ft_putstr("\" is unavailable\n");
	}
	exit(1);
}

int		mem(t_e *data, int c, int fd, int ret)
{
	if (ret < 0)
	{
		ft_putstr("./wolf3d : \"");
		ft_putstr(data->name);
		ft_putstr("\" is not a file\n");
		exit(1);
	}
	data->grid = (int **)ft_memalloc(sizeof(int *) * c);
	data->jmax = c;
	close(fd);
	return (-1);
}

int		parse(char *file, t_e *data)
{
	int		fd;
	int		c;
	int		size;
	int		ret;
	char	*line;

	fd = 0;
	if ((file == NULL || (fd = open(file, O_RDONLY)) < 0))
		ex_err(file);
	c = 1;
	while ((ret = get_next_line(fd, &line)) > 0 && c++)
	{
		size = lenght(line);
		data->imax = (size > data->imax) ? size : data->imax;
		ft_strdel(&line);
	}
	c = mem(data, c - 1, fd, ret);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		conv(data, line, data->imax, ++c);
		ft_strdel(&line);
	}
	close(fd);
	return (0);
}
