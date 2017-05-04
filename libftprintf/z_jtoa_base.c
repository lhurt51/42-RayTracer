/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_jtoa_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:09:33 by lhurt             #+#    #+#             */
/*   Updated: 2017/04/02 20:09:34 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ztoa_store(size_t tmp, int base, unsigned int *count)
{
	char			*new;
	size_t			len;

	len = 0;
	while (tmp >= (unsigned)base)
	{
		tmp /= base;
		len++;
	}
	len++;
	*count = len;
	new = (char*)malloc(sizeof(char) * (*count) + 1);
	return (new);
}

char	*ft_ztoa_base(size_t n, int base)
{
	char			*base_d;
	char			*new;
	unsigned int	count;

	count = 0;
	base_d = ft_strdup("0123456789ABCDEF");
	new = ztoa_store(n, base, &count);
	if (!new)
		return (NULL);
	new[count] = '\0';
	while (n >= (unsigned int)base)
	{
		new[--count] = base_d[n % base];
		n /= base;
	}
	new[--count] = base_d[n % base];
	ft_strdel(&base_d);
	return (new);
}

char	*jtoa_store(intmax_t *num, int base, int *i, int *count)
{
	char			*new;
	intmax_t		tmp;
	int				len;

	len = 0;
	if (*num < 0)
	{
		if (base == 10)
			(*i)++;
		(*num) *= -1;
	}
	tmp = *num;
	while (tmp >= base)
	{
		tmp /= base;
		len++;
	}
	len++;
	*count = (len + (*i));
	new = (char*)malloc(sizeof(char) * (*count) + 1);
	return (new);
}

char	*ft_jtoa_base(intmax_t n, int base)
{
	char		*base_d;
	char		*new;
	intmax_t	num;
	int			i;
	int			count;

	i = 0;
	count = 0;
	num = n;
	base_d = ft_strdup("0123456789ABCDEF");
	new = jtoa_store(&num, base, &i, &count);
	if (!new)
		return (NULL);
	if (i > 0)
		new[0] = '-';
	new[count] = '\0';
	while (num >= base)
	{
		new[--count] = base_d[num % base];
		num /= base;
	}
	new[i] = base_d[num % base];
	ft_strdel(&base_d);
	return (new);
}
