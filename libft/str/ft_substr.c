/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:34:26 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/07 00:00:30 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*substr;
	unsigned int	substr_len;

	if (!str)
		return (NULL);
	s_len = ft_strlen(str);
	if (start > s_len)
		substr_len = 0;
	else if (s_len - start < len)
		substr_len = s_len - start;
	else
		substr_len = len;
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[substr_len] = '\0';
	while (substr_len--)
		substr[substr_len] = str[start + substr_len];
	return (substr);
}
