/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:09:33 by lhurt             #+#    #+#             */
/*   Updated: 2017/04/02 20:09:34 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*utoa_store(unsigned int tmp, int base, unsigned int *count)
{
	char			*new;
	unsigned int	len;

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

char	*ft_utoa_base(unsigned int n, int base)
{
	char			*base_d;
	char			*new;
	unsigned int	count;

	count = 0;
	base_d = ft_strdup("0123456789ABCDEF");
	new = utoa_store(n, base, &count);
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

char	*ujtoa_store(uintmax_t tmp, int base, unsigned int *count)
{
	char			*new;
	uintmax_t		len;

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

char	*ft_ujtoa_base(uintmax_t n, int base)
{
	char			*base_d;
	char			*new;
	unsigned int	count;

	count = 0;
	base_d = ft_strdup("0123456789ABCDEF");
	new = ujtoa_store(n, base, &count);
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
