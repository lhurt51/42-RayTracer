/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	pixel_to_img(t_mlx *new, int x, int y, t_color color)
{
	int		i;

	i = (x * 4) + (y * new->size_line);
	if (i > 0)
	{
		new->data[i++] = (unsigned char)MIN(color.blue*255.0f, 255.0f);
		new->data[i++] = (unsigned char)MIN(color.green*255.0f, 255.0f);
		new->data[i] = (unsigned char)MIN(color.red*255.0f, 255.0f);
	}
}

int				exit_hook(t_env *obj)
{
	if (obj->mlx.win)
		mlx_destroy_window(obj->mlx.mlx, obj->mlx.win);
	if (obj->mlx.img)
		mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	if (obj->mc)
		ft_memdel((void**)&obj->materials);
	if (obj->lc)
		ft_memdel((void**)&obj->lights);
	if (obj->sc)
		ft_memdel((void**)&obj->spheres);
	free(obj);
	exit(0);
}

int		my_key_press(int keycode, t_env *obj)
{
	if (keycode == 53)
		exit_hook(obj);
	// if (keycode == 257)
	// 	obj->mlx.keys.shift = 1;
	// if (keycode == 0)
	// 	obj->mlx.keys.a = 1;
	// if (keycode == 1)
	// 	obj->mlx.keys.s = 1;
	// if (keycode == 2)
	// 	obj->mlx.keys.d = 1;
	// if (keycode == 13)
	// 	obj->mlx.keys.w = 1;
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

t_vector	vect_sub(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

t_vector	vect_add(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vector	vect_scale(float scale, t_vector *v)
{
	t_vector	res;

	res.x = v->x * scale;
	res.y = v->y * scale;
	res.z = v->z * scale;
	return (res);
}

float		vect_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

int			ray_intersect_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vector	dist;
	float		a;
	float		b;
	float		c;
	float		discr;
	float		discr_sq;
	float		t0;
	float		t1;

	dist = vect_sub(&ray->start, &sphere->pos);
	a = vect_dot(&ray->dir, &ray->dir);
	b = 2 * vect_dot(&ray->dir, &dist);
	c = vect_dot(&dist, &dist) - (sphere->radius * sphere->radius);
	discr = b * b - 4 * a * c;

	if (discr < 0)
		return (0);
	else
	{
		discr_sq = sqrtf(discr);
		t0 = ((-b + discr_sq) / 2);
		t1 = ((-b - discr_sq) / 2);

		if (t0 > t1)
			t0 = t1;

		if ((t0 > 0.001f) && (t0 < *t))
		{
			*t = t0;
			return (1);
		}
		else
			return (0);
	}
}

void		draw_sphere(t_env *obj)
{
	t_vector		scaled, new_start, norm, dist, rtn;
	t_ray			light_ray;
	t_mat			cur_mat;
	t_light			cur_light;
	t_color			color;
	int				x, y, level, cur_sphere;
	unsigned		i;
	float			t, coef, tmp, lambert, reflect, k;

	obj->mc = 3;
	obj->materials = (t_mat*)malloc(sizeof(t_mat) * obj->mc);

	obj->materials[0].diffuse.red = 1;
	obj->materials[0].diffuse.green = 0;
	obj->materials[0].diffuse.blue = 0;
	obj->materials[0].reflection = 0.2;

	obj->materials[1].diffuse.red = 0;
	obj->materials[1].diffuse.green = 1;
	obj->materials[1].diffuse.blue = 0;
	obj->materials[1].reflection = 0.5;

	obj->materials[2].diffuse.red = 0;
	obj->materials[2].diffuse.green = 0;
	obj->materials[2].diffuse.blue = 1;
	obj->materials[2].reflection = 0.9;

	obj->sc = 3;
	obj->spheres = (t_sphere*)malloc(sizeof(t_sphere) * obj->sc);

	obj->spheres[0].pos.x = 200;
	obj->spheres[0].pos.y = 300;
	obj->spheres[0].pos.z = 0;
	obj->spheres[0].radius = 100;
	obj->spheres[0].mat = 0;

	obj->spheres[1].pos.x = 400;
	obj->spheres[1].pos.y = 400;
	obj->spheres[1].pos.z = 0;
	obj->spheres[1].radius = 100;
	obj->spheres[1].mat = 1;

	obj->spheres[2].pos.x = 500;
	obj->spheres[2].pos.y = 140;
	obj->spheres[2].pos.z = 0;
	obj->spheres[2].radius = 100;
	obj->spheres[2].mat = 2;

	obj->lc = 3;
	obj->lights = (t_light*)malloc(sizeof(t_light) * obj->lc);

	obj->lights[0].pos.x = 0;
	obj->lights[0].pos.y = 240;
	obj->lights[0].pos.z = -100;
	obj->lights[0].intensity.red = 1;
	obj->lights[0].intensity.green = 1;
	obj->lights[0].intensity.blue = 1;

	obj->lights[1].pos.x = 3200;
	obj->lights[1].pos.y = 3000;
	obj->lights[1].pos.z = -1000;
	obj->lights[1].intensity.red = 0.6;
	obj->lights[1].intensity.green = 0.7;
	obj->lights[1].intensity.blue = 1;

	obj->lights[2].pos.x = 600;
	obj->lights[2].pos.y = 0;
	obj->lights[2].pos.z = -100;
	obj->lights[2].intensity.red = 0.3;
	obj->lights[2].intensity.green = 0.5;
	obj->lights[2].intensity.blue = 1;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			level = 0;
			coef = 1.0;

			color.red = 0;
			color.green = 0;
			color.blue = 0;

			obj->ray.start.x = x;
			obj->ray.start.y = y;
			obj->ray.start.z = -2000;

			obj->ray.dir.x = 0;
			obj->ray.dir.y = 0;
			obj->ray.dir.z = 1;

			while ((coef > 0.0f) && (level < RAY_DEPTH))
			{
				t = 20000.0f;
				cur_sphere = -1;

				i = 0;
				while (i < obj->sc)
				{
					if (ray_intersect_sphere(&obj->ray, &obj->spheres[i], &t))
						cur_sphere = i;
					i++;
				}
				if (cur_sphere == -1)
					break;
				scaled = vect_scale(t, &obj->ray.dir);
				new_start = vect_add(&obj->ray.start, &scaled);
				norm = vect_sub(&new_start, &obj->spheres[cur_sphere].pos);
				if (!(tmp = vect_dot(&norm, &norm)))
					break;
				tmp = 1.0f / sqrtf(tmp);
				norm = vect_scale(tmp, &norm);
				cur_mat = obj->materials[obj->spheres[cur_sphere].mat];
				i = 0;
				while (i < obj->lc)
				{
					cur_light = obj->lights[i++];
					dist = vect_sub(&cur_light.pos, &new_start);
					if (vect_dot(&norm, &dist) > 0.0f)
						if ((k = sqrtf(vect_dot(&dist, &dist))) > 0.0f)
						{
							light_ray.start = new_start;
							light_ray.dir = vect_scale((1/k), &dist);
							lambert = vect_dot(&light_ray.dir, &norm) * coef;
							color.red += lambert * cur_light.intensity.red * cur_mat.diffuse.red;
							color.green += lambert * cur_light.intensity.green * cur_mat.diffuse.green;
							color.blue += lambert * cur_light.intensity.blue * cur_mat.diffuse.blue;
						}
				}
				coef *= cur_mat.reflection;
				obj->ray.start = new_start;
				reflect = 2.0f * vect_dot(&obj->ray.dir, &norm);
				rtn = vect_scale(reflect, &norm);
				obj->ray.dir = vect_sub(&obj->ray.dir, &rtn);
				level++;
			}
			pixel_to_img(&obj->mlx, x, y, color);
			x++;
		}
		y++;
	}
}

