/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:04:54 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/08 17:07:06 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (dst[i])
		i++;
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst);
}
