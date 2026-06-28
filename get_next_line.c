/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianda <adrianda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:24:33 by adrianda          #+#    #+#             */
/*   Updated: 2026/06/28 15:10:30 by adrianda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_buff(int fd, char *remainder)
{
	ssize_t		bytes;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	while (ft_strchr(remainder, '\n') == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(remainder);
			free(buf);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
	free(buf);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*tmp;
	int			i;

	i = 0;
	remainder = ft_read_buff(fd, remainder);
	if (remainder == NULL || !*remainder)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	while (remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	tmp = remainder;
	line = ft_substr(remainder, 0, i + 1);
	remainder = ft_substr(remainder, i + 1, ft_strlen(remainder) - (i + 1));
	free(tmp);
	return (line);
}
