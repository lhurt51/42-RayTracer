/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		check_len(t_conv *obj, const char *str)
{
	if (ft_strnequ(str, "hh\0", 2))
	{
		obj->len.hh = 1;
		return (2);
	}
	else if (str[0] == 'h')
		obj->len.h = 1;
	else if (ft_strnequ(str, "ll\0", 2))
	{
		obj->len.ll = 1;
		return (2);
	}
	else if (str[0] == 'l')
		obj->len.l = 1;
	else if (str[0] == 'j')
		obj->len.j = 1;
	else if (str[0] == 'z')
		obj->len.z = 1;
	else
		return (0);
	return (1);
}

int		any_len(t_conv *obj)
{
	if (obj->len.hh || obj->len.h || obj->len.ll || obj->len.j
		|| obj->len.z)
		return (1);
	return (0);
}

char	*print_len(t_conv *obj)
{
	if (obj->len.hh)
		return ("hh\0");
	else if (obj->len.h)
		return ("h\0");
	else if (obj->len.l)
		return ("l\0");
	else if (obj->len.ll)
		return ("ll\0");
	else if (obj->len.j)
		return ("j\0");
	else if (obj->len.z)
		return ("z\0");
	else
		return (NULL);
}
