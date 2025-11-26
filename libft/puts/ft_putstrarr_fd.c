/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:24:23 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/16 14:27:55 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrarr_fd(char *const *strarr, int fd)
{
	int	len;

	len = 0;
	while (*strarr)
		len += ft_putstr_fd(*strarr++, fd);
	return (len);
}
