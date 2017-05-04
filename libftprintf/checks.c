/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		check_width(t_conv *obj, const char *num)
{
	int	end;
	int	tmp;

	end = 0;
	if (num[0] == '0' && num[1] > '0')
	{
		obj->width = atoi(&num[1]);
		end++;
	}
	else
		obj->width = atoi(num);
	tmp = obj->width;
	while (tmp /= 10)
		end++;
	end++;
	return (end);
}

int		check_prec(t_conv *obj, const char *num)
{
	int	end;
	int	tmp;

	end = 1;
	obj->b_prec = 1;
	if (ft_isdigit(num[1]))
	{
		obj->prec = atoi(&num[1]);
		tmp = obj->prec;
		while (tmp /= 10)
			end++;
		end++;
	}
	else
		obj->prec = 0;
	return (end);
}

int		check_all(va_list ap, t_conv *obj, const char *str, int *i)
{
	(*i)++;
	if (check_flag(obj, str[*i]))
		(*i)++;
	if (obj->flags.space)
		while (str[*i] == ' ')
			(*i)++;
	if (obj->flags.zero && check_flag(obj, str[*i]))
		(*i)++;
	if (str[*i] != '.' && ft_isdigit(str[*i]))
		(*i) += check_width(obj, &str[*i]);
	if (str[*i] == '.')
		(*i) += check_prec(obj, &str[*i]);
	if (ft_isalpha(str[*i]))
		(*i) += check_len(obj, &str[*i]);
	if (!check_conv(ap, obj, str[*i]))
		return (0);
	(*i)++;
	return (obj->size);
}
