/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:01:56 by jchuah            #+#    #+#             */
/*   Updated: 2025/07/17 12:22:00 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	*partition(void *base, size_t nmemb, size_t size,
		int (*compare)(const void *, const void*))
{
	unsigned char	*array;
	unsigned char	*pvtptr;
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	array = (unsigned char *)base;
	pvtptr = array + (nmemb - 1) * size;
	ft_memswap(array + (nmemb / 2) * size, pvtptr, size);
	ptr1 = array;
	ptr2 = array;
	i = 0;
	while (i < nmemb - 1)
	{
		if (compare(ptr1, pvtptr) < 0)
		{
			ft_memswap(ptr1, ptr2, size);
			ptr2 += size;
		}
		ptr1 += size;
		i++;
	}
	ft_memswap(ptr2, pvtptr, size);
	return (ptr2);
}

void	ft_qsort(void *base, size_t nmemb, size_t size,
		int (*compare)(const void *, const void *))
{
	unsigned char	*pvtptr;
	size_t			pvtindx;

	while (nmemb > 1)
	{
		pvtptr = partition(base, nmemb, size, compare);
		pvtindx = (pvtptr - (unsigned char *)base) / size;
		if (pvtindx < nmemb / 2)
		{
			ft_qsort(base, pvtindx, size, compare);
			if (nmemb <= pvtindx + 1)
				return ;
			base = pvtptr + size;
			nmemb -= pvtindx + 1;
		}
		else
		{
			if (nmemb > pvtindx + 1)
				ft_qsort(pvtptr + size, nmemb - (pvtindx + 1), size, compare);
			nmemb = pvtindx;
		}
	}
}
