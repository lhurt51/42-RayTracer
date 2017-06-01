/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

unsigned		set_settings(unsigned *size)
{
	*size = 1;
	return (SETTINGS);
}

unsigned		set_materials(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.mc = *size;
	s->objs.materials = (t_mat*)malloc(sizeof(t_mat) * s->obj_count.mc);
	if (!s->objs.materials)
		return ((int)error("failed to malloc"));
	return (MATERIALS);
}

unsigned		set_lights(t_scene *s, char *str, unsigned *size)
{
	*size = ft_atoi(str);
	s->obj_count.lc = *size;
	s->objs.lights = (t_light*)malloc(sizeof(t_light) * s->obj_count.lc);
	if (!s->objs.lights)
		return ((int)error("failed to malloc"));
	return (LIGHTS);
}
