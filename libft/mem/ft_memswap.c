/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:34:21 by jchuah            #+#    #+#             */
/*   Updated: 2025/07/15 10:37:49 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
//swaps size number of bytes from memory pointed to by a and b
void	ft_memswap(void	*a, void *b, size_t size)
{
	const size_t	swap_size = 32;
	unsigned char	temp[32];
	unsigned char	tempchar;

	if (a == b)
		return ;
	while (size > swap_size)
	{
		ft_memcpy(temp, a, swap_size);
		ft_memcpy(a, b, swap_size);
		ft_memcpy(b, temp, swap_size);
		a = (unsigned char *)a + swap_size;
		b = (unsigned char *)b + swap_size;
		size -= swap_size;
	}
	while (size--)
	{
		tempchar = ((unsigned char *)a)[size];
		((unsigned char *)a)[size] = ((unsigned char *)b)[size];
		((unsigned char *)b)[size] = tempchar;
	}
}
