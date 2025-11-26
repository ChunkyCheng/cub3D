/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:39:52 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/02 16:30:08 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ptrarr.h"

size_t	ft_strarr_len(char *const *strarr)
{
	return (ft_ptrarr_len((void *const *)strarr));
}
