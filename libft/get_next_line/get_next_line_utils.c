/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:40:17 by jchuah            #+#    #+#             */
/*   Updated: 2025/06/08 18:11:04 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//the pointer to the string dst is changed to a new memory space sufficient
//for the additional characters of source
//the original pointer to the string is freed
//size is the number of characters to copy from src into dst
//returns -1 on memory error
static int	ft_strcat_malloc(char **dst, char *src, int size)
{
	int		dstlen;
	char	*temp;

	dstlen = 0;
	if (*dst)
	{
		while ((*dst)[dstlen])
			dstlen++;
	}
	temp = (char *)malloc((dstlen + size + 1) * sizeof(char));
	if (!temp)
		return (-1);
	temp[dstlen + size] = '\0';
	while (size--)
		temp[dstlen + size] = src[size];
	while (dstlen--)
		temp[dstlen] = (*dst)[dstlen];
	free(*dst);
	*dst = temp;
	return (1);
}

//removes characters that have already been used
//refills buffer if line hasnt been found
static int	reset_buffer(int line_found, char *buffer, int endline, int fd)
{
	int		i;

	if (line_found)
	{
		i = 0;
		while (endline + i < BUFFER_SIZE)
		{
			buffer[i] = buffer[endline + i];
			i++;
		}
	}
	else
		i = read(fd, buffer, BUFFER_SIZE);
	if (i < BUFFER_SIZE)
		buffer[i] = '\0';
	return (i);
}

//finds a line in buffer and adds it to string pointed to by line
//returns 1 if line found, 0 if not, -1 if error or if end of file with no line
int	add_to_line(char **line, char *buffer, int fd)
{
	int		endline;
	int		line_found;
	int		bytes_read;

	endline = 0;
	line_found = 0;
	while (endline < BUFFER_SIZE && buffer[endline] && buffer[endline] != '\n')
		endline++;
	if (endline != BUFFER_SIZE && buffer[endline] == '\n')
	{
		endline++;
		line_found++;
	}
	if (endline)
	{
		if (ft_strcat_malloc(line, buffer, endline) == -1)
			return (-1);
	}
	bytes_read = reset_buffer(line_found, buffer, endline, fd);
	if (!line_found && !bytes_read && *line)
		line_found = 1;
	if (!line_found && bytes_read <= 0)
		return (-1);
	return (line_found);
}
