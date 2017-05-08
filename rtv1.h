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
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define RANGE(x, a, b, mn, mx) (((b)-(a)) * ((x)-(mn)) / ((mx)-(mn))) + (a)

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;

typedef struct	s_mat
{
	t_color		diffse;
	float		reflextion;
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
	float		radius;
	int			mat;
}				t_sphere;

typedef struct		s_mlx
{
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
	// t_pressed		keys;
	t_sphere		*sphere;
	t_light			*lights;
	t_mlx			mlx;
	t_ray			ray;
	int				sc;
}					t_env;

#endif
