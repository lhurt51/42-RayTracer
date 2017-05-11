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
	discr = b * b - vect_dot(&dist, &dist) + sphere->radius * sphere->radius;
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

void		apply_reflection(t_env *obj, t_vector new_start)
{
	t_vector	rtn;
	double		reflect;

	obj->coef *= obj->cur_mat.reflection;
	reflect = 2.0f * vect_dot(&obj->ray.dir, &obj->norm);
	obj->ray.start = new_start;
	rtn = vect_scale(reflect, &obj->norm);
	obj->ray.dir = vect_sub(&obj->ray.dir, &rtn);
}

void		correct_gamma(t_color *color)
{
	/* gamma correction */
	double invgamma; //Fixed value from sRGB standard

	invgamma = 0.45f;
	color->blue = powf(color->blue, invgamma);
	color->red = powf(color->red, invgamma);
	color->green = powf(color->green, invgamma);
}

void		handle_light(t_env *obj, t_color *color, t_vector new_start)
{
	t_ray		light_ray;
	t_color		tmp_color;
	double		lambert, dist, light_proj, t;
	int			shadow;
	unsigned	i, j;

	i = 0;
	light_ray.start = new_start;
	while (i < obj->lc)
	{
		obj->cur_light = obj->lights[i++];
		light_ray.dir = vect_sub(&obj->cur_light.pos, &new_start);
		if ((light_proj = vect_dot(&light_ray.dir, &obj->norm)) > 0.0f)
		{
			if ((dist = vect_dot(&light_ray.dir, &light_ray.dir)) != 0.0f)
			{
				light_ray.dir = vect_scale(INVSQRTF(dist), &light_ray.dir);
				light_proj = INVSQRTF(dist) * light_proj;
				t = dist;
				j = 0;
				while (j < obj->sc)
					if ((shadow = ray_intersect_sphere(&light_ray, &obj->spheres[j++], &t)))
						break;
				if (!shadow)
				{
					lambert = vect_dot(&light_ray.dir, &obj->norm) * obj->coef;
					color->red += lambert * obj->cur_light.intensity.red * obj->cur_mat.diffuse.red;
					color->green += lambert * obj->cur_light.intensity.green * obj->cur_mat.diffuse.green;
					color->blue += lambert * obj->cur_light.intensity.blue * obj->cur_mat.diffuse.blue;
				}
			}
			tmp_color = apply_specular(obj, light_ray, light_proj);
			*color = col_add(color, &tmp_color);
		}
	}
}

void		check_norm(t_env *obj, t_color *color, t_vector new_start)
{
	if (vect_dot(&obj->norm, &obj->ray.dir) > 0.0f)
		obj->norm = vect_scale(-1.0f, &obj->norm);
	else
		handle_light(obj, color, new_start);
}

int			hit_obj(t_env *obj, t_color *color, t_vector *new_start, double t)
{
	t_vector	scaled;
	double		tmp;

	if (obj->cur_sphere != -1)
	{
		scaled = vect_scale(t, &obj->ray.dir);
		*new_start = vect_add(&obj->ray.start, &scaled);
		obj->norm = vect_sub(new_start, &obj->spheres[obj->cur_sphere].pos);
		if ((tmp = vect_dot(&obj->norm, &obj->norm)) == 0.0f)
			return (0);
		tmp = INVSQRTF(tmp);
		obj->norm = vect_scale(tmp, &obj->norm);
		obj->cur_mat = obj->materials[obj->spheres[obj->cur_sphere].mat];
	}
	else
	{
		/* No hit - add background */
		t_color test = col_create(0.05,0.05,0.22);
		t_color tmp_c = col_mul_coef(&test, obj->coef);
		*color = col_add(color, &tmp_c);
		return (0);
	}
	return (1);
}

void		ray_tracing(t_env *obj, t_color *color)
{
	t_vector		new_start;
	int				level;
	unsigned		i;
	double			t;

	level = 0;
	while ((obj->coef > 0.0f) && (level < RAY_DEPTH))
	{
		t = 20000.0f;
		obj->cur_sphere = -1;

		i = 0;
		while (i < obj->sc)
		{
			if (ray_intersect_sphere(&obj->ray, &obj->spheres[i], &t))
				obj->cur_sphere = i;
			i++;
		}
		if (!hit_obj(obj, color, &new_start, t))
			break;
		check_norm(obj, color, new_start);
		apply_reflection(obj, new_start);
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
	obj->mc = 3;
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

	obj->sc = 3;
	obj->spheres = (t_sphere*)malloc(sizeof(t_sphere) * obj->sc);

	obj->spheres[0].pos = vect_create(200, 300, 0);
	obj->spheres[0].radius = 100;
	obj->spheres[0].mat = 0;

	obj->spheres[1].pos = vect_create(400, 400 ,0);
	obj->spheres[1].radius = 100;
	obj->spheres[1].mat = 1;

	obj->spheres[2].pos = vect_create(600, 245, 120);
	obj->spheres[2].radius = 100;
	obj->spheres[2].mat = 2;

	obj->lc = 2;
	obj->lights = (t_light*)malloc(sizeof(t_light) * obj->lc);

	obj->lights[0].pos = vect_create(0, 0, -300);
	obj->lights[0].intensity = col_create(1, 1, 1);

	obj->lights[1].pos = vect_create(600, 0, -100);
	obj->lights[1].intensity = col_create(0.3, 0.5, 1);
}

void		create_win(t_env *obj)
{
	obj->mlx.mlx = mlx_init();
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, W_WIDTH, W_HEIGHT, "Wolf3D");
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	setup_struct(obj);
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
