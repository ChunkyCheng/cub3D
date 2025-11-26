/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:23:44 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/02 17:26:45 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ptrarr.h"

char	**ft_strarr_join(char *const *strarr1, char *const *strarr2)
{
	return ((char **)ft_ptrarr_join((void *const *)strarr1,
			(void *const *)strarr2));
}
