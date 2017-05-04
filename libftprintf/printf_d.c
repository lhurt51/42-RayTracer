/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*call_len_d(va_list ap, t_conv *obj)
{
	if (obj->len.hh)
		return (ft_sctoa_base(va_arg(ap, int), 10));
	else if (obj->len.h)
		return (ft_sitoa_base(va_arg(ap, int), 10));
	else if (obj->len.l)
		return (ft_ltoa_base(va_arg(ap, long), 10));
	else if (obj->len.ll)
		return (ft_lltoa_base(va_arg(ap, long long), 10));
	else if (obj->len.j)
		return (ft_jtoa_base(va_arg(ap, intmax_t), 10));
	else if (obj->len.z)
		return (ft_ztoa_base(va_arg(ap, size_t), 10));
	else
		return (ft_itoa_base(va_arg(ap, int), 10));
}

int		printf_d(va_list ap, t_conv *obj)
{
	char	*tmp;

	tmp = call_len_d(ap, obj);
	if (obj->b_prec)
		tmp = modify_prec(obj, tmp);
	if (obj->flags.zero && obj->width)
		tmp = modify_width(obj, tmp);
	if (obj->flags.plus && tmp[0] != '-')
		tmp = ft_strjoin("+", tmp);
	if (obj->flags.space && tmp[0] != '-')
		tmp = ft_strjoin(" ", tmp);
	if (!obj->flags.zero && obj->width)
		tmp = modify_width(obj, tmp);
	obj->size += ft_strlen(tmp);
	obj->rtn = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (obj->size);
}

int		printf_ld(va_list ap, t_conv *obj)
{
	obj->len.l = 1;
	return (printf_d(ap, obj));
}
