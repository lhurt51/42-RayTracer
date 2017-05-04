/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		flag_c(t_conv *obj)
{
	if (obj->flags.plus || obj->flags.space || obj->flags.hash
		|| obj->flags.zero)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with len:", print_len(obj)))));
	}
	if (obj->conv == 'C' && any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			" does work with any len")));
	}
	return (1);
}

int		flag_s(t_conv *obj)
{
	if (obj->flags.plus || obj->flags.space || obj->flags.hash
		|| obj->flags.zero)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with len:", print_len(obj)))));
	}
	if (obj->conv == 'S' && any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			" does work with any len")));
	}
	return (1);
}

int		flag_p(t_conv *obj)
{
	if (obj->flags.plus || obj->flags.space || obj->flags.hash
		|| obj->flags.zero)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (any_len(obj) || obj->len.l)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			" does work with any len")));
	}
	return (1);
}

int		can_mix(t_conv *obj)
{
	if (obj->conv == 'd' || obj->conv == 'i' || obj->conv == 'D')
		return (flag_d(obj));
	else if (obj->conv == 'u' || obj->conv == 'U')
		return (flag_u(obj));
	else if (obj->conv == 'o' || obj->conv == 'O')
		return (flag_o(obj));
	else if (obj->conv == 'x' || obj->conv == 'X')
		return (flag_x(obj));
	else if (obj->conv == 'c' || obj->conv == 'C')
		return (flag_c(obj));
	else if (obj->conv == 's' || obj->conv == 'S')
		return (flag_s(obj));
	else if (obj->conv == 'p')
		return (flag_p(obj));
	else if (obj->conv == '%')
		return (1);
	else
		return (0);
}
