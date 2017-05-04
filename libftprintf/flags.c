/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		check_flag(t_conv *obj, char c)
{
	if (c == '#')
		obj->flags.hash = 1;
	else if (c == '0')
		obj->flags.zero = 1;
	else if (c == '-')
		obj->flags.minus = 1;
	else if (c == '+')
		obj->flags.plus = 1;
	else if (c == ' ')
		obj->flags.space = 1;
	else
		return (0);
	return (1);
}

char	*print_flag(t_conv *obj)
{
	if (obj->flags.plus)
		return ("+\0");
	else if (obj->flags.space)
		return ("space\0");
	else if (obj->flags.hash)
		return ("#\0");
	else if (obj->flags.zero)
		return ("0\0");
	else
		return (NULL);
}
