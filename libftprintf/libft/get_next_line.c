/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 17:38:30 by lhurt             #+#    #+#             */
/*   Updated: 2016/10/13 17:38:31 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*store(char **line, char *str, unsigned int count)
{
	char	*dst;

	if (count == 0)
		dst = ft_strdup(str);
	else
		dst = ft_strjoin(*line, str);
	return (dst);
}

static int		check_the_line(char **line, char *str, char **start,
	unsigned int *count)
{
	char	*tmp;

	if ((tmp = ft_strchr(str, '\n')))
	{
		*tmp = '\0';
		tmp++;
		*line = store(line, str, *count);
		*start = ft_strdup(tmp);
		return (1);
	}
	*line = store(line, str, *count);
	(*count)++;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*start[1024] = {0};
	char			buff[BUFF_SIZE + 1];
	unsigned int	count;
	int				ret;

	count = 0;
	if (fd < 0 || line == NULL || (-1 == read(fd, buff, 0)))
		return (-1);
	if (start[fd])
		if (check_the_line(line, start[fd], &start[fd], &count))
			return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (check_the_line(line, buff, &start[fd], &count))
			return (1);
	}
	if (ret == 0 && (!start[fd] || ft_strlen(start[fd]) > 0))
	{
		start[fd] = "\0";
		return (1);
	}
	*line = "\0";
	return (0);
}
