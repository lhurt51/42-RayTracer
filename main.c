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
	exit(0);
}

# include <stdio.h>

void	print_vector(t_vector v)
{
	static unsigned i = 0;

	printf("Vector #%u (x.%f y.%f z.%f)\n", i, v.x, v.y, v.z);
	i++;
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

t_color		col_create(double r, double g, double b)
{
	t_color		color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color		col_mul_coef(t_color *c1, double coef)
{
	t_color		res;

	res.red = c1->red * coef;
	res.green = c1->green * coef;
	res.blue = c1->blue * coef;
	return (res);
}

t_color		col_add(t_color *c1, t_color *c2)
{
	t_color		res;

	res.red = c1->red + c2->red;
	res.green = c1->green + c2->green;
	res.blue = c1->blue + c2->blue;
	return (res);
}

t_color		col_mul(t_color *c1, t_color *c2)
{
	t_color		res;

	res.red = c1->red * c2->red;
	res.green = c1->green * c2->green;
	res.blue = c1->blue * c2->blue;
	return (res);
}

t_vector	vect_create(double x, double y, double z)
{
	t_vector	vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
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

t_vector	vect_scale(double scale, t_vector *v)
{
	t_vector	res;

	res.x = v->x * scale;
	res.y = v->y * scale;
	res.z = v->z * scale;
	return (res);
}

t_vector	vect_cross(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = (v1->z * v2->x) - (v1->x * v2->z);
	res.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (res);
}

float		vect_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

double		vect_norm(t_vector *v)
{
	double		dist;
	double		tmp;

	if ((dist = vect_dot(v, v)) == 0.0f)
		return (dist);
	tmp = INVSQRTF(dist);
	*v = vect_scale(tmp, v);
	return (dist);
}

int			ray_intersect_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	t_vector	dist;
	int			rtn;
	double		b;
	double		discr;
	double		t0;
	double		t1;

	rtn = 0;
	dist = vect_sub(&sphere->pos, &ray->start);
	b = vect_dot(&ray->dir, &dist);
	discr = SQ(b) - vect_dot(&dist, &dist) + SQ(sphere->radius);
	if (discr < 0.0f)
		return (rtn);
	t0 = (b - sqrtf(discr));
	t1 = (b + sqrtf(discr));
	if ((t0 > 0.1f) && (t0 < *t))
	{
		*t = t0;
		rtn = 1;
	}
	if ((t1 > 0.1f) && (t1 < *t))
	{
		*t = t1;
		rtn = 1;
	}
	return (rtn);
}

int			ray_intersect_cylinder(t_ray *ray, t_cylinder *c, double *t, int flip)
{
	t_vector	dist;
	t_vector	tmp;
	t_vector	cr;
	double		b;
	double		discr;
	double		t0;
	double		t1;
	double		answ;

	// Need to use the rotation of the cylinder it is seg faulting right now
	cr = vect_scale(vect_dot(&ray->dir, &c->rot), &c->rot);
	cr = vect_sub(&ray->dir, &cr);
	dist = vect_sub(&ray->start, &c->pos);
	tmp = vect_scale(vect_dot(&dist, &c->rot), &c->rot);
	dist = vect_sub(&dist, &tmp);
	b = 2 * vect_dot(&cr, &dist);
	discr = SQ(b) - 4 * vect_dot(&cr, &cr)
		* (vect_dot(&dist, &dist) - SQ(c->radius));
	answ = (-b + sqrtf(discr)) / (2 * vect_dot(&cr, &cr));
	if (discr > 0.0f)
	{
		t0 = (-b - sqrtf(discr)) / (2 * vect_dot(&cr, &cr));
		t1 = (-b + sqrtf(discr)) / (2 * vect_dot(&cr, &cr));
		answ = ((MIN(t1, t0) < 0) ^ flip ? MAX(t1, t0) : MIN(t1, t0));
	}
	if ((discr >= 0) && (answ > 0.1f) && (answ < *t))
		*t = answ;
	return (*t == answ);
}

int			ray_intersect_cone(t_ray *ray, t_cone *cn, double *t, int flip)
{
	t_vector	dist;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		tmp[3];

	dist = vect_sub(&ray->start, &cn->pos);
	a = vect_dot(&ray->dir, &ray->dir) - ((1 + SQ(cn->radius))) * vect_dot(&ray->dir, &cn->rot) * vect_dot(&ray->dir, &cn->rot);
	b = 2 * (vect_dot(&ray->dir, &dist) - ((1 + SQ(cn->radius))) * vect_dot(&ray->dir, &cn->rot) * vect_dot(&dist, &cn->rot));
	c = vect_dot(&dist, &dist) - ((1 + SQ(cn->radius))) * vect_dot(&dist, &cn->rot) * vect_dot(&dist, &cn->rot);
	discr = SQ(b) - 4 * a * c;
	if (discr == 0.0f)
		tmp[2] = (-b + sqrtf(discr)) / (2 * a);
	else if (discr > 0.0f)
	{
		tmp[0] = (-b + sqrtf(discr)) / (2 * a);
		tmp[1] = (-b - sqrtf(discr)) / (2 * a);
		tmp[2] = (tmp[0] < tmp[1]) ^ flip ? tmp[0] : tmp[1];
		tmp[2] = (tmp[2] < 0.0f) ? tmp[1] : tmp[2];
	}
	if ((tmp[2] > 0.1f) && (tmp[2] < *t))
		*t = tmp[2];
	return (*t == tmp[2]);
}

int			ray_intersect_plane(t_ray *ray, t_plane *p, double *t)
{
	t_vector	dist;
	double		norm;
	double		discr;
	double		answ;

	dist = vect_sub(&p->pos, &ray->start);
	norm = vect_dot(&p->rot, &dist);
	discr = vect_dot(&p->rot, &ray->dir);
	if ((answ = norm / discr) > 0.1 && (answ < *t))
		*t = answ;
	return (*t == answ);
}

t_color		apply_specular(t_env *obj, t_ray light_ray, double light_proj)
{
	t_vector blinn_dir;
	t_color	rtn;
	double view_proj;
	double tmp;
	double blinn;

	/* Blinn-Phong's Specular Lighting */
	rtn = col_create(0, 0, 0);
	view_proj = vect_dot(&obj->draw_data.ray.dir, &obj->draw_data.norm);
	blinn_dir = vect_sub(&light_ray.dir, &obj->draw_data.ray.dir);
	tmp = vect_dot(&blinn_dir, &blinn_dir);
	if (tmp != 0.0f)
	{
		blinn = INVSQRTF(tmp) * MAX(light_proj - view_proj, 0.0f);
		blinn = obj->draw_data.coef * powf(blinn, obj->draw_data.cur_objs.cur_mat.power);
		rtn = col_mul_coef(&obj->draw_data.cur_objs.cur_mat.specular, blinn);
		rtn = col_mul(&rtn, &obj->draw_data.cur_objs.cur_light.intensity);
	}
	return (rtn);
}

void		apply_reflection(t_env *obj)
{
	t_vector	rtn;
	double		reflect;

	obj->draw_data.coef *= obj->draw_data.cur_objs.cur_mat.reflection;
	reflect = 2.0f * vect_dot(&obj->draw_data.ray.dir, &obj->draw_data.norm);
	// obj->draw_data.ray.start = new_start;
	rtn = vect_scale(reflect, &obj->draw_data.norm);
	obj->draw_data.ray.dir = vect_sub(&obj->draw_data.ray.dir, &rtn);
}

void		correct_gamma(t_color *color)
{
	//Fixed gamma value from sRGB standard
	double invgamma;

	invgamma = 0.45f;
	color->blue = powf(color->blue, invgamma);
	color->red = powf(color->red, invgamma);
	color->green = powf(color->green, invgamma);
}

void		handle_light(t_env *obj, t_color *color)
{
	t_ray		light_ray;
	t_color		tmp_color;
	double		lambert, light_proj, t;
	int			shadow;
	unsigned	i, j;

	i = 0;
	light_ray.start = obj->draw_data.ray.start;
	while (i < obj->scene.obj_count.lc)
	{
		shadow = 0;
		obj->draw_data.cur_objs.cur_light = obj->scene.objs.lights[i++];
		light_ray.dir = vect_sub(&obj->draw_data.cur_objs.cur_light.pos, &obj->draw_data.ray.start);
		if ((light_proj = vect_dot(&light_ray.dir, &obj->draw_data.norm)) > 0.0f)
		{
			if ((t = vect_norm(&light_ray.dir)))
			{
				light_proj = INVSQRTF(t) * light_proj;
				j = 0;
				while (j < obj->scene.obj_count.sc && !shadow)
					if ((shadow = ray_intersect_sphere(&light_ray, &obj->scene.objs.spheres[j++], &t)))
						break;
				j = 0;
				while (j < obj->scene.obj_count.cyc && !shadow)
					if ((shadow = ray_intersect_cylinder(&light_ray, &obj->scene.objs.cylinders[j++], &t, obj->draw_data.flip)))
						break;
				j = 0;
				while (j < obj->scene.obj_count.cnc && !shadow)
					if ((shadow = ray_intersect_cone(&light_ray, &obj->scene.objs.cones[j++], &t, obj->draw_data.flip)))
						break;
				j = 0;
				while (j < obj->scene.obj_count.pc && !shadow)
					if ((shadow = ray_intersect_plane(&light_ray, &obj->scene.objs.planes[j++], &t)))
						break;
				if (!shadow)
				{
					lambert = vect_dot(&light_ray.dir, &obj->draw_data.norm) * obj->draw_data.coef;
					color->red += lambert * obj->draw_data.cur_objs.cur_light.intensity.red * obj->draw_data.cur_objs.cur_mat.diffuse.red;
					color->green += lambert * obj->draw_data.cur_objs.cur_light.intensity.green * obj->draw_data.cur_objs.cur_mat.diffuse.green;
					color->blue += lambert * obj->draw_data.cur_objs.cur_light.intensity.blue * obj->draw_data.cur_objs.cur_mat.diffuse.blue;
					tmp_color = apply_specular(obj, light_ray, light_proj);
					*color = col_add(color, &tmp_color);
				}
			}
		}
	}
}

void		check_norm(t_env *obj)
{
	if (vect_dot(&obj->draw_data.norm, &obj->draw_data.ray.dir) > 0.0f)
	{
		obj->draw_data.norm = vect_scale(-1.0f, &obj->draw_data.norm);
		obj->draw_data.flip = 1;
	}
	else
		obj->draw_data.flip = 0;
}

int			hit_obj(t_env *obj, t_color *color, double t)
{
	t_vector	scaled;
	// double		tmp;

	// Need to add a camera position and translation
	// Need to thin out repeated code and make another function
	scaled = vect_scale(t, &obj->draw_data.ray.dir);
	obj->draw_data.ray.start = vect_add(&obj->draw_data.ray.start, &scaled);
	if (obj->draw_data.cur_objs.cur_sphere != -1)
	{
		obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[obj->scene.objs.spheres[obj->draw_data.cur_objs.cur_sphere].mat];
		obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &obj->scene.objs.spheres[obj->draw_data.cur_objs.cur_sphere].pos);
		check_norm(obj);
		if (!vect_norm(&obj->draw_data.norm))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_cylinder != -1)
	{
		t_vector	projection;

		obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_cylinder].mat];
		obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_cylinder].pos);
		projection = vect_scale(vect_dot(&obj->draw_data.norm, &obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_cylinder].rot), &obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_cylinder].rot);
		obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection);
		check_norm(obj);
		if (!vect_norm(&obj->draw_data.norm))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_cone != -1)
	{
		t_vector		projection1;

		obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[obj->scene.objs.cones[obj->draw_data.cur_objs.cur_cone].mat];
		obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &obj->scene.objs.cones[obj->draw_data.cur_objs.cur_cone].pos);
		projection1 = vect_scale(vect_dot(&obj->draw_data.norm, &obj->scene.objs.cones[obj->draw_data.cur_objs.cur_cone].rot), &obj->scene.objs.cones[obj->draw_data.cur_objs.cur_cone].rot);
		obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection1);
		check_norm(obj);
		if (!vect_norm(&obj->draw_data.norm))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_plane != -1)
	{
		obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[obj->scene.objs.planes[obj->draw_data.cur_objs.cur_plane].mat];
		obj->draw_data.norm = obj->scene.objs.planes[obj->draw_data.cur_objs.cur_plane].rot;
		if (vect_dot(&obj->draw_data.ray.dir, &obj->scene.objs.planes[obj->draw_data.cur_objs.cur_plane].rot) > 0.0f)
		{
			obj->draw_data.norm = vect_scale(-1.0f, &obj->draw_data.norm);
			obj->draw_data.flip = 1;
		}
		if (!vect_norm(&obj->draw_data.norm))
			return (0);
	}
	else
	{
		/* No hit - add background */
		t_color test = col_create(0, 0, 0);
		test = col_mul_coef(&test, obj->draw_data.coef);
		*color = col_add(color, &test);
		return (0);
	}
	return (1);
}

