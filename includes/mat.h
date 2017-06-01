/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT_H
# define MAT_H

void		mat_identity(float mat[4][4]);
void		mat_copy(float source[4][4], float dest[4][4]);
void		mat_mult(float mata[4][4], float matb[4][4], float dest[4][4]);
void		mat_translate(float matrix[4][4], float tx, float ty, float tz);
void		mat_scale(float matrix[4][4], float sx, float sy, float sz);
void		mat_rotate(float matrix[4][4], float ax, float ay, float az);
void		vec_mult_mat(t_vector *source, float mat[4][4], t_vector *dest);

#endif
