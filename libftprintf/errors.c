/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		flag_d(t_conv *obj)
{
	if (obj->flags.hash)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv)
			, ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (obj->conv == 'D' && any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv)
			, " does work with any len")));
	}
	return (1);
}

int		flag_u(t_conv *obj)
{
	if (obj->flags.hash || obj->flags.plus || obj->flags.space)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (obj->conv == 'U' && any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			" does work with any len")));
	}
	return (1);
}

int		flag_o(t_conv *obj)
{
	if (obj->flags.plus || obj->flags.space)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	if (obj->conv == 'O' && any_len(obj))
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			" does work with any len")));
	}
	return (1);
}

int		flag_x(t_conv *obj)
{
	if (obj->flags.plus || obj->flags.space)
	{
		return ((int)error(ft_strjoin(ft_strjoin(" conv:", &obj->conv),
			ft_strjoin(" does work with flag:", print_flag(obj)))));
	}
	return (1);
}