void		ray_tracing(t_env *obj, t_color *color)
{
	int				level;
	unsigned		i;
	double			t;

	level = 0;
	while ((obj->draw_data.coef > 0.0f) && (level < RAY_DEPTH))
	{
		t = 20000.0f;
		obj->draw_data.cur_objs.cur_sphere = -1;
		obj->draw_data.cur_objs.cur_cylinder = -1;
		obj->draw_data.cur_objs.cur_cone = -1;
		obj->draw_data.cur_objs.cur_plane = -1;
		obj->draw_data.flip = 0;

		i = 0;
		// Search for ray intersection with obj in env
		while (i < obj->scene.obj_count.sc)
		{
			if (ray_intersect_sphere(&obj->draw_data.ray, &obj->scene.objs.spheres[i], &t))
				obj->draw_data.cur_objs.cur_sphere = i;
			i++;
		}
		i = 0;
		while (i < obj->scene.obj_count.cyc)
		{
			if (ray_intersect_cylinder(&obj->draw_data.ray, &obj->scene.objs.cylinders[i], &t, obj->draw_data.flip))
			{
				obj->draw_data.cur_objs.cur_sphere = -1;
				obj->draw_data.cur_objs.cur_cylinder = i;
			}
			i++;
		}
		i = 0;
		while (i < obj->scene.obj_count.cnc)
		{
			if (ray_intersect_cone(&obj->draw_data.ray, &obj->scene.objs.cones[i], &t, obj->draw_data.flip))
			{
				obj->draw_data.cur_objs.cur_sphere = -1;
				obj->draw_data.cur_objs.cur_cylinder = -1;
				obj->draw_data.cur_objs.cur_cone = i;
			}
			i++;
		}
		i = 0;
		while (i < obj->scene.obj_count.pc)
		{
			if (ray_intersect_plane(&obj->draw_data.ray, &obj->scene.objs.planes[i], &t))
			{
				obj->draw_data.cur_objs.cur_sphere = -1;
				obj->draw_data.cur_objs.cur_cylinder = -1;
				obj->draw_data.cur_objs.cur_cone = -1;
				obj->draw_data.cur_objs.cur_plane = i;
			}
			i++;
		}
		if (!hit_obj(obj, color, t))
			break;
		if (!obj->draw_data.flip)
		{
			handle_light(obj, color);
			apply_reflection(obj);
		}
		level++;
	}
}

