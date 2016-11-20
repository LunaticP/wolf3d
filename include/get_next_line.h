/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 06:18:24 by aviau             #+#    #+#             */
/*   Updated: 2016/11/20 06:18:33 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include "libft.h"
# define BUFF_SIZE 4096

typedef struct	s_fd
{
	int			fd;
	char		*res;
}				t_fd;

int				get_next_line(int const fd, char **line);

#endif
