/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 19:41:20 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/26 19:41:22 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_strrev(char *str, size_t len)
{
	size_t	i;
	char	tmp;

	i = 0;
	if (str[i] == '-')
		i++;
	while (i < len)
	{
		tmp = str[len];
		str[len] = str[i];
		str[i] = tmp;
		i++;
		len--;
	}
	str[len + i + 1] = '\0';
}

static char	*itoa_build(int n, size_t *i, size_t *count)
{
	char	*new;
	long	num;
	long	num2;

	num = n;
	if (num < 0)
	{
		num *= -1;
		(*i)++;
	}
	num2 = n;
	while (num2 /= 10)
		(*count)++;
	(*count) += (*i);
	new = ft_strnew((*count) + 1);
	if (!new)
		return (NULL);
	return (new);
}

char		*ft_itoa(int n)
{
	char	*new;
	long	num;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	new = itoa_build(n, &i, &count);
	if (!new)
		return (NULL);
	num = n;
	if (i > 0)
	{
		num *= -1;
		new[0] = '-';
	}
	while (num > 9)
	{
		new[i++] = (num % 10) + 48;
		num /= 10;
	}
	new[i++] = (num % 10) + 48;
	itoa_strrev(new, count);
	return (new);
}
