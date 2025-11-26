/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:13:48 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/08 18:10:55 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//gets a line from a fd
//repeated calls to the same fd returns a string of the next line
//returns NULL on error of if no more lines are available
char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE];
	char		*line;
	int			line_found;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	line_found = 0;
	while (!line_found)
	{
		line_found = add_to_line(&line, buffer[fd], fd);
		if (line_found == -1)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
