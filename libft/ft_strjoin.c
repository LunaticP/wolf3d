/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 04:34:12 by aviau             #+#    #+#             */
/*   Updated: 2016/07/01 05:40:17 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *a, char const *b)
{
	int		i;
	int		j;
	char	*r;

	if (!a || !b)
		return (NULL);
	i = 0;
	j = 0;
	if (!(r = (char*)malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1))))
		return (NULL);
	while (a[i] != '\0')
	{
		r[j] = a[i];
		i++;
		j++;
	}
	i = 0;
	while (b[i] != '\0')
	{
		r[j] = b[i];
		i++;
		j++;
	}
	r[j] = '\0';
	return (r);
}
