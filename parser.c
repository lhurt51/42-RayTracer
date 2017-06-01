/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

unsigned		check_enum(t_scene *s, char *str, unsigned *size)
{
	char		**tmp;
	unsigned	rtn;

	rtn = 0;
	tmp = ft_strsplit(str, ' ');
	if (ft_strequ("settings:", str_low(str)))
		rtn = set_settings(size);
	else if (ft_strequ("materials:", str_low(tmp[0])))
		rtn = set_materials(s, tmp[1], size);
	else if (ft_strequ("lights:", str_low(tmp[0])))
		rtn = set_lights(s, tmp[1], size);
	else if (ft_strequ("spheres:", str_low(tmp[0])))
		rtn = set_spheres(s, tmp[1], size);
	else if (ft_strequ("cylinders:", str_low(tmp[0])))
		rtn = set_cylinders(s, tmp[1], size);
	else if (ft_strequ("cones:", str_low(tmp[0])))
		rtn = set_cones(s, tmp[1], size);
	else if (ft_strequ("planes:", str_low(tmp[0])))
		rtn = set_planes(s, tmp[1], size);
	memdel_2d(tmp);
	return (rtn == 0 ? (int)error(ft_strjoin(s->name, ": wrong category name"))
		: rtn);
}

unsigned		store_props(t_scene *s, char *str, unsigned type, unsigned i)
{
	char		**tmp;
	unsigned	rtn;

	rtn = 0;
	tmp = ft_strsplit(ft_strtrim(str, '\t'), ' ');
	if (type == SETTINGS)
		rtn = store_settings(s, tmp);
	else if (type == MATERIALS)
		rtn = store_materials(s, tmp, i);
	else if (type == LIGHTS)
		rtn = store_lights(s, tmp, i);
	else if (type == SPHERES)
		rtn = store_spheres(s, tmp, i);
	else if (type == CYLINDERS)
		rtn = store_cylinders(s, tmp, i);
	else if (type == CONES)
		rtn = store_cones(s, tmp, i);
	else if (type == PLANES)
		rtn = store_planes(s, tmp, i);
	memdel_2d(tmp);
	return (rtn == 0 ? (int)error(ft_strjoin(s->name, ": wrong type")) : rtn);
}

unsigned		check_size(t_scene *s, unsigned type, unsigned size)
{
	if (type == SETTINGS && size != 0)
	{
		return ((int)error(ft_strjoin(s->name,
			": too many settings sections, only use 1 section")));
	}
	else if (type == MATERIALS && size >= s->obj_count.mc)
		return ((int)error(ft_strjoin(s->name, ": too many materials")));
	else if (type == LIGHTS && size >= s->obj_count.lc)
		return ((int)error(ft_strjoin(s->name, ": too many lights")));
	else if (type == SPHERES && size >= s->obj_count.sc)
		return ((int)error(ft_strjoin(s->name, ": too many spheres")));
	else if (type == CYLINDERS && size >= s->obj_count.cyc)
		return ((int)error(ft_strjoin(s->name, ": too many cylinders")));
	else if (type == CONES && size >= s->obj_count.cnc)
		return ((int)error(ft_strjoin(s->name, ": too many cones")));
	else if (type == PLANES && size >= s->obj_count.pc)
		return ((int)error(ft_strjoin(s->name, ": too many planes")));
	else
		return (1);
}

int				read_file(char *av, t_scene *scene)
{
	char			*tmp;
	int				fd;
	unsigned		cur;
	unsigned		size;

	size = 0;
	if (!check_fd(av))
		return (0);
	fd = open(av, O_RDONLY);
	scene->name = ft_strdup(av);
	while (get_next_line(fd, &tmp))
	{
		if (ft_isalpha(tmp[0]) && size != 0)
			return ((int)error(ft_strjoin(av, ": wrong catergory size")));
		else if (ft_isalpha(tmp[0]) && !(cur = check_enum(scene, tmp, &size)))
			return (0);
		else if (tmp[0] == '\t' && !store_props(scene, tmp, cur, size - 1))
			return (0);
		else if (!tmp[0] && !check_size(scene, cur, (--size)))
			return (0);
	}
	close(fd);
	return (1);
}
