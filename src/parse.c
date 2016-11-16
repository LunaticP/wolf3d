/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 07:01:53 by aviau             #+#    #+#             */
/*   Updated: 2016/11/16 09:03:15 by aviau            ###   ########.fr       */
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
		while (ft_isdigit(line[i]) && line[i])
			i++;
		c++;
		while (line[i] != ' ' && line[i] && ft_isprint(line[i]))
			i++;
		if (!ft_isprint(line[i]) && line[i] != '\0')
		{
			ft_putstr("./fdf : file error\n");
			exit(1);
		}
		while (line[i] == ' ' && line[i])
			i++;
	}
	return (c);
}

int		conv(int **grid, char *line, int size)
{
	int			i;
	int			c;
	static int	max = 0;

	i = 0;
	c = 0;
	*grid = (int *)ft_memalloc(sizeof(int) * size);
	while (line[i])
	{
		if (line[i] == ',')
			while (line[i] != ' ' && line[i])
				i++;
		while (line[i] && line[i] == ' ')
			i++;
		grid[0][c] = ft_atoi(&line[i]);
		if (grid[0][c] >= max)
			max = grid[0][c];
		c++;
		while (line[i] && line[i] != ' ' && line[i] != ',')
			i++;
	}
	return (max);
}

void	ex_err(char *file)
{
	if (file == NULL)
		ft_putstr("usage : ./fdf <file>\n");
	else
	{
		ft_putstr("./fdf : file \"");
		ft_putstr(file);
		ft_putstr("\" is unavailable\n");
	}
	exit(1);
}

int		mem(t_e *data, int c, int fd, int ret)
{
	if (ret < 0)
	{
		ft_putstr("./fdf : \"");
		ft_putstr(data->name);
		ft_putstr("\" is not a file\n");
		exit(1);
	}
	data->grid = (int **)ft_memalloc(sizeof(int *) * (c + 1));
	data->grid[c] = NULL;
	data->jmax = c;
	close(fd);
	return (0);
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
		if (size > data->imax)
			data->imax = size;
		free(line);
	}
	c = mem(data, c - 1, fd, ret);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		conv(&data->grid[c++], line, size);
		free(line);
	}
	return (0);
}
