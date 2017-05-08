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

void	pixel_to_img(t_mlx *new, int x, int y, int color)
{
	int		i;

	i = (x * 4) + (y * new->size_line);
	if (i > 0 && color >= 0)
	{
		new->data[i++] = color & 0xFF;
		new->data[i++] = (color >> 8) & 0xFF;
		new->data[i] = (color >> 16) & 0xFF;
	}
}

int				exit_hook(t_env *obj)
{
	int	i;

	if (obj->mlx.win)
		mlx_destroy_window(obj->mlx.mlx, obj->mlx.win);
	if (obj->mlx.img)
		mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	i = 0;
	while (i < obj->sc)
		free(&obj->sphere[i++]);
	free(obj);
	exit(0);
}

t_vector	vect_sub(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

float		vect_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

int			ray_intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vector	dist;
	float		a;
	float		b;
	float		c;
	float		discr;

	dist = vect_sub(&ray->start, &sphere->pos);
	a = vect_dot(&ray->dir, &ray->dir);
	b = 2 * vect_dot(&ray->dir, &dist);
	c = vect_dot(&dist, &dist) - (sphere->radius * sphere->radius);
	discr = b * b - 4 * a * c;

	if (discr < 0)
		return (0);
	else
		return (1);
}

void		draw_sphere(t_env *obj)
{
	int			hit, x, y;

	obj->sphere = (t_sphere*)malloc(sizeof(t_sphere) * 1);

	obj->sphere[0].pos.x = 20;
	obj->sphere[0].pos.y = 20;
	obj->sphere[0].pos.z = 20;

	obj->sphere[0].radius = 10;

	obj->ray.start.z = 0;

	hit = 0;
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		obj->ray.start.y = y;
		while (x < W_WIDTH)
		{
			obj->ray.start.x = x;
			if (ray_intersect_sphere(&obj->ray, &obj->sphere[0]))
				pixel_to_img(&obj->mlx, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(obj->mlx.mlx, obj->mlx.win, obj->mlx.img, 0, 0);
	// obj = NULL;
	// for(y=0; y < 40; y++){
	// 	ray->start.y = y;
	// 	for(x=0; x<40; x++){
	// 		ray->start.x = x;
	//
	// 		hit = ray_intersect_sphere(ray, sphere);
	// 		if(hit)
	// 			ft_printf("++");
	// 		else
	// 			ft_printf("--");
	// 	}
	// 	/* First row of the screen done, move to next row */
	// 	ft_printf("\n");
	// }
}

int			main(int argc, char **argv)
{
	t_env		*obj;

	argc = 0;
	argv = NULL;
	obj = malloc(sizeof(t_env));
	obj->sc = 1;
	obj->ray.dir.x = 0;
	obj->ray.dir.y = 0;
	obj->ray.dir.z = 1;
	obj->mlx.mlx = mlx_init();
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, W_WIDTH, W_HEIGHT, "Wolf3D");
	// if (obj->img)
	// 	mlx_destroy_image(obj->mlx, obj->img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	obj->mlx.data = mlx_get_data_addr(obj->mlx.img, &obj->mlx.bits,
		&obj->mlx.size_line, &obj->mlx.endian);
	draw_sphere(obj);
	mlx_hook(obj->mlx.win, 17, 0, exit_hook, obj);
	// mlx_hook(obj->win, 2, 0, key_press, obj);
	// mlx_loop_hook(obj->mlx, start_loading, obj);
	mlx_loop(obj->mlx.mlx);
	return (0);
}
