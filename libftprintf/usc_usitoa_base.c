/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usc_usitoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:09:33 by lhurt             #+#    #+#             */
/*   Updated: 2017/04/02 20:09:34 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*usctoa_store(unsigned char tmp, int base, unsigned int *count)
{
	char			*new;
	unsigned int	len;

	len = 0;
	while (tmp >= (unsigned int)base)
	{
		tmp /= base;
		len++;
	}
	len++;
	*count = len;
	new = (char*)malloc(sizeof(char) * (*count) + 1);
	return (new);
}

char	*ft_usctoa_base(unsigned char n, int base)
{
	char			*base_d;
	char			*new;
	unsigned int	count;

	count = 0;
	base_d = ft_strdup("0123456789ABCDEF");
	new = usctoa_store(n, base, &count);
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

char	*usitoa_store(unsigned short int tmp, int base, unsigned int *count)
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

char	*ft_usitoa_base(unsigned short int n, int base)
{
	char			*base_d;
	char			*new;
	unsigned int	count;

	count = 0;
	base_d = ft_strdup("0123456789ABCDEF");
	new = usitoa_store(n, base, &count);
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
