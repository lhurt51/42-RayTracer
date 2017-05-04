/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_lltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:09:33 by lhurt             #+#    #+#             */
/*   Updated: 2017/04/02 20:09:34 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ltoa_store(long long int *num, int base, int *i, int *count)
{
	char			*new;
	long long int	tmp;
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

char	*ft_ltoa_base(long int n, int base)
{
	char			*base_d;
	char			*new;
	long long int	num;
	int				i;
	int				count;

	i = 0;
	count = 0;
	num = n;
	base_d = ft_strdup("0123456789ABCDEF");
	new = ltoa_store(&num, base, &i, &count);
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

char	*ft_lltoa_base(long long n, int base)
{
	char		*base_d;
	char		*new;
	long long	num;
	int			i;
	int			count;

	i = 0;
	count = 0;
	num = n;
	base_d = ft_strdup("0123456789ABCDEF");
	new = ltoa_store(&num, base, &i, &count);
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
