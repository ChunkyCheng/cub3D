/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:28:33 by jchuah            #+#    #+#             */
/*   Updated: 2025/09/25 10:55:16 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Same as ft_strjoin but joins at most n bytes from str2 to str1
char	*ft_strnjoin(const char *str1, const char *str2, size_t n)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (ft_strndup(str2, n));
	if (!str2 || n == 0)
		return (ft_strdup(str1));
	len = ft_strlen(str2);
	if (len > n)
		len = n;
	len += ft_strlen(str1);
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (*str1)
		newstr[i++] = *str1++;
	while (i < len)
		newstr[i++] = *str2++;
	newstr[i] = '\0';
	return (newstr);
}
