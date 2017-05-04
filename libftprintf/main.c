/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/03/02 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*set_up_conv(va_list ap, const char *str, int *i, int *b_con)
{
	t_conv	*obj;
	char	*tmp;

	obj = malloc(sizeof(t_conv));
	if (!obj)
		return (0);
	set_struct(obj);
	if (!check_all(ap, obj, str, i) || !can_mix(obj))
	{
		if ((*b_con = obj->b_con))
			(*i)++;
		return (0);
	}
	tmp = ft_strdup(obj->rtn);
	ft_strdel(&obj->rtn);
	free(obj);
	return (tmp);
}

char	*first_or(char *rtn, char *tmp, int i)
{
	if (i == 0)
		rtn = ft_strdup(tmp);
	else
		rtn = ft_strjoin(rtn, tmp);
	return (rtn);
}

int		search_params(va_list ap, const char *str, char **rtn, int count)
{
	char	*tmp;
	int		i;
	int		con;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		count = i;
		if (str[i] == '%' && !(tmp = set_up_conv(ap, str, &i, &con)) && !con)
			return (0);
		if (tmp)
		{
			*rtn = first_or(*rtn, tmp, count++);
			tmp = NULL;
		}
		if (str[i] != '%')
		{
			*rtn = first_or(*rtn, ft_strsub(&str[i], 0, 1), count);
			if (str[i])
				i++;
		}
	}
	return (1);
}

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	char	*rtn;
	int		len;

	rtn = NULL;
	va_start(ap, str);
	if (!search_params(ap, str, &rtn, 0))
		return (0);
	ft_putstr(rtn);
	len = ft_strlen(rtn);
	ft_strdel(&rtn);
	va_end(ap);
	return (len);
}
