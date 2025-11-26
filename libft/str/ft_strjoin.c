/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:28:33 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:25:38 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*newstr;
	int		len;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (ft_strdup(str2));
	if (!str2)
		return (ft_strdup(str1));
	len = ft_strlen(str1);
	len += ft_strlen(str2);
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (*str1)
		newstr[i++] = *str1++;
	while (*str2)
		newstr[i++] = *str2++;
	newstr[i] = '\0';
	return (newstr);
}
