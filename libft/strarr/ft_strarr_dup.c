/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:38:37 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/02 15:57:52 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ptrarr.h"

char	**ft_strarr_dup(char *const *strarr)
{
	return ((char **)ft_ptrarr_dup((void *const *)strarr));
}
