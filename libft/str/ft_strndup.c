/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:30:32 by jchuah            #+#    #+#             */
/*   Updated: 2025/09/24 12:59:23 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	str_len;
	char	*dupe;

	if (!str || n == 0)
		return (NULL);
	str_len = ft_strlen(str);
	if (str_len <= n)
		return (ft_strdup(str));
	dupe = (char *)malloc((n + 1) * sizeof(char));
	if (!dupe)
		return (NULL);
	dupe[n] = '\0';
	while (n--)
		dupe[n] = str[n];
	return (dupe);
}
