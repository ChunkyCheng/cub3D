/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:54:26 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/07 00:00:15 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	value;

	value = (unsigned char)c;
	while (*str)
	{
		if (*str == value)
			return ((char *)str);
		str++;
	}
	if (*str == value)
		return ((char *)str);
	return (NULL);
}
