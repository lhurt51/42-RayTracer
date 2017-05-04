/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:02:18 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/26 17:02:21 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *new;

	new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!new)
		return (NULL);
	ft_strncpy(new, s1, ft_strlen(s1));
	ft_strncat(new, s2, ft_strlen(s2));
	return (new);
}
