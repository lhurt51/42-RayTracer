/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*switch_width(t_conv *obj, char *str, char *space, unsigned int len)
{
	if (obj->flags.minus)
	{
		str = ft_strjoin(str, space);
		while (++len < obj->width)
			str = ft_strjoin(str, space);
	}
	else
	{
		str = ft_strjoin(space, str);
		while (++len < obj->width)
			str = ft_strjoin(space, str);
	}
	return (str);
}

char	*modify_width(t_conv *obj, char *str)
{
	unsigned int	len;
	char			*space;

	len = ft_strlen(str) - obj->flags.plus;
	if (!len)
		len = 1;
	if (obj->flags.zero && !obj->b_prec)
		space = ft_strdup("0");
	else
		space = ft_strdup(" ");
	if (len < obj->width)
		str = switch_width(obj, str, space, len);
	ft_strdel(&space);
	return (str);
}

char	*modify_prec(t_conv *obj, char *str)
{
	unsigned int	len;
	char			*ext;

	len = ft_strlen(str);
	ext = ft_strdup("0");
	if (len < obj->prec)
	{
		str = ft_strjoin(ext, str);
		while (++len < obj->prec)
			str = ft_strjoin(ext, str);
	}
	ft_strdel(&ext);
	return (str);
}
