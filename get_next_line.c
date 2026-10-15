/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-wil <nide-wil@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:55:36 by nide-wil          #+#    #+#             */
/*   Updated: 2026/10/15 19:02:47 by nide-wil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

char *get_next_line(int fd)
{
	char buf[BUFFER_SIZE + 1];
	int bytes_read;
	char *new_remainder;
	int	i;
	char *line;
	char *tmp;
	static char *remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	
	do
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(remainder, buf);
		free(remainder);
		remainder = tmp;
	} while (bytes_read > 0 && !ft_strchr(remainder, '\n'));

	if (ft_strchr(remainder, (int)'\n'))
	{
		i = 0;
		while (remainder[i] && remainder[i] != '\n')
			i++;
		line = ft_substr(remainder, 0, i + 1);
		new_remainder = ft_strdup(&remainder[i + 1]);
		free(remainder);
		remainder = new_remainder;
	}
	else if (remainder)
	{
		if (*remainder)
			line = ft_strdup(remainder);
		else
			line = NULL;
		free(remainder);
		remainder = NULL;
	}
	else 
		line = NULL;
	return (line);
}
