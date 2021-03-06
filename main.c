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

#include "includes/rtv1.h"

void		memdel_2d(char **str)
{
	unsigned	i;

	i = 0;
	while (str[i])
		ft_strdel(&str[i++]);
	ft_memdel((void**)&str);
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
