/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:06:58 by lhurt             #+#    #+#             */
/*   Updated: 2017/03/02 18:07:02 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_FUNC_H
# define STRUCT_FUNC_H

# include "struct.h"

char	*modify_prec(t_conv *obj, char *str);
char	*modify_width(t_conv *obj, char *str);
int		check_conv(va_list ap, t_conv *obj, char c);
int		check_flag(t_conv *obj, char c);
char	*print_flag(t_conv *obj);
int		any_len(t_conv *obj);
int		check_len(t_conv *obj, const char *str);
char	*print_len(t_conv *obj);
int		check_all(va_list ap, t_conv *obj, const char *str, int *i);
int		flag_d(t_conv *obj);
int		flag_u(t_conv *obj);
int		flag_o(t_conv *obj);
int		flag_x(t_conv *obj);
int		can_mix(t_conv *obj);
int		printf_d(va_list ap, t_conv *obj);
int		printf_ld(va_list ap, t_conv *obj);
int		printf_u(va_list ap, t_conv *obj);
int		printf_lu(va_list ap, t_conv *obj);
int		printf_o(va_list ap, t_conv *obj);
int		printf_lo(va_list ap, t_conv *obj);
int		printf_x(va_list ap, t_conv *obj);
int		printf_lx(va_list ap, t_conv *obj);
int		printf_s(va_list ap, t_conv *obj);
int		printf_ws(va_list ap, t_conv *obj);
int		printf_c(va_list ap, t_conv *obj);
int		printf_p(va_list ap, t_conv *obj);
int		printf_per(t_conv *obj);

#endif
