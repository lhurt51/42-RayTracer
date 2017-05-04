/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*call_len_s(va_list ap, t_conv *obj)
{
	if (obj->len.l)
		return (wstr_to_str(va_arg(ap, wchar_t *)));
	else
		return (va_arg(ap, char *));
}

int		printf_s(va_list ap, t_conv *obj)
{
	char		*holder;
	char		*tmp;

	holder = call_len_s(ap, obj);
	if (!holder)
	{
		obj->b_con = 1;
		if (!obj->prec || obj->prec >= 6)
			tmp = ft_strdup("(null)");
		else
			tmp = ft_strdup("");
	}
	else
		tmp = ft_strdup(holder);
	if (obj->prec)
		tmp = ft_strsub(tmp, 0, obj->prec);
	if (obj->width)
		tmp = modify_width(obj, tmp);
	obj->size += ft_strlen(tmp);
	obj->rtn = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (obj->size);
}

int		printf_ws(va_list ap, t_conv *obj)
{
	obj->len.l = 1;
	return (printf_s(ap, obj));
}
