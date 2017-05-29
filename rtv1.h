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
# define RAY_DEPTH 15
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define SQ(x) (x * x)
# define INVSQRTF(x) (1.0f / sqrtf(x))
# define RANGE(x, a, b, mn, mx) (((b)-(a)) * ((x)-(mn)) / ((mx)-(mn))) + (a)

enum			e_obj
{
				NONE,
				SETTINGS,
				MATERIALS,
				LIGHTS,
				SPHERES,
				CYLINDERS,
				CONES,
				PLANES
};

typedef struct	s_read
{
	char			*av;
	char			*tmp;
	int				fd;
	int				ret;
}				t_read;

typedef struct	s_pressed
{
	int			shift:1;
	int			a:1;
	int			d:1;
	int			w:1;
	int			s:1;
}				t_pressed;

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

typedef struct	s_cylinder
{
	t_vector	pos;
	t_vector	rot;
	double		radius;
	int			mat;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	pos;
	t_vector	rot;
	double		radius;
	int			mat;
}				t_cone;

typedef struct	s_plane
{
	t_vector	pos;
	t_vector	rot;
	int			mat;
}				t_plane;

typedef struct	s_mlx
{
	t_pressed	keys;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bits;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct	s_cur
{
	t_mat		cur_mat;
	t_light		cur_light;
	int			cur_sphere;
	int			cur_cylinder;
	int			cur_cone;
	int			cur_plane;
}				t_cur;

typedef struct	s_objc
{
	unsigned	mc;
	unsigned	lc;
	unsigned	sc;
	unsigned	cyc;
	unsigned	cnc;
	unsigned	pc;
}				t_objc;

typedef struct	s_objs
{
	t_mat		*materials;
	t_light		*lights;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_cone		*cones;
	t_plane		*planes;
}				t_objs;

// Need to add a camera input system using Matrix multiplication
typedef struct	s_scene
{
	char*		name;
	t_vector	cam_pos;
	t_vector	cam_rot;
	t_objs		objs;
	t_objc		obj_count;
	unsigned	w_width;
	unsigned	w_height;
	unsigned	ray_depth;
	unsigned	fov;
}				t_scene;

typedef struct	s_draw
{
	t_ray		ray;
	t_cur		cur_objs;
	t_vector	norm;
	float		g_mat[4][4];
	double		coef;
	int			flip:1;
}				t_draw;

// Need to reorganize my structures delete whats not neccissary such as the ray and coef and norm
typedef struct	s_env
{
	t_mlx		mlx;
	t_scene		scene;
	t_draw		draw_data;
	unsigned	w_num;
}				t_env;

void	mat_identity(float mat[4][4]);
void	mat_copy(float source[4][4], float dest[4][4]);
void	mat_mult(float mata[4][4], float matb[4][4], float dest[4][4]);
void	mat_translate(float matrix[4][4], float tx, float ty, float tz);
void	mat_scale(float matrix[4][4], float sx, float sy, float sz);
void	mat_rotate(float matrix[4][4], float ax, float ay, float az);
void	vec_mult_mat(t_vector *source, float mat[4][4], t_vector *dest);

#endif
