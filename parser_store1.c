/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"
#include "includes/mat.h"

t_vector		rot_cy_cn(char *rot)
{
	t_vector	rtn;
	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, -1, 0);
	rtn = parse_rot(rot);
	mat_identity(mat);
	mat_rotate(mat, rtn.x, rtn.y, rtn.z);
	vec_mult_mat(&tmp, mat, &rtn);
	return (rtn);
}

unsigned		store_cylinders(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.cylinders[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.cylinders[i].rot = rot_cy_cn(str[1]);
	else if (ft_strequ("radius:", str[0]))
		s->objs.cylinders[i].radius = parse_double(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.cylinders[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong cylinder properties")));
	return (1);
}

unsigned		store_cones(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.cones[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.cones[i].rot = rot_cy_cn(str[1]);
	else if (ft_strequ("radius:", str[0]))
		s->objs.cones[i].radius = parse_double(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.cones[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong cone properties")));
	return (1);
}
