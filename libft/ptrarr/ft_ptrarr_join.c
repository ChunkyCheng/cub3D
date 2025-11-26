/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarr_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:28:33 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/23 18:06:08 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "ptrarr.h"

void	**ft_ptrarr_join(void *const *ptrarr1, void *const *ptrarr2)
{
	void	**newarr;
	size_t	len1;
	size_t	len2;

	if (!ptrarr1 && !ptrarr2)
		return (NULL);
	if (!ptrarr1)
		return (ft_ptrarr_dup(ptrarr2));
	if (!ptrarr2)
		return (ft_ptrarr_dup(ptrarr1));
	len1 = ft_ptrarr_len(ptrarr1);
	len2 = ft_ptrarr_len(ptrarr2);
	if (len1 > SIZE_MAX - len2)
		return (NULL);
	newarr = (void **)malloc((len1 + len2 + 1) * sizeof(void *));
	if (!newarr)
		return (NULL);
	ft_memcpy(newarr, ptrarr1, len1 * sizeof(void *));
	ft_memcpy(newarr + len1, ptrarr2, (len2 + 1) * sizeof(void *));
	return (newarr);
}
