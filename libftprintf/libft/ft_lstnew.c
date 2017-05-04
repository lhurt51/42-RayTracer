/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 11:24:21 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/27 11:24:23 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new)
	{
		if (content == NULL)
		{
			new->content_size = 0;
			new->content = NULL;
		}
		else
		{
			new->content_size = content_size;
			if (!(new->content = ft_memalloc(new->content_size)))
				return (NULL);
			new->content = ft_memcpy(new->content, content, new->content_size);
		}
		new->next = NULL;
	}
	return (new);
}
