/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	check_conv1(va_list ap, t_conv *obj, char c)
{
	if (c == 'c')
		return (printf_c(ap, obj));
	else if (c == 'C')
		return (printf_c(ap, obj));
	else if (c == 's')
		return (printf_s(ap, obj));
	else if (c == 'S')
		return (printf_ws(ap, obj));
	else if (c == 'p')
		return (printf_p(ap, obj));
	else if (c == '%')
		return (printf_per(obj));
	else
		return ((int)error(" No specified conversion"));
}

int	check_conv(va_list ap, t_conv *obj, char c)
{
	obj->conv = c;
	if (c == 'd' || c == 'i')
		return (printf_d(ap, obj));
	else if (c == 'D')
		return (printf_ld(ap, obj));
	else if (c == 'u')
		return (printf_u(ap, obj));
	else if (c == 'U')
		return (printf_lu(ap, obj));
	else if (c == 'o')
		return (printf_o(ap, obj));
	else if (c == 'O')
		return (printf_lo(ap, obj));
	else if (c == 'x')
		return (printf_x(ap, obj));
	else if (c == 'X')
		return (printf_lx(ap, obj));
	else
		return (check_conv1(ap, obj, c));
}
