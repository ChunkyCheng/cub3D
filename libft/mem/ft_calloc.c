/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:13:09 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:35:47 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	product;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	product = nmemb * size;
	if (product / nmemb != size)
		return (NULL);
	ptr = malloc(product);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, product);
	return (ptr);
}
