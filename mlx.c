/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"
#include "includes/mat.h"

void	pixel_to_img(t_mlx *obj, int x, int y, t_color color)
{
	int		i;

	i = (x * 4) + (y * obj->size_line);
	if (i > 0)
	{
		obj->data[i++] = (unsigned char)MIN(color.blue*255.0f, 255.0f);
		obj->data[i++] = (unsigned char)MIN(color.green*255.0f, 255.0f);
		obj->data[i] = (unsigned char)MIN(color.red*255.0f, 255.0f);
	}
}

void		setup_struct(t_env *obj)
{
	mat_identity(obj->draw_data.g_mat);
	mat_rotate(obj->draw_data.g_mat, obj->scene.cam_rot.x, obj->scene.cam_rot.y,
		obj->scene.cam_rot.z);
	mat_translate(obj->draw_data.g_mat, obj->scene.cam_pos.x,
		obj->scene.cam_pos.y, obj->scene.cam_pos.z);
}

int			run_img(t_env *obj)
{
	setup_struct(obj);
	if (obj->mlx.img)
		mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, obj->scene.w_width,
		obj->scene.w_height);
	obj->mlx.data = mlx_get_data_addr(obj->mlx.img, &obj->mlx.bits,
		&obj->mlx.size_line, &obj->mlx.endian);
	trace_each_pixel(obj);
	mlx_put_image_to_window(obj->mlx.mlx, obj->mlx.win, obj->mlx.img, 0, 0);
	return (0);
}

void		create_win(t_env *obj)
{
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, obj->scene.w_width,
		obj->scene.w_height, ft_strjoin("RTv1 - ", obj->scene.name));
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, obj->scene.w_width,
		obj->scene.w_height);
	mlx_hook(obj->mlx.win, 17, 0, exit_hook, obj);
	mlx_hook(obj->mlx.win, 2, 0, my_key_press, obj);
	// mlx_hook(obj->mlx.win, 3, 0, my_key_release, obj);
	mlx_expose_hook(obj->mlx.win, run_img, obj);
}
