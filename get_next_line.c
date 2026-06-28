/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianda <adrianda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:24:33 by adrianda          #+#    #+#             */
/*   Updated: 2026/06/27 22:16:09 by adrianda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_buff(int fd, char *remainder)
{
	ssize_t		bytes;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(remainder, '\n') == NULL)
	{
		bytes = read(fd, buf, sizeof(buf) - 1);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
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
		return (NULL);
	while (remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	tmp = remainder;
	line = ft_substr(remainder, 0, i + 1);
	remainder = ft_substr(remainder, i + 1, ft_strlen(remainder) - (i + 1));
	free(tmp);
	return (line);
}
