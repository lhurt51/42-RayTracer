/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 10:24:52 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/22 10:24:55 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strcpy(tmp, s1);
	return (tmp);
}
