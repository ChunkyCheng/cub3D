/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:26:12 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/23 19:13:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(const char *str, int fd)
{
	int	len;

	if (!str)
		return (write(fd, "(null)\n", 7));
	len = write(fd, str, ft_strlen(str));
	return (write(fd, "\n", 1) + len);
}
