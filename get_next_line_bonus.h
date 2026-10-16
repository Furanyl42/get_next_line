/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-wil <nide-wil@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 10:16:28 by nide-wil          #+#    #+#             */
/*   Updated: 2026/10/16 10:16:36 by nide-wil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list_gnl
{
	int					fd;
	char				*remainder;
	struct s_list_gnl	*next;
}						t_list_gnl;

char					*get_next_line(int fd);
size_t					ft_strlen(const char *s);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s1);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);

#endif
