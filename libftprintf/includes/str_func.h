/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:06:58 by lhurt             #+#    #+#             */
/*   Updated: 2017/03/02 18:07:02 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_FUNC_H
# define STR_FUNC_H

void	*error(char *msg);
void	set_struct(t_conv *obj);
char	*str_low(char *str);
int		wchar_len(wchar_t num);
int		wstr_len(wchar_t *str);
char	*wchar_to_str(wchar_t num);
char	*wstr_to_str(wchar_t *str);
char	*ft_itoa_base(int n, int base);
char	*ft_utoa_base(unsigned int n, int base);
char	*ft_ltoa_base(long n, int base);
char	*ft_ultoa_base(unsigned long int n, int base);
char	*ft_lltoa_base(long long n, int base);
char	*ft_ulltoa_base(unsigned long long n, int base);
char	*ft_sctoa_base(signed char n, int base);
char	*ft_usctoa_base(unsigned char n, int base);
char	*ft_sitoa_base(short int n, int base);
char	*ft_usitoa_base(unsigned short int n, int base);
char	*ft_jtoa_base(intmax_t n, int base);
char	*ft_ujtoa_base(uintmax_t n, int base);
char	*ft_ztoa_base(size_t n, int base);

#endif
