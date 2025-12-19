/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:35:47 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/19 15:44:46 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

//warning: do not use too small of a place value that could lead to
//floating point rounding errors
double	ft_round_to(double nbr, double place_value)
{
	return (round(nbr / place_value) * place_value);
}