void		trace_each_pixel(t_env *obj)
{
	t_vector		tmp, tmp1;
	t_color			color;
	int				x, y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			obj->draw_data.coef = 1.0;
			color = col_create(0, 0, 0);
			tmp = vect_create(x, y, -1000.0f);
			obj->draw_data.ray.start = obj->scene.cam_pos;
			vec_mult_mat(&tmp, obj->draw_data.g_mat, &tmp1);
			obj->draw_data.ray.dir = vect_sub(&tmp1, &obj->draw_data.ray.start);
			vect_norm(&obj->draw_data.ray.dir);
			// if (!vect_norm(&obj->draw_data.ray.dir))
			// 	return (0);
			ray_tracing(obj, &color);
			correct_gamma(&color);
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
	trace_each_pixel(obj);
	mlx_put_image_to_window(obj->mlx.mlx, obj->mlx.win, obj->mlx.img, 0, 0);
	return (0);
}

void		setup_struct(t_env *obj)
{
	obj->scene.cam_pos = vect_create(0, 0, -1000);
	obj->scene.cam_rot = vect_create(0, -150, 0);
	obj->scene.cam_rot = vect_scale(M_PI / 180, &obj->scene.cam_rot);

	mat_identity(obj->draw_data.g_mat);
	mat_rotate(obj->draw_data.g_mat, obj->scene.cam_rot.x, obj->scene.cam_rot.y, obj->scene.cam_rot.z);
	mat_translate(obj->draw_data.g_mat, obj->scene.cam_pos.x, obj->scene.cam_pos.y, obj->scene.cam_pos.z);

	obj->scene.obj_count.mc = 4;
	obj->scene.objs.materials = (t_mat*)malloc(sizeof(t_mat) * obj->scene.obj_count.mc);

	obj->scene.objs.materials[0].diffuse = col_create(1, 0, 0);
	obj->scene.objs.materials[0].specular = col_create(1, 1, 1);
	obj->scene.objs.materials[0].reflection = 0.2;
	obj->scene.objs.materials[0].power = 60;

	obj->scene.objs.materials[1].diffuse = col_create(0, 1, 0);
	obj->scene.objs.materials[1].specular = col_create(1, 1, 1);
	obj->scene.objs.materials[1].reflection = 0.5;
	obj->scene.objs.materials[1].power = 60;

	obj->scene.objs.materials[2].diffuse = col_create(0, 0, 1);
	obj->scene.objs.materials[2].specular = col_create(0.1, 0.1, 0.1);
	obj->scene.objs.materials[2].reflection = 0.9;
	obj->scene.objs.materials[2].power = 60;

	obj->scene.objs.materials[3].diffuse = col_create(0.5, 0.5, 0.5);
	obj->scene.objs.materials[3].specular = col_create(0.5, 0.5, 0.5);
	obj->scene.objs.materials[3].reflection = 0;
	obj->scene.objs.materials[3].power = 60;

	obj->scene.obj_count.sc = 2;
	obj->scene.objs.spheres = (t_sphere*)malloc(sizeof(t_sphere) * obj->scene.obj_count.sc);

	obj->scene.objs.spheres[0].pos = vect_create(200, 400, 10);
	obj->scene.objs.spheres[0].radius = 100;
	obj->scene.objs.spheres[0].mat = 0;

	obj->scene.objs.spheres[1].pos = vect_create(600, 245, 120);
	obj->scene.objs.spheres[1].radius = 100;
	obj->scene.objs.spheres[1].mat = 2;

	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, -1, 0);
	mat_identity(mat);
	mat_rotate(mat, 0, 0, -(45 * M_PI / 180));

	obj->scene.obj_count.cyc = 1;
	obj->scene.objs.cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * obj->scene.obj_count.cyc);

	obj->scene.objs.cylinders[0].pos = vect_create(200, 600, 500);
	vec_mult_mat(&tmp, mat, &obj->scene.objs.cylinders[0].rot);
	obj->scene.objs.cylinders[0].radius = 100;
	obj->scene.objs.cylinders[0].mat = 1;

	float		mat2[4][4];

	mat_identity(mat2);
	mat_rotate(mat2, 0, 0, (45 * M_PI / 180));

	obj->scene.obj_count.cnc = 1;
	obj->scene.objs.cones = (t_cone*)malloc(sizeof(t_cone) * obj->scene.obj_count.cnc);

	obj->scene.objs.cones[0].pos = vect_create(650, 300, 400);
	vec_mult_mat(&tmp, mat2, &obj->scene.objs.cones[0].rot);
	obj->scene.objs.cones[0].radius = 0.5;
	obj->scene.objs.cones[0].mat = 2;

	t_vector	tmp1;
	float		mat1[4][4];

	tmp1 = vect_create(0, 0, -1);
	mat_identity(mat1);
	mat_rotate(mat1, -(90 * M_PI / 180), 0, 0);

	obj->scene.obj_count.pc = 1;
	obj->scene.objs.planes = (t_plane*)malloc(sizeof(t_plane) * obj->scene.obj_count.pc);

	obj->scene.objs.planes[0].pos = vect_create(0, 550, 0);
	vec_mult_mat(&tmp1, mat1, &obj->scene.objs.planes[0].rot);
	obj->scene.objs.planes[0].mat = 3;

	obj->scene.obj_count.lc = 2;
	obj->scene.objs.lights = (t_light*)malloc(sizeof(t_light) * obj->scene.obj_count.lc);

	obj->scene.objs.lights[0].pos = vect_create(300, 300, -600);
	obj->scene.objs.lights[0].intensity = col_create(1, 1, 1);

	obj->scene.objs.lights[1].pos = vect_create(500, 100, -200);
	obj->scene.objs.lights[1].intensity = col_create(0.3, 0.5, 1);
}

