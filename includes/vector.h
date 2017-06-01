/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# define INVSQRTF(x) (1.0f / sqrtf(x))

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

t_vector		vect_create(double x, double y, double z);
t_vector		vect_add(t_vector *v1, t_vector *v2);
t_vector		vect_sub(t_vector *v1, t_vector *v2);
t_vector		vect_scale(double scale, t_vector *v);
t_vector		vect_cross(t_vector *v1, t_vector *v2);
float			vect_dot(t_vector *v1, t_vector *v2);
t_vector		vect_diff(t_vector *v1, t_vector *v2);
double			vect_norm(t_vector *v);

#endif
