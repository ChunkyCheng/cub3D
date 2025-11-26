/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:30:32 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/06 23:32:41 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*dupe;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dupe = (char *)malloc((len + 1) * sizeof(char));
	if (!dupe)
		return (NULL);
	dupe[len] = '\0';
	while (len--)
		dupe[len] = str[len];
	return (dupe);
}
