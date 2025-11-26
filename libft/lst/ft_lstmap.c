/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:55:44 by jchuah            #+#    #+#             */
/*   Updated: 2025/05/21 08:33:53 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	ptr = newlist;
	ptr->content = f(lst->content);
	while (lst->next)
	{
		ptr->next = (t_list *)malloc(sizeof(t_list));
		if (!ptr->next)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ptr = ptr->next;
		lst = lst->next;
		ptr->content = f(lst->content);
	}
	ptr->next = NULL;
	return (newlist);
}
