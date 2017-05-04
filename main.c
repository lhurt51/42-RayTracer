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

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*win;

	argc = 0;
	argv = NULL;
	ft_printf("Hello\n");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Wolf3D");
	// if (obj->mlx.img)
	// 	mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	// obj->mlx.img = mlx_new_image(obj->mlx.mlx, W_WIDTH, W_HEIGHT);
	// obj->mlx.data = mlx_get_data_addr(obj->mlx.img, &obj->mlx.bits,
	// 	&obj->mlx.size_line, &obj->mlx.endian);
	// mlx_hook(obj->mlx.win, 17, 0, exit_hook, obj);
	// mlx_hook(obj->mlx.win, 2, 0, loading_press, obj);
	// mlx_loop_hook(obj->mlx.mlx, start_loading, obj);
	mlx_loop(mlx);
	return (0);
}
