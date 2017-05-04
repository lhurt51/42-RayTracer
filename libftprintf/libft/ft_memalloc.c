/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memwalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:03:50 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/26 12:03:51 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tmp;

	tmp = (void*)malloc(sizeof(void) * size);
	if (!tmp || size == 0)
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}
