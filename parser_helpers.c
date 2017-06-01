/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

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
