/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/12/02 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	*error(char *msg)
{
	ft_putstr("Error: ");
	ft_putendl(msg);
	ft_strdel(&msg);
	return (NULL);
}

char	*str_low(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i-- > 0)
		if (ft_isupper(str[i]))
			str[i] = ft_tolower(str[i]);
	return (str);
}

void	set_struct(t_conv *obj)
{
	obj->b_con = 0;
	obj->b_prec = 0;
	obj->size = 0;
	obj->flags.plus = 0;
	obj->flags.minus = 0;
	obj->flags.space = 0;
	obj->flags.hash = 0;
	obj->flags.zero = 0;
	obj->len.hh = 0;
	obj->len.h = 0;
	obj->len.l = 0;
	obj->len.ll = 0;
	obj->len.j = 0;
	obj->len.z = 0;
	obj->width = 0;
	obj->prec = 0;
}
