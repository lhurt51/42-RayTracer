/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	printf_c(va_list ap, t_conv *obj)
{
	char			tmp;
	char			*str;

	tmp = va_arg(ap, int);
	if (!tmp)
	{
		obj->b_con = 1;
		str = ft_strdup("");
		ft_putchar('\0');
	}
	else
	{
		str = ft_strnew(1);
		str[0] = tmp;
	}
	if (obj->width)
		str = modify_width(obj, str);
	obj->size += ft_strlen(str);
	obj->rtn = ft_strdup(str);
	ft_strdel(&str);
	return (obj->size);
}

int	printf_p(va_list ap, t_conv *obj)
{
	uintmax_t		test;
	char			*tmp;

	test = va_arg(ap, uintmax_t);
	tmp = str_low(ft_ujtoa_base(test, 16));
	tmp = ft_strjoin("0x", tmp);
	if (obj->width)
		tmp = modify_width(obj, tmp);
	obj->size += ft_strlen(tmp);
	obj->rtn = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (obj->size);
}

int	printf_per(t_conv *obj)
{
	char	*tmp;

	tmp = ft_strdup("%\0");
	if (obj->width)
		tmp = modify_width(obj, tmp);
	obj->size += ft_strlen(tmp);
	obj->rtn = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (obj->size);
}
