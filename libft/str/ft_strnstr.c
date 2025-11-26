/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:24:06 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:27:55 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!big)
		return (NULL);
	if (!little || !*little)
		return ((char *)big);
	while (len-- && *big)
	{
		if (*little == *big)
		{
			i = 1;
			while (i <= len && big[i] && little[i])
			{
				if (little[i] != big[i])
					break ;
				i++;
			}
			if (!little[i])
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
