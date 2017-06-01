/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int		exit_hook(t_env *obj)
{
	static unsigned i = 0;

	if (obj->mlx.win)
		mlx_destroy_window(obj->mlx.mlx, obj->mlx.win);
	if (obj->mlx.img)
		mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	if (obj->scene.name)
		ft_strdel(&obj->scene.name);
	if (obj->scene.obj_count.mc)
		ft_memdel((void**)&obj->scene.objs.materials);
	if (obj->scene.obj_count.lc)
		ft_memdel((void**)&obj->scene.objs.lights);
	if (obj->scene.obj_count.sc)
		ft_memdel((void**)&obj->scene.objs.spheres);
	if (obj->scene.obj_count.cyc)
		ft_memdel((void**)&obj->scene.objs.cylinders);
	if (obj->scene.obj_count.cnc)
		ft_memdel((void**)&obj->scene.objs.cones);
	if (obj->scene.obj_count.pc)
		ft_memdel((void**)&obj->scene.objs.planes);
	free(obj);
	if (++i == obj->w_num)
		exit(0);
	return (0);
}

int		my_key_press(int keycode, t_env *obj)
{
	if (keycode == 53)
		exit_hook(obj);
	if (keycode == 49)
		obj->scene.shadows = (obj->scene.shadows != 0) ? 0 : 1;
	if (keycode == 24 && obj->scene.ray_depth < 20)
		obj->scene.ray_depth += 1;
	if (keycode == 27 && obj->scene.ray_depth > 1)
		obj->scene.ray_depth -= 1;
	if (keycode == 257)
		obj->mlx.keys.shift = 1;
	if (keycode == 0)
		obj->mlx.keys.a = 1;
	if (keycode == 1)
		obj->mlx.keys.s = 1;
	if (keycode == 2)
		obj->mlx.keys.d = 1;
	if (keycode == 13)
		obj->mlx.keys.w = 1;
	run_img(obj);
	return (0);
}

int		my_key_release(int keycode, t_env *obj)
{
	if (keycode == 257)
		obj->mlx.keys.shift = 0;
	if (keycode == 0)
		obj->mlx.keys.a = 0;
	if (keycode == 1)
		obj->mlx.keys.s = 0;
	if (keycode == 2)
		obj->mlx.keys.d = 0;
	if (keycode == 13)
		obj->mlx.keys.w = 0;
	return (0);
}
