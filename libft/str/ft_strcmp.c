/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:55:48 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:23:49 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	diff;

	while (*str1 || *str2)
	{
		diff = *(unsigned char *)str1++ - *(unsigned char *)str2++;
		if (diff)
			return (diff);
	}
	return (0);
}
