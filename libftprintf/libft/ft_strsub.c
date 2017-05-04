/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:52:19 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/26 16:52:21 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	new = ft_strnew(len);
	if (!new)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	return (new);
}
