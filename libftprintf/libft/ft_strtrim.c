/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:21:22 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/26 18:21:23 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*new;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	start = i;
	while (s[i] != '\0')
		i++;
	while ((s[i] == c || s[i] == '\0') && i > start)
		i--;
	end = i;
	new = ft_strnew(end - start + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (start++ <= end)
	{
		new[i] = s[start - 1];
		i++;
	}
	new[i] = '\0';
	return (new);
}
