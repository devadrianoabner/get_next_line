/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianda <adrianda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 19:12:06 by adrianda          #+#    #+#             */
/*   Updated: 2026/06/25 20:44:05 by adrianda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*src;
	size_t			i;
	size_t			total;

	i = 0;
	total = nmemb * size;
	if (nmemb != 0 && (total) / nmemb != size)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	src = (unsigned char *) ptr;
	while (size > i)
	{
		src[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == 0)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	s3 = ft_calloc(1, ft_strlen(s1) +ft_strlen(s2) +1);
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	char	*src;
	size_t	buff;
	size_t	i;

	i = 0;
	if (ft_strlen(s) <= start)
		return ( ft_calloc(1, 1));
	if(ft_strlen(s) - start < len)
		buff = ft_strlen(s) - start + 1;
	else
		buff = len + 1;
	dest = ft_calloc(buff, 1);
	if (!dest)
		return (NULL);
	src = s + start;
	if (buff == 0)
		return (ft_calloc(1, 1));
	while (src[i] && i < buff - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
