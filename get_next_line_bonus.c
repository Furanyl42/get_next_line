/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-wil <nide-wil@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 10:15:55 by nide-wil          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:10 by nide-wil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list_gnl	*ft_get_node(t_list_gnl **head, int fd)
{
	t_list_gnl	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	curr = malloc(sizeof(t_list_gnl));
	if (!curr)
		return (NULL);
	curr->fd = fd;
	curr->remainder = NULL;
	curr->next = *head;
	*head = curr;
	return (curr);
}

static void	ft_remove_node(t_list_gnl **head, int fd)
{
	t_list_gnl	*curr;
	t_list_gnl	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->remainder);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static char	*ft_read_and_join(int fd, char *remainder)
{
	char	*buf;
	int		bytes_read;
	char	*tmp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(remainder, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(remainder);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(remainder, buf);
		free(remainder);
		remainder = tmp;
	}
	free(buf);
	return (remainder);
}

static char	*ft_extract_and_update(char **remainder)
{
	int		i;
	char	*line;
	char	*new_rem;

	i = 0;
	if (!*remainder || !(*remainder)[i])
	{
		free(*remainder);
		*remainder = NULL;
		return (NULL);
	}
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	line = ft_substr(*remainder, 0, i + ((*remainder)[i] == '\n'));
	if (!(*remainder)[i])
	{
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	new_rem = ft_strdup(&(*remainder)[i + 1]);
	free(*remainder);
	*remainder = new_rem;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list_gnl	*head;
	t_list_gnl			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_get_node(&head, fd);
	if (!node)
		return (NULL);
	node->remainder = ft_read_and_join(fd, node->remainder);
	if (!node->remainder)
	{
		ft_remove_node(&head, fd);
		return (NULL);
	}
	line = ft_extract_and_update(&node->remainder);
	if (!node->remainder)
		ft_remove_node(&head, fd);
	return (line);
}
