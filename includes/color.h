/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color
{
	double		red;
	double		green;
	double		blue;
}				t_color;

t_color			col_create(double r, double g, double b);
t_color			col_mul_coef(t_color *c1, double coef);
t_color			col_add(t_color *c1, t_color *c2);
t_color			col_mul(t_color *c1, t_color *c2);

#endif
