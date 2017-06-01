/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

unsigned		store_settings(t_scene *s, char **str)
{
	if (ft_strequ("width:", str[0]))
		s->w_width = atoi(str[1]);
	else if (ft_strequ("height:", str[0]))
		s->w_height = atoi(str[1]);
	else if (ft_strequ("ray_depth:", str[0]))
		s->ray_depth = atoi(str[1]);
	else if (ft_strequ("fov:", str[0]))
		s->fov = atoi(str[1]);
	else if (ft_strequ("shadows:", str[0]))
		s->shadows = atoi(str[1]);
	else if (ft_strequ("cam_pos:", str[0]))
		s->cam_pos = parse_tripple(str[1]);
	else if (ft_strequ("cam_rot:", str[0]))
		s->cam_rot = parse_rot(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong settings options")));
	return (1);
}

unsigned		store_materials(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("diffuse:", str[0]))
		s->objs.materials[i].diffuse = parse_color(str[1]);
	else if (ft_strequ("specular:", str[0]))
		s->objs.materials[i].specular = parse_color(str[1]);
	else if (ft_strequ("reflection:", str[0]))
		s->objs.materials[i].reflection = parse_double(str[1]);
	else if (ft_strequ("power:", str[0]))
		s->objs.materials[i].power = parse_double(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong material properties")));
	return (1);
}

unsigned		store_lights(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.lights[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("intensity:", str[0]))
		s->objs.lights[i].intensity = parse_color(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong light properties")));
	return (1);
}

unsigned		store_spheres(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.spheres[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("radius:", str[0]))
		s->objs.spheres[i].radius = parse_double(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.spheres[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong sphere properties")));
	return (1);
}
