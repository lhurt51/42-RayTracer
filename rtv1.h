/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "libftprintf/printf.h"

# define W_HEIGHT 600
# define W_WIDTH 800
# define RAY_DEPTH 10
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define INVSQRTF(x) (1.0f / sqrtf(x))
# define RANGE(x, a, b, mn, mx) (((b)-(a)) * ((x)-(mn)) / ((mx)-(mn))) + (a)

typedef struct		s_pressed
{
	int				shift;
	int				a;
	int				d;
	int				w;
	int				s;
}					t_pressed;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_color
{
	double		red;
	double		green;
	double		blue;
}				t_color;

typedef struct	s_mat
{
	t_color		diffuse;
	t_color		specular;
	double		reflection;
	double		power;
}				t_mat;

typedef struct	s_light
{
	t_vector	pos;
	t_color		intensity;
}				t_light;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_sphere
{
	t_vector	pos;
	double		radius;
	int			mat;
}				t_sphere;

typedef struct		s_mlx
{
	t_pressed		keys;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bits;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_env
{
	t_mlx			mlx;
	t_ray			ray;
	t_mat			*materials;
	t_mat			cur_mat;
	t_light			*lights;
	t_light			cur_light;
	t_sphere		*spheres;
	int				cur_sphere;
	t_vector		norm;
	double			coef;
	unsigned		mc;
	unsigned		lc;
	unsigned		sc;
}					t_env;

#endif
