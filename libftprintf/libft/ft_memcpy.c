/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:39:25 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/22 15:39:27 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	count = 0;
	while (count < n)
	{
		d[count] = s[count];
		count++;
	}
	return (dst);
}
