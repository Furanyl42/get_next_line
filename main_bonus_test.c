/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-wil <nide-wil@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 11:06:53 by nide-wil          #+#    #+#             */
/*   Updated: 2026/10/16 12:09:09 by nide-wil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Erreur lors de l'ouverture des fichiers");
		return (1);
	}

	printf("=== DEBUT DES TESTS MULTI-FD ===\n\n");

	line = get_next_line(fd1);
	printf("FD 1 -> %s", line ? line : "(null)");
	free(line);

	line = get_next_line(fd2);
	printf("FD 2 -> %s", line ? line : "(null)");
	free(line);

	line = get_next_line(fd3);
	printf("FD 3 -> %s", line ? line : "(null)");
	free(line);

	line = get_next_line(fd1);
	printf("FD 1 (2eme ligne) -> %s", line ? line : "(null)");
	free(line);

	line = get_next_line(fd2);
	printf("FD 2 (2eme ligne) -> %s", line ? line : "(null)");
	free(line);

	line = get_next_line(fd3);
	printf("FD 3 (2eme ligne) -> %s", line ? line : "(null)");
	free(line);

	printf("\n=== FIN DES TESTS ===\n");

	while ((line = get_next_line(fd1)) != NULL)
		free(line);

	while ((line = get_next_line(fd2)) != NULL)
		free(line);

	while ((line = get_next_line(fd3)) != NULL)
		free(line);

	close(fd1);
	close(fd2);
	close(fd3);

	return (0);
}
