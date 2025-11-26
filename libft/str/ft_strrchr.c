/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:44:29 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:33:48 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	value;
	char			*found;

	found = NULL;
	value = (unsigned char)c;
	while (*str)
	{
		if (*str == value)
			found = (char *)str;
		str++;
	}
	if (*str == value)
		found = (char *)str;
	return (found);
}
