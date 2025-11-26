/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:28:48 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/08 00:50:09 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		len;
	char	c;

	len = 1;
	if (n < 0)
		c = '0' - (n % 10);
	else
		c = '0' + (n % 10);
	if (n / 10)
		len += ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
	{
		write(fd, "-", 1);
		len++;
	}
	write(fd, &c, 1);
	return (len);
}
