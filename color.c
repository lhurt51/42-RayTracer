/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/color.h"

t_color		col_create(double r, double g, double b)
{
	t_color		color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color		col_mul_coef(t_color *c1, double coef)
{
	t_color		res;

	res.red = c1->red * coef;
	res.green = c1->green * coef;
	res.blue = c1->blue * coef;
	return (res);
}

t_color		col_add(t_color *c1, t_color *c2)
{
	t_color		res;

	res.red = c1->red + c2->red;
	res.green = c1->green + c2->green;
	res.blue = c1->blue + c2->blue;
	return (res);
}

t_color		col_mul(t_color *c1, t_color *c2)
{
	t_color		res;

	res.red = c1->red * c2->red;
	res.green = c1->green * c2->green;
	res.blue = c1->blue * c2->blue;
	return (res);
}