void		create_win(t_env *obj)
{
	setup_struct(obj);
	obj->mlx.mlx = mlx_init(); // Same mlx different windows for multiple windows
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, W_WIDTH, W_HEIGHT, "RTv1");
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	// run_img(obj);
	mlx_hook(obj->mlx.win, 17, 0, exit_hook, obj);
	mlx_hook(obj->mlx.win, 2, 0, my_key_press, obj);
	// mlx_hook(obj->mlx.win, 3, 0, my_key_release, obj);
	mlx_loop_hook(obj->mlx.mlx, run_img, obj);
	mlx_loop(obj->mlx.mlx);
}

unsigned int	check_fd(char *av)
{
	int				fd;
	char			*tmp;
	unsigned int	count;

	count = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return ((int)error(ft_strjoin(av, ": failed to open")));
	while (get_next_line(fd, &tmp))
		count++;
	close(fd);
	return (count == 0 ? (int)error(ft_strjoin(av, ": is empty")) : count);
}

unsigned		check_enum(t_scene *s, char *str, unsigned *size)
{
	char	**tmp; // mem delete this

	tmp = ft_strsplit(str, ' ');
	if (ft_strequ("settings:", str_low(str)))
	{
		*size = 1;
		return (SETTINGS);
	}
	else if (ft_strequ("materials:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.mc = *size;
		s->objs.materials = (t_mat*)malloc(sizeof(t_mat) * s->obj_count.mc);
		if (!s->objs.materials)
			return ((int)error("failed to malloc"));
		return (MATERIALS);
	}
	else if (ft_strequ("lights:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.lc = *size;
		s->objs.lights = (t_light*)malloc(sizeof(t_light) * s->obj_count.lc);
		if (!s->objs.lights)
			return ((int)error("failed to malloc"));
		return (LIGHTS);
	}
	else if (ft_strequ("spheres:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.sc = *size;
		s->objs.spheres = (t_sphere*)malloc(sizeof(t_sphere) * s->obj_count.sc);
		if (!s->objs.spheres)
			return ((int)error("failed to malloc"));
		return (SPHERES);
	}
	else if (ft_strequ("cylinders:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.cyc = *size;
		s->objs.cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * s->obj_count.cyc);
		if (!s->objs.cylinders)
			return ((int)error("failed to malloc"));
		return (CYLINDERS);
	}
	else if (ft_strequ("cones:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.cnc = *size;
		s->objs.cones = (t_cone*)malloc(sizeof(t_cone) * s->obj_count.cnc);
		if (!s->objs.cones)
			return ((int)error("failed to malloc"));
		return (CONES);
	}
	else if (ft_strequ("planes:", str_low(tmp[0])))
	{
		*size = ft_atoi(tmp[1]);
		s->obj_count.pc = *size;
		s->objs.planes = (t_plane*)malloc(sizeof(t_plane) * s->obj_count.pc);
		if (!s->objs.planes)
			return ((int)error("failed to malloc"));
		return (PLANES);
	}
	return ((int)error(ft_strjoin(s->name, ": wrong category name")));
}

t_vector		parse_tripple(char *str)
{
	char		**t_s; // mem delete this
	t_vector	tmp;

	// I have to handle doubles
	t_s = ft_strsplit(ft_strtrim(ft_strtrim(str, '('), ')'), ',');
	if (t_s[2] && !t_s[3])
		tmp = vect_create(atoi(t_s[0]), atoi(t_s[1]), atoi(t_s[2]));
	else
		tmp = vect_create(0, 0, 0);
	print_vector(tmp);
	return (tmp);
}

t_color		parse_color(char *str)
{
	t_vector	tmp;
	t_color		rtn;

	tmp = parse_tripple(str);
	rtn = col_create(tmp.x, tmp.y, tmp.z);
	return (rtn);
}

t_vector		parse_rot(char *str)
{
	t_vector	tmp;

	tmp = parse_tripple(str);
	tmp = vect_scale(M_PI / 180, &tmp);
	return (tmp);
}

unsigned		store_settings(t_scene *s, char **str)
{
	if (ft_strequ("width:", str[0]))
		s->w_width = atoi(str[1]);
	else if (ft_strequ("height:", str[0]))
		s->w_height = atoi(str[1]);
	else if (ft_strequ("ray_depth:", str[0]))
		s->ray_depth = atoi(str[1]);
	else if (ft_strequ("cam_pos:", str[0]))
		s->cam_pos = parse_tripple(str[1]);
	else if (ft_strequ("cam_rot:", str[0]))
		s->cam_pos = parse_rot(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong settings options")));
	return (1);
}

unsigned		store_materials(t_scene *s, char **str, unsigned i)
{
	ft_printf("1: %s, 2: %s, index: %u\n", str[0], str[1], i);
	if (ft_strequ("", str[0]))
		s->objs.materials[i].diffuse = parse_color(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong materials options")));
	return (1);
}

unsigned		store_props(t_scene *s, char *str, unsigned type, unsigned i)
{
	char	**tmp; // mem delete this

	ft_printf("str: %s\n" , str);
	tmp = ft_strsplit(ft_strtrim(str, '\t'), ' ');
	if (type == SETTINGS)
		return (store_settings(s, tmp));
	else if (type == MATERIALS)
		return (store_materials(s, tmp, i));
	else if (type == LIGHTS)
		return (1);
	else if (type == SPHERES)
		return (1);
	else if (type == CYLINDERS)
		return (1);
	else if (type == CONES)
		return (1);
	else if (type == PLANES)
		return (1);
	else
		return (NONE);
}
//
unsigned		check_size(t_scene *s, unsigned type, unsigned size)
{
	if (type == SETTINGS && size == 0)
		return (1);
	else if (type == MATERIALS && size < s->obj_count.mc)
		return (1);
	else if (type == LIGHTS && size < s->obj_count.lc)
		return (1);
	else if (type == SPHERES && size < s->obj_count.sc)
		return (1);
	else if (type == CYLINDERS && size < s->obj_count.cyc)
		return (1);
	else if (type == CONES && size < s->obj_count.cnc)
		return (1);
	else if (type == PLANES && size < s->obj_count.cnc)
		return (1);
	else
		return (NONE);
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
			return ((int)error(ft_strjoin(av, ": wrong amount of objs")));
	}
	close(fd);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env		*obj;
	// void		*mlx;
	t_scene		*s;

	s = malloc(sizeof(t_scene));
	if (!s)
		return (0);
	if (argc == 2)
		read_file(argv[1], s);
	obj = malloc(sizeof(t_env));
	create_win(obj);
	return (0);
}
