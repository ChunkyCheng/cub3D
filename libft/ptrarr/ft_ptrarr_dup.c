/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:22:35 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/23 18:05:35 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ptrarr.h"

void	**ft_ptrarr_dup(void *const *ptrarr)
{
	void	**newarr;
	size_t	len;

	if (!ptrarr)
		return (NULL);
	len = ft_ptrarr_len(ptrarr);
	newarr = (void **)malloc((len + 1) * sizeof(void *));
	if (!newarr)
		return (NULL);
	ft_memcpy(newarr, ptrarr, (len + 1) * sizeof(void *));
	return (newarr);
}
