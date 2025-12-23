/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:35:47 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/23 16:35:30 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <stdio.h>

//warning: high number of decimals will lead to rounding errors
double	ft_decimal_round(double nbr, int decimals)
{
	int	place_value;

	place_value = 1;
	while (decimals--)
		place_value *= 10;
	return (round(nbr * place_value) / place_value);
}
