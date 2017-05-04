/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:29:17 by lhurt             #+#    #+#             */
/*   Updated: 2016/09/27 14:29:18 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*curr;
	t_list	*tail;
	t_list	*head;

	head = NULL;
	while (lst)
	{
		tail = malloc(sizeof(size_t));
		if (!tail)
			return (NULL);
		tail = f(lst);
		if (!head)
		{
			head = tail;
			curr = tail;
		}
		else
		{
			curr->next = tail;
			curr = curr->next;
		}
		lst = lst->next;
	}
	return (head);
}
