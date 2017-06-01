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
# include "../minilibx/mlx.h"
# include "../libftprintf/printf.h"
# include "color.h"
# include "vector.h"
# include "obj.h"

# define SQ(x) (x * x)
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define RANGE(x, a, b, mn, mx) (((b)-(a)) * ((x)-(mn)) / ((mx)-(mn))) + (a)

typedef struct	s_pressed
{
	int			shift:1;
	int			a:1;
	int			d:1;
	int			w:1;
	int			s:1;
}				t_pressed;

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
	int			cur_obj;
	int			cur_index;
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

typedef struct	s_scene
{
	char		*name;
	t_vector	cam_pos;
	t_vector	cam_rot;
	t_objs		objs;
	t_objc		obj_count;
	unsigned	w_width;
	unsigned	w_height;
	unsigned	ray_depth;
	unsigned	fov;
	int			shadows:1;
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

typedef struct	s_env
{
	t_mlx		mlx;
	t_scene		scene;
	t_draw		draw_data;
	unsigned	w_num;
}				t_env;

void			memdel_2d(char **str);

int				exit_hook(t_env *obj);
int				my_key_press(int keycode, t_env *obj);

int				read_file(char *av, t_scene *scene);

void			pixel_to_img(t_mlx *obj, int x, int y, t_color color);
int				run_img(t_env *obj);
void			create_win(t_env *obj);

void			trace_each_pixel(t_env *obj);

#endif
