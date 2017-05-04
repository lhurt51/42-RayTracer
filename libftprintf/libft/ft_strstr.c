/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:48:33 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/25 20:48:41 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (big[i] == little[i] && big[i] == '\0')
		return ((char*)&big[i]);
	while (big[i] != '\0')
	{
		j = i;
		while (big[j] == little[j - i] && big[j] != '\0')
			j++;
		if (little[j - i] == '\0')
		{
			return ((char*)&big[i]);
		}
		i++;
	}
	return (NULL);
}
