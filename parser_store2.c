/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"
#include "includes/mat.h"

t_vector		rot_plane(char *rot)
{
	t_vector	rtn;
	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, 0, -1);
	rtn = parse_rot(rot);
	mat_identity(mat);
	mat_rotate(mat, rtn.x, rtn.y, rtn.z);
	vec_mult_mat(&tmp, mat, &rtn);
	return (rtn);
}

unsigned		store_planes(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.planes[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.planes[i].rot = rot_plane(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.planes[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong plane properties")));
	return (1);
}
