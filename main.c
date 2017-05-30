/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

t_vector	vect_diff(t_vector *v1, t_vector *v2)
{
	t_vector	rtn;

	rtn = vect_scale(vect_dot(v1, v2), v2);
	rtn = vect_sub(v1, &rtn);
	return (rtn);
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
	double		b;
	double		discr;
	double		ans;

	dist = vect_sub(&sphere->pos, &ray->start);
	b = vect_dot(&ray->dir, &dist);
	if ((discr = SQ(b) - vect_dot(&dist, &dist) + SQ(sphere->radius)) < 0.0f)
		return (0);
	ans = MIN((b - sqrtf(discr)), (b + sqrtf(discr)));
	if ((ans > 0.1f) && (ans < *t))
		*t = ans;
	return (*t == ans);
}

int			ray_intersect_cylinder(t_ray *ray, t_cylinder *c, double *t, int flip)
{
	t_vector	dist;
	t_vector	cr;
	double		b;
	double		tmp[4];

	cr = vect_diff(&ray->dir, &c->rot);
	dist = vect_sub(&ray->start, &c->pos);
	dist = vect_diff(&dist, &c->rot);
	b = 2 * vect_dot(&cr, &dist);
	tmp[0] = SQ(b) - 4 * vect_dot(&cr, &cr)
		* (vect_dot(&dist, &dist) - SQ(c->radius));
	tmp[3] = (-b + sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
	if (tmp[0] > 0.0f)
	{
		tmp[1] = (-b - sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
		tmp[2] = (-b + sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
		tmp[3] = ((MIN(tmp[2], tmp[1]) < 0) ^ flip ? MAX(tmp[2], tmp[1])
			: MIN(tmp[2], tmp[1]));
	}
	if ((tmp[0] >= 0) && (tmp[3] > 0.1f) && (tmp[3] < *t))
		*t = tmp[3];
	return (*t == tmp[3]);
}

int			ray_intersect_cone(t_ray *ray, t_cone *cn, double *t, int flip)
{
	t_vector	dist;
	double		a;
	double		b;
	double		tmp[4];

	dist = vect_sub(&ray->start, &cn->pos);
	a = vect_dot(&ray->dir,&ray->dir)-((1+SQ(cn->radius)))
		*vect_dot(&ray->dir,&cn->rot)*vect_dot(&ray->dir,&cn->rot);
	b = 2*(vect_dot(&ray->dir,&dist)-((1+SQ(cn->radius)))
		*vect_dot(&ray->dir,&cn->rot)*vect_dot(&dist,&cn->rot));
	tmp[3] = SQ(b)-4*a*(vect_dot(&dist,&dist)-((1+SQ(cn->radius)))
		*vect_dot(&dist,&cn->rot)*vect_dot(&dist,&cn->rot));
	if (tmp[3] == 0.0f)
		tmp[2] = (-b + sqrtf(tmp[3])) / (2 * a);
	else if (tmp[3] > 0.0f)
	{
		tmp[0] = (-b + sqrtf(tmp[3])) / (2 * a);
		tmp[1] = (-b - sqrtf(tmp[3])) / (2 * a);
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
	if ((answ = norm / discr) > 0.1f && (answ < *t))
		*t = answ;
	return (*t == answ);
}

t_color		apply_specular(t_env *obj, t_ray light_ray, double light_proj,
	double view_proj)
{
	t_vector blinn_dir;
	t_color	rtn;
	double tmp;
	double blinn;

	rtn = col_create(0, 0, 0);
	blinn_dir = vect_sub(&light_ray.dir, &obj->draw_data.ray.dir);
	if ((tmp = vect_dot(&blinn_dir, &blinn_dir)) != 0.0f)
	{
		blinn = INVSQRTF(tmp) * MAX(light_proj - view_proj, 0.0f);
		blinn = obj->draw_data.coef * powf(blinn,
			obj->draw_data.cur_objs.cur_mat.power);
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
	rtn = vect_scale(reflect, &obj->draw_data.norm);
	obj->draw_data.ray.dir = vect_sub(&obj->draw_data.ray.dir, &rtn);
}

void		correct_gamma(t_color *color)
{
	double invgamma;

	invgamma = 0.45f;
	color->blue = powf(color->blue, invgamma);
	color->red = powf(color->red, invgamma);
	color->green = powf(color->green, invgamma);
}

int			find_closest_sphere(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.sc)
	{
		if (ray_intersect_sphere(ray,
			&obj->scene.objs.spheres[i], t))
			rtn = i;
		i++;
	}
	return (rtn);
}

int			find_closest_cylinder(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.cyc)
	{
		if (ray_intersect_cylinder(ray,
			&obj->scene.objs.cylinders[i], t, obj->draw_data.flip))
			rtn = i;
		i++;
	}
	return (rtn);
}

int			find_closest_cone(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.cnc)
	{
		if (ray_intersect_cone(ray, &obj->scene.objs.cones[i],
			t, obj->draw_data.flip))
		 	rtn = i;
		i++;
	}
	return (rtn);
}

int			find_closest_plane(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.pc)
	{
		if (ray_intersect_plane(ray,
			&obj->scene.objs.planes[i], t))
	 		rtn = i;
		i++;
	}
	return (rtn);
}

int			check_shadows(t_env *obj, t_ray *ray, double *t)
{
	if (find_closest_sphere(obj, ray, t) != -1)
		return (1);
	else if (find_closest_cylinder(obj, ray, t) != -1)
		return (1);
	else if (find_closest_cone(obj, ray, t) != -1)
		return (1);
	else if (find_closest_plane(obj, ray, t) != -1)
		return (1);
	else
		return (0);
}

void		apply_light(t_env *obj, t_ray *light_ray, t_color *color,
	double light_proj)
{
	t_color		tmp_color;
	double		lambert;

	lambert = vect_dot(&light_ray->dir, &obj->draw_data.norm)
		* obj->draw_data.coef;
	color->red += lambert * obj->draw_data.cur_objs.cur_light.intensity.red
		* obj->draw_data.cur_objs.cur_mat.diffuse.red;
	color->green += lambert * obj->draw_data.cur_objs.cur_light.intensity.green
		* obj->draw_data.cur_objs.cur_mat.diffuse.green;
	color->blue += lambert * obj->draw_data.cur_objs.cur_light.intensity.blue
		* obj->draw_data.cur_objs.cur_mat.diffuse.blue;
	tmp_color = apply_specular(obj, *light_ray, light_proj,
		vect_dot(&obj->draw_data.ray.dir, &obj->draw_data.norm));
	*color = col_add(color, &tmp_color);
}

void		handle_light(t_env *obj, t_color *color)
{
	t_ray		light_ray;
	double		light_proj;
	double		t;
	unsigned	i;

	i = 0;
	light_ray.start = obj->draw_data.ray.start;
	while (i < obj->scene.obj_count.lc)
	{
		obj->draw_data.cur_objs.cur_light = obj->scene.objs.lights[i++];
		light_ray.dir = vect_sub(&obj->draw_data.cur_objs.cur_light.pos,
			&obj->draw_data.ray.start);
		if ((light_proj = vect_dot(&light_ray.dir,&obj->draw_data.norm)) > 0.0f)
			if ((t = vect_norm(&light_ray.dir)))
				if (!check_shadows(obj, &light_ray, &t) || !obj->scene.shadows)
					apply_light(obj, &light_ray, color, INVSQRTF(t)*light_proj);
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

int			set_cur_sphere(t_env *obj)
{
	t_sphere	cur;

	cur = obj->scene.objs.spheres[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_cur_cylinder(t_env *obj)
{
	t_cylinder	cur;
	t_vector	projection;

	cur = obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	projection = vect_scale(vect_dot(&obj->draw_data.norm, &cur.rot), &cur.rot);
	obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_cur_cone(t_env *obj)
{
	t_cone		cur;
	t_vector	projection;

	cur = obj->scene.objs.cones[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	projection = vect_scale(vect_dot(&obj->draw_data.norm, &cur.rot), &cur.rot);
	obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_cur_plane(t_env *obj)
{
	t_plane		cur;

	cur = obj->scene.objs.planes[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = cur.rot;
	if (vect_dot(&obj->draw_data.ray.dir, &cur.rot) > 0.0f)
	{
		obj->draw_data.norm = vect_scale(-1.0f, &obj->draw_data.norm);
		obj->draw_data.flip = 1;
	}
	else
		obj->draw_data.flip = 0;
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_background(t_env *obj, t_color *color)
{
	t_color		test;

	test = col_create(0, 0, 0);
	test = col_mul_coef(&test, obj->draw_data.coef);
	*color = col_add(color, &test);
	return (0);
}

void		set_ray_start(t_env *obj, double *t)
{
	t_vector	scaled;

	scaled = vect_scale(*t, &obj->draw_data.ray.dir);
	obj->draw_data.ray.start = vect_add(&obj->draw_data.ray.start, &scaled);
}

int			hit_obj(t_env *obj, t_color *color, double t)
{
	set_ray_start(obj, &t);
	if (obj->draw_data.cur_objs.cur_obj == SPHERES)
	{
		if (!set_cur_sphere(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == CYLINDERS)
	{
		if (!set_cur_cylinder(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == CONES)
	{
		if (!set_cur_cone(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == PLANES)
	{
		if (!set_cur_plane(obj))
			return (0);
	}
	else
		return (set_background(obj, color));
	return (1);
}

void		find_closest_obj(t_env *obj, double *t)
{
	int 	i;

	obj->draw_data.cur_objs.cur_index = -1;
	obj->draw_data.cur_objs.cur_obj = NONE;
	if ((i = find_closest_sphere(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = SPHERES;
	}
	if ((i = find_closest_cylinder(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = CYLINDERS;
	}
	if ((i = find_closest_cone(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = CONES;
	}
	if ((i = find_closest_plane(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = PLANES;
	}
}

void		ray_tracing(t_env *obj, t_color *color)
{
	int				level;
	double			t;

	level = 0;
	while ((obj->draw_data.coef > 0.0f) && (level < RAY_DEPTH))
	{
		t = 20000.0f;
		obj->draw_data.flip = 0;
		find_closest_obj(obj, &t);
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

int			set_draw_data(t_env *obj, unsigned x, unsigned y)
{
	t_vector		tmp;
	t_vector		ans;

	obj->draw_data.coef = 1.0;
	tmp = vect_create(x, y, obj->scene.fov * 10);
	obj->draw_data.ray.start = obj->scene.cam_pos;
	vec_mult_mat(&tmp, obj->draw_data.g_mat, &ans);
	obj->draw_data.ray.dir = vect_sub(&ans, &obj->draw_data.ray.start);
	if (!vect_norm(&obj->draw_data.ray.dir))
		return (0);
	return (1);
}

void		trace_each_pixel(t_env *obj)
{
	t_color			color;
	unsigned		x;
	unsigned		y;

	y = 0;
	while (y < obj->scene.w_height)
	{
		x = 0;
		while (x < obj->scene.w_width)
		{
			color = col_create(0, 0, 0);
			if (!set_draw_data(obj, x, y))
				return;
			ray_tracing(obj, &color);
			correct_gamma(&color);
			pixel_to_img(&obj->mlx, x++, y, color);
		}
		y++;
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

unsigned		check_enum(t_scene *s, char *str, unsigned *size)
{
	char	**tmp; // mem delete this

	tmp = ft_strsplit(str, ' ');
	if (ft_strequ("settings:", str_low(str)))
		return (set_settings(size));
	else if (ft_strequ("materials:", str_low(tmp[0])))
		return (set_materials(s, tmp[1], size));
	else if (ft_strequ("lights:", str_low(tmp[0])))
		return (set_lights(s, tmp[1], size));
	else if (ft_strequ("spheres:", str_low(tmp[0])))
		return (set_spheres(s, tmp[1], size));
	else if (ft_strequ("cylinders:", str_low(tmp[0])))
		return (set_cylinders(s, tmp[1], size));
	else if (ft_strequ("cones:", str_low(tmp[0])))
		return (set_cones(s, tmp[1], size));
	else if (ft_strequ("planes:", str_low(tmp[0])))
		return (set_planes(s, tmp[1], size));
	return ((int)error(ft_strjoin(s->name, ": wrong category name")));
}

double			find_decimal(char *str)
{
	unsigned	power;
	unsigned	pos;
	double		ans;

	pos = 1;
	power = ft_strlen(str);
	while (power-- > 0)
		pos *= 10;
	ans = (double)(atoi(str)) / pos;
	return (ans);
}

double			parse_double(char *str)
{
	char	**tmp; // mem delete this
	double	ans;

	tmp = ft_strsplit(str, '.');
	if (tmp[1] && !tmp[2])
	{
		ans = atoi(tmp[0]);
		if (ans >= 0.0f)
			ans += find_decimal(tmp[1]);
		else
			ans -= find_decimal(tmp[1]);
	}
	else if (tmp[0] && !tmp[1])
		ans = atoi(tmp[0]);
	else
		ans = 0.0f;
	return (ans);
}

t_vector		parse_tripple(char *str)
{
	char		**t_s; // mem delete this
	t_vector	tmp;

	t_s = ft_strsplit(ft_strtrim(ft_strtrim(str, '('), ')'), ',');
	if (t_s[2] && !t_s[3])
	{
		tmp = vect_create(parse_double(t_s[0]),
			parse_double(t_s[1]), parse_double(t_s[2]));
	}
	else
		tmp = vect_create(0, 0, 0);
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

t_vector		rot_cy_cn(char *rot)
{
	t_vector	rtn;
	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, -1, 0);
	rtn = parse_rot(rot);
	mat_identity(mat);
	mat_rotate(mat, rtn.x, rtn.y, rtn.z);
	vec_mult_mat(&tmp, mat, &rtn);
	return (rtn);
}

unsigned		store_cylinders(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.cylinders[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.cylinders[i].rot = rot_cy_cn(str[1]);
	else if (ft_strequ("radius:", str[0]))
		s->objs.cylinders[i].radius = parse_double(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.cylinders[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong cylinder properties")));
	return (1);
}

unsigned		store_cones(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.cones[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.cones[i].rot = rot_cy_cn(str[1]);
	else if (ft_strequ("radius:", str[0]))
		s->objs.cones[i].radius = parse_double(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.cones[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong cone properties")));
	return (1);
}

t_vector		rot_plane(char *rot)
{
	t_vector	rtn;
	t_vector	tmp;
	float		mat[4][4];

	tmp = vect_create(0, 0, -1);
	rtn = parse_rot(rot);
	mat_identity(mat);
	mat_rotate(mat, rtn.x, rtn.y, rtn.z);
	vec_mult_mat(&tmp, mat, &rtn);
	return (rtn);
}

unsigned		store_planes(t_scene *s, char **str, unsigned i)
{
	if (ft_strequ("pos:", str[0]))
		s->objs.planes[i].pos = parse_tripple(str[1]);
	else if (ft_strequ("rot:", str[0]))
		s->objs.planes[i].rot = rot_plane(str[1]);
	else if (ft_strequ("mat:", str[0]))
		s->objs.planes[i].mat = atoi(str[1]);
	else
		return ((int)error(ft_strjoin(s->name, ": wrong plane properties")));
	return (1);
}

unsigned		store_props(t_scene *s, char *str, unsigned type, unsigned i)
{
	char	**tmp; // mem delete this

	tmp = ft_strsplit(ft_strtrim(str, '\t'), ' ');
	if (type == SETTINGS)
		return (store_settings(s, tmp));
	else if (type == MATERIALS)
		return (store_materials(s, tmp, i));
	else if (type == LIGHTS)
		return (store_lights(s, tmp, i));
	else if (type == SPHERES)
		return (store_spheres(s, tmp, i));
	else if (type == CYLINDERS)
		return (store_cylinders(s, tmp, i));
	else if (type == CONES)
		return (store_cones(s, tmp, i));
	else if (type == PLANES)
		return (store_planes(s, tmp, i));
	else
		return ((int)error(ft_strjoin(s->name, ": wrong type")));
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

int			main(int argc, char **argv)
{
	t_env		*obj;
	void		*mlx;
	int			i;

	i = 0;
	mlx = mlx_init();
	while (i < argc - 1 && argc < 5)
	{
		obj = malloc(sizeof(t_env));
		if (!obj)
			return ((int)error("failed to malloc"));
		obj->mlx.mlx = mlx;
		obj->w_num = argc - 1;
		if (read_file(argv[i + 1], &obj->scene))
			create_win(obj);
		i++;
	}
	mlx_loop(mlx);
	return (0);
}
