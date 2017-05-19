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

int			ray_intersect_cylinder(t_ray *ray, t_cylinder *c, double *t)
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
		answ = ((MIN(t1, t0) < 0) ^ 0 ? MAX(t1, t0) : MIN(t1, t0));
	}
	if ((discr >= 0) && (answ > 0.1f) && (answ < *t))
		*t = answ;
	return (*t == answ);
}

int			ray_intersect_cone(t_ray *ray, t_cone *cn, double *t)
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
		tmp[2] = (tmp[0] < tmp[1]) ^ 0 ? tmp[0] : tmp[1];
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
	view_proj = vect_dot(&obj->ray.dir, &obj->norm);
	blinn_dir = vect_sub(&light_ray.dir, &obj->ray.dir);
	tmp = vect_dot(&blinn_dir, &blinn_dir);
	if (tmp != 0.0f)
	{
		blinn = INVSQRTF(tmp) * MAX(light_proj - view_proj, 0.0f);
		blinn = obj->coef * powf(blinn, obj->cur_mat.power);
		rtn = col_mul_coef(&obj->cur_mat.specular, blinn);
		rtn = col_mul(&rtn, &obj->cur_light.intensity);
	}
	return (rtn);
}

void		apply_reflection(t_env *obj)
{
	t_vector	rtn;
	double		reflect;

	obj->coef *= obj->cur_mat.reflection;
	reflect = 2.0f * vect_dot(&obj->ray.dir, &obj->norm);
	// obj->ray.start = new_start;
	rtn = vect_scale(reflect, &obj->norm);
	obj->ray.dir = vect_sub(&obj->ray.dir, &rtn);
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
	light_ray.start = obj->ray.start;
	while (i < obj->lc)
	{
		shadow = 0;
		obj->cur_light = obj->lights[i++];
		light_ray.dir = vect_sub(&obj->cur_light.pos, &obj->ray.start);
		if ((light_proj = vect_dot(&light_ray.dir, &obj->norm)) > 0.0f)
		{
			if ((t = vect_norm(&light_ray.dir)))
			{
				light_proj = INVSQRTF(t) * light_proj;
				j = 0;
				while (j < obj->sc && !shadow)
					if ((shadow = ray_intersect_sphere(&light_ray, &obj->spheres[j++], &t)))
						break;
				j = 0;
				while (j < obj->cyc && !shadow)
					if ((shadow = ray_intersect_cylinder(&light_ray, &obj->cylinders[j++], &t)))
						break;
				j = 0;
				while (j < obj->cnc && !shadow)
					if ((shadow = ray_intersect_cone(&light_ray, &obj->cones[j++], &t)))
						break;
				j = 0;
				while (j < obj->pc && !shadow)
					if ((shadow = ray_intersect_plane(&light_ray, &obj->planes[j++], &t)))
						break;
				if (!shadow)
				{
					lambert = vect_dot(&light_ray.dir, &obj->norm) * obj->coef;
					color->red += lambert * obj->cur_light.intensity.red * obj->cur_mat.diffuse.red;
					color->green += lambert * obj->cur_light.intensity.green * obj->cur_mat.diffuse.green;
					color->blue += lambert * obj->cur_light.intensity.blue * obj->cur_mat.diffuse.blue;
					tmp_color = apply_specular(obj, light_ray, light_proj);
					*color = col_add(color, &tmp_color);
				}
			}
		}
	}
}

void		check_norm(t_env *obj, t_color *color)
{
	if (vect_dot(&obj->norm, &obj->ray.dir) > 0.0f)
		obj->norm = vect_scale(-1.0f, &obj->norm);
	handle_light(obj, color);
}

