/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:14:33 by jchuah            #+#    #+#             */
/*   Updated: 2025/09/23 14:17:08 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_atoll_safe(const char *nptr, t_llong *dst)
{
	int	sign;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	*dst = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if ((sign == 1 && *dst > (LLONG_MAX - (*nptr - '0')) / 10)
			|| (sign == -1 && *dst < (LLONG_MIN + (*nptr - '0')) / 10))
			return (1);
		*dst *= 10;
		*dst += (*nptr - '0') * sign;
		nptr++;
	}
	return (0);
}