int			run_img(t_env *obj)
{
	if (obj->mlx.img)
		mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	obj->mlx.data = mlx_get_data_addr(obj->mlx.img, &obj->mlx.bits,
		&obj->mlx.size_line, &obj->mlx.endian);
	draw_sphere(obj);
	mlx_put_image_to_window(obj->mlx.mlx, obj->mlx.win, obj->mlx.img, 0, 0);
	return (0);
}

void		setup_struct(t_env *obj)
{
	obj->sc = 1;
	obj->ray.dir.x = 0;
	obj->ray.dir.y = 0;
	obj->ray.dir.z = 1;
}

void		create_win(t_env *obj)
{
	obj->mlx.mlx = mlx_init();
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, W_WIDTH, W_HEIGHT, "Wolf3D");
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	// setup_struct(obj);
	// run_img(obj);
	mlx_hook(obj->mlx.win, 17, 0, exit_hook, obj);
	mlx_hook(obj->mlx.win, 2, 0, my_key_press, obj);
	// mlx_hook(obj->mlx.win, 3, 0, my_key_release, obj);
	mlx_loop_hook(obj->mlx.mlx, run_img, obj);
	mlx_loop(obj->mlx.mlx);
}

int			main(int argc, char **argv)
{
	t_env		*obj;

	argc = 0;
	argv = NULL;
	obj = malloc(sizeof(t_env));
	create_win(obj);
	return (0);
}
