/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 20:09:16 by amaitre           #+#    #+#             */
/*   Updated: 2016/11/20 06:17:31 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd			*get_current_fd(int const fd, t_list **fds)
{
	t_list		*tmp;
	t_fd		content;

	tmp = *fds;
	while (tmp != NULL)
	{
		if (((t_fd *)tmp->content)->fd == fd)
			return (tmp->content);
		tmp = tmp->next;
	}
	content.fd = fd;
	content.res = NULL;
	ft_lstadd(fds, ft_lstnew((void *)&content, sizeof(content)));
	return ((*fds)->content);
}

static int			ft_check_rest(t_fd *current, char **line)
{
	char			*tmp;

	tmp = ft_strchr(current->res, '\n');
	if (tmp)
	{
		*line = ft_strsub2(current->res, 0, tmp - current->res, 0);
		ft_memmove(current->res, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

static	int			ft_read(int fd, t_fd *current, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (current->res)
			current->res = ft_strjoin2(current->res, buf, 1);
		else
			current->res = ft_strdup(buf);
		if (ft_check_rest(current, line))
			return (1);
	}
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static t_list		*fds = NULL;
	t_fd				*current;
	int					result;

	if (!line || fd < 0)
		return (-1);
	current = get_current_fd(fd, &fds);
	if (current->res && ft_check_rest(current, line))
		return (1);
	if ((result = ft_read(fd, current, line)) != 0)
		return (result);
	if (current->res == NULL || current->res[0] == '\0')
		return (0);
	*line = current->res;
	current->res = NULL;
	return (1);
}
