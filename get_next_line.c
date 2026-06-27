/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianda <adrianda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 17:24:33 by adrianda          #+#    #+#             */
/*   Updated: 2026/06/27 19:52:12 by adrianda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*tmp;
	ssize_t		bytes;
	char		buf[BUFFER_SIZE + 1];
	int			i;

	i = 0;
	bytes = read(fd, buf, sizeof(buf) - 1);
	while (bytes > 0 && ft_strchr(remainder, '\n') == NULL)
	{
		buf[bytes] = '\0';
		remainder = ft_strjoin(remainder, buf);
		bytes = read(fd, buf, sizeof(buf) - 1);
		buf[bytes] = '\0';
	}
	while (remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	tmp = remainder;
	line = ft_substr(remainder, 0, i + 1);
	remainder = ft_substr(remainder, i + 1, ft_strlen(remainder) - (i + 1));
	free(tmp);
	return (line);
}
