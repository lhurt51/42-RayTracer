/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:06:58 by lhurt             #+#    #+#             */
/*   Updated: 2017/03/02 18:07:02 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_flags
{
	int				plus:1;
	int				minus:1;
	int				space:1;
	int				hash:1;
	int				zero:1;
}					t_flags;

typedef struct		s_len
{
	int				hh:1;
	int				h:1;
	int				l:1;
	int				ll:1;
	int				j:1;
	int				z:1;
}					t_len;

typedef struct		s_conv
{
	char			*rtn;
	char			conv;
	int				b_con:1;
	int				b_prec:1;
	t_flags			flags;
	t_len			len;
	unsigned int	width;
	unsigned int	prec;
	unsigned int	size;
}					t_conv;

#endif
