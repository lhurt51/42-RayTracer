/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rtv1.h"

/* Helpers */
unsigned	check_fd(char *av);
double		parse_double(char *str);
t_vector	parse_tripple(char *str);
t_color		parse_color(char *str);
t_vector	parse_rot(char *str);
/* Set up */
unsigned	set_settings(unsigned *size);
unsigned	set_materials(t_scene *s, char *str, unsigned *size);
unsigned	set_lights(t_scene *s, char *str, unsigned *size);
unsigned	set_spheres(t_scene *s, char *str, unsigned *size);
unsigned	set_cylinders(t_scene *s, char *str, unsigned *size);
unsigned	set_cones(t_scene *s, char *str, unsigned *size);
unsigned	set_planes(t_scene *s, char *str, unsigned *size);
/* Store */
unsigned	store_settings(t_scene *s, char **str);
unsigned	store_materials(t_scene *s, char **str, unsigned i);
unsigned	store_lights(t_scene *s, char **str, unsigned i);
unsigned	store_spheres(t_scene *s, char **str, unsigned i);
unsigned	store_cylinders(t_scene *s, char **str, unsigned i);
unsigned	store_cones(t_scene *s, char **str, unsigned i);
unsigned	store_planes(t_scene *s, char **str, unsigned i);

#endif
