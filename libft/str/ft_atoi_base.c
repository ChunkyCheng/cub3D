/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:01:58 by jchuah            #+#    #+#             */
/*   Updated: 2025/07/09 19:17:41 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *nptr, const char *radix)
{
	int		base;
	char	*radix_val_pos;
	int		num;
	int		sign;

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
	base = ft_strlen(radix);
	num = 0;
	radix_val_pos = ft_strchr(radix, *nptr);
	while (*nptr && radix_val_pos)
	{
		num = num * base + (int)(radix_val_pos - radix);
		nptr++;
		radix_val_pos = ft_strchr(radix, *nptr);
	}
	return (num * sign);
}
