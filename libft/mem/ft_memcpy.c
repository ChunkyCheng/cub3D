/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:18:50 by jchuah            #+#    #+#             */
/*   Updated: 2025/07/15 11:13:27 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static inline void	bytecpy(unsigned char *dst, unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

static inline void	batchcpy(size_t *dst, size_t *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const uintptr_t	batch = sizeof(size_t);
	const uintptr_t	batchmask = batch - 1;
	size_t			offset;

	if (((uintptr_t)dst & batchmask) == ((uintptr_t)src & batchmask))
	{
		offset = batch - ((uintptr_t)dst & batchmask);
		if (offset && offset < batch)
		{
			bytecpy(dst, (unsigned char *)src, offset);
			dst = ((unsigned char *)dst) + offset;
			src = ((unsigned char *)src) + offset;
			n -= offset;
		}
		batchcpy(dst, (size_t *)src, n / 8);
		dst = ((size_t *)dst) + n / 8;
		src = ((size_t *)src) + n / 8;
		n &= batchmask;
	}
	bytecpy(dst, (unsigned char *)src, n);
	return (dst);
}
