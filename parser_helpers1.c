/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

double			find_decimal(char *str)
{
	unsigned	power;
	unsigned	pos;
	double		ans;

	pos = 1;
	power = ft_strlen(str);
	while (power-- > 0)
		pos *= 10;
	ans = (double)(atoi(str)) / pos;
	return (ans);
}

double			parse_double(char *str)
{
	char	**tmp;
	double	ans;

	tmp = ft_strsplit(str, '.');
	if (tmp[1] && !tmp[2])
	{
		ans = atoi(tmp[0]);
		if (ans >= 0.0f)
			ans += find_decimal(tmp[1]);
		else
			ans -= find_decimal(tmp[1]);
	}
	else if (tmp[0] && !tmp[1])
		ans = atoi(tmp[0]);
	else
		ans = 0.0f;
	memdel_2d(tmp);
	return (ans);
}

t_vector		parse_tripple(char *str)
{
	char		**t_s;
	t_vector	tmp;

	t_s = ft_strsplit(ft_strtrim(ft_strtrim(str, '('), ')'), ',');
	if (t_s[2] && !t_s[3])
	{
		tmp = vect_create(parse_double(t_s[0]),
			parse_double(t_s[1]), parse_double(t_s[2]));
	}
	else
		tmp = vect_create(0, 0, 0);
	memdel_2d(t_s);
	return (tmp);
}
