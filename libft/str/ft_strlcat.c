/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:40:16 by jchuah            #+#    #+#             */
/*   Updated: 2025/05/19 16:37:07 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	i;

	length = 0;
	while (*dst && length < size)
	{
		dst++;
		length++;
	}
	i = 0;
	while (src[i] && i < size - length - 1)
	{
		if (length != size)
			dst[i] = src[i];
		i++;
	}
	if (length != size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (length + i);
}
