/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		wchar_len(wchar_t num)
{
	if (num <= 0x7F)
		return (1);
	else if (num <= 0x7FF)
		return (2);
	else if (num <= 0xFFFF)
		return (3);
	else if (num <= 0x10FFFF)
		return (4);
	else
		return (0);
}

char	*wchar_to_str(wchar_t num)
{
	char *str;

	if (!(str = ft_strnew(wchar_len(num) + 1)))
		return (NULL);
	if (num <= 0x7F)
		str[0] = num;
	else if (num <= 0x7FF)
	{
		str[0] = 192 | (((unsigned int)(num) >> 6) & 63);
		str[1] = 128 | ((unsigned int)(num) & 63);
	}
	else if (num <= 0xFFFF)
	{
		str[0] = 224 | (((unsigned int)(num) >> 12) & 63);
		str[1] = 128 | (((unsigned int)(num) >> 6) & 63);
		str[2] = 128 | ((unsigned int)(num) & 63);
	}
	else if (num <= 0x10FFFF)
	{
		str[0] = 240 | (((unsigned int)(num) >> 18) & 63);
		str[1] = 224 | (((unsigned int)(num) >> 12) & 63);
		str[2] = 128 | (((unsigned int)(num) >> 6) & 63);
		str[3] = 128 | ((unsigned int)(num) & 63);
	}
	return (str);
}

int		wstr_len(wchar_t *str)
{
	int len;

	len = 0;
	while (*str)
		len += wchar_len((*str)++);
	return (len);
}

char	*wstr_to_str(wchar_t *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*str)
	{
		if (i++ == 0)
			tmp = wchar_to_str(*str);
		else
			tmp = ft_strjoin(tmp, wchar_to_str(*str));
		str++;
	}
	return (tmp);
}