int			hit_obj(t_env *obj, t_color *color, double t)
{
	t_vector	scaled;
	// double		tmp;

	// Need to add a camera position and translation
	// Need to thin out repeated code and make another function
	scaled = vect_scale(t, &obj->ray.dir);
	obj->ray.start = vect_add(&obj->ray.start, &scaled);
	if (obj->cur_sphere != -1)
	{
		obj->cur_mat = obj->materials[obj->spheres[obj->cur_sphere].mat];
		obj->norm = vect_sub(&obj->ray.start, &obj->spheres[obj->cur_sphere].pos);
		if (!vect_norm(&obj->norm))
			return (0);
	}
	else if (obj->cur_cylinder != -1)
	{
		t_vector	projection;

		obj->cur_mat = obj->materials[obj->cylinders[obj->cur_cylinder].mat];
		obj->norm = vect_sub(&obj->ray.start, &obj->cylinders[obj->cur_cylinder].pos);
		projection = vect_scale(vect_dot(&obj->norm, &obj->cylinders[obj->cur_cylinder].rot), &obj->cylinders[obj->cur_cylinder].rot);
		obj->norm = vect_sub(&obj->norm, &projection);
		if (!vect_norm(&obj->norm))
			return (0);
	}
	else if (obj->cur_cone != -1)
	{
		t_vector		projection1;

		obj->cur_mat = obj->materials[obj->cones[obj->cur_cone].mat];
		obj->norm = vect_sub(&obj->ray.start, &obj->cones[obj->cur_cone].pos);
		projection1 = vect_scale(vect_dot(&obj->norm, &obj->cones[obj->cur_cone].rot), &obj->cones[obj->cur_cone].rot);
		obj->norm = vect_sub(&obj->norm, &projection1);
		if (!vect_norm(&obj->norm))
			return (0);
	}
	else if (obj->cur_plane != -1)
	{
		obj->cur_mat = obj->materials[obj->planes[obj->cur_plane].mat];
		obj->norm = obj->planes[obj->cur_plane].rot;
		if (vect_dot(&obj->ray.dir, &obj->planes[obj->cur_plane].rot) > 0.0f)
			obj->norm = vect_scale(-1.0f, &obj->norm);
		if (!vect_norm(&obj->norm))
			return (0);
	}
	else
	{
		/* No hit - add background */
		t_color test = col_create(0, 0, 0);
		test = col_mul_coef(&test, obj->coef);
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
	while ((obj->coef > 0.0f) && (level < RAY_DEPTH))
	{
		t = 20000.0f;
		obj->cur_sphere = -1;
		obj->cur_cylinder = -1;
		obj->cur_cone = -1;
		obj->cur_plane = -1;

		i = 0;
		// Search for ray intersection with obj in env
		while (i < obj->sc)
		{
			if (ray_intersect_sphere(&obj->ray, &obj->spheres[i], &t))
				obj->cur_sphere = i;
			i++;
		}
		i = 0;
		while (i < obj->cyc)
		{
			if (ray_intersect_cylinder(&obj->ray, &obj->cylinders[i], &t))
			{
				obj->cur_sphere = -1;
				obj->cur_cylinder = i;
			}
			i++;
		}
		i = 0;
		while (i < obj->cnc)
		{
			if (ray_intersect_cone(&obj->ray, &obj->cones[i], &t))
			{
				obj->cur_sphere = -1;
				obj->cur_cylinder = -1;
				obj->cur_cone = i;
			}
			i++;
		}
		i = 0;
		while (i < obj->pc)
		{
			if (ray_intersect_plane(&obj->ray, &obj->planes[i], &t))
			{
				obj->cur_sphere = -1;
				obj->cur_cylinder = -1;
				obj->cur_cone = -1;
				obj->cur_plane = i;
			}
			i++;
		}
		if (!hit_obj(obj, color, t))
			break;
		check_norm(obj, color);
		apply_reflection(obj);
		level++;
	}
}

void		trace_each_pixel(t_env *obj)
{
	t_color			color;
	int				x, y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			obj->coef = 1.0;

			color = col_create(0, 0, 0);
			obj->ray.start = vect_create(x, y, -1000.0f);
			obj->ray.dir = vect_create(0, 0, 1);
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
	obj->mc = 4;
	obj->materials = (t_mat*)malloc(sizeof(t_mat) * obj->mc);

	obj->materials[0].diffuse = col_create(1, 0, 0);
	obj->materials[0].specular = col_create(1, 1, 1);
	obj->materials[0].reflection = 0.2;
	obj->materials[0].power = 60;

	obj->materials[1].diffuse = col_create(0, 1, 0);
	obj->materials[1].specular = col_create(1, 1, 1);
	obj->materials[1].reflection = 0.5;
	obj->materials[1].power = 60;

	obj->materials[2].diffuse = col_create(0, 0, 1);
	obj->materials[2].specular = col_create(0.1, 0.1, 0.1);
	obj->materials[2].reflection = 0.9;
	obj->materials[2].power = 60;

	obj->materials[3].diffuse = col_create(0.5, 0.5, 0.5);
	obj->materials[3].specular = col_create(0.5, 0.5, 0.5);
	obj->materials[3].reflection = 0;
	obj->materials[3].power = 60;

	obj->sc = 2;
	obj->spheres = (t_sphere*)malloc(sizeof(t_sphere) * obj->sc);

	obj->spheres[0].pos = vect_create(200, 400, 10);
	obj->spheres[0].radius = 100;
	obj->spheres[0].mat = 0;

	obj->spheres[1].pos = vect_create(600, 245, 120);
	obj->spheres[1].radius = 100;
	obj->spheres[1].mat = 2;

	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, -1, 0);
	mat_identity(mat);
	mat_rotate(mat, 0, 0, -(45 * M_PI / 180));

	obj->cyc = 1;
	obj->cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * obj->cyc);

	obj->cylinders[0].pos = vect_create(200, 600, 300);
	vec_mult_mat(&tmp, mat, &obj->cylinders[0].rot);
	obj->cylinders[0].radius = 100;
	obj->cylinders[0].mat = 1;

	t_vector	tmp2;
	float		mat2[4][4];

	tmp = vect_create(0, -1, 0);
	mat_identity(mat2);
	mat_rotate(mat2, 0, 0, 0);

	obj->cnc = 1;
	obj->cones = (t_cone*)malloc(sizeof(t_cone) * obj->cnc);

	obj->cones[0].pos = vect_create(400, 400, 300);
	vec_mult_mat(&tmp2, mat2, &obj->cones[0].rot);
	obj->cones[0].radius = 50;
	obj->cones[0].mat = 2;

	t_vector	tmp1;
	float		mat1[4][4];

	tmp1 = vect_create(0, 0, -1);
	mat_identity(mat1);
	mat_rotate(mat1, (92 * M_PI / 180), 0, 0);

	obj->pc = 1;
	obj->planes = (t_plane*)malloc(sizeof(t_plane) * obj->pc);

	obj->planes[0].pos = vect_create(0, 550, 0);
	vec_mult_mat(&tmp1, mat1, &obj->planes[0].rot);
	obj->planes[0].mat = 3;

	obj->lc = 2;
	obj->lights = (t_light*)malloc(sizeof(t_light) * obj->lc);

	obj->lights[0].pos = vect_create(300, 300, -600);
	obj->lights[0].intensity = col_create(1, 1, 1);

	obj->lights[1].pos = vect_create(500, 100, -100);
	obj->lights[1].intensity = col_create(0.3, 0.5, 1);
}

void		create_win(t_env *obj)
{
	setup_struct(obj);
	obj->mlx.mlx = mlx_init();
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, W_WIDTH, W_HEIGHT, "Wolf3D");
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
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
