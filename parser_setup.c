/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

unsigned		set_spheres(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.sc = *size;
	s->objs.spheres = (t_sphere*)malloc(sizeof(t_sphere) * s->obj_count.sc);
	if (!s->objs.spheres)
		return ((int)error("failed to malloc"));
	return (SPHERES);
}

unsigned		set_cylinders(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.cyc = *size;
	s->objs.cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * s->obj_count.cyc);
	if (!s->objs.cylinders)
		return ((int)error("failed to malloc"));
	return (CYLINDERS);
}

unsigned		set_cones(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.cnc = *size;
	s->objs.cones = (t_cone*)malloc(sizeof(t_cone) * s->obj_count.cnc);
	if (!s->objs.cones)
		return ((int)error("failed to malloc"));
	return (CONES);
}

unsigned		set_planes(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.pc = *size;
	s->objs.planes = (t_plane*)malloc(sizeof(t_plane) * s->obj_count.pc);
	if (!s->objs.planes)
		return ((int)error("failed to malloc"));
	return (PLANES);
}
