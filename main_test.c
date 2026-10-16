/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-wil <nide-wil@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:39:23 by nide-wil          #+#    #+#             */
/*   Updated: 2026/10/16 12:13:05 by nide-wil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char *get_next_line(int fd);

int	main(int ac, char **av)
{
	(void)av;
	(void)ac;
	int fd;
	char *line;
	int i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur lors de l'ouverture du fichier.\n");
		return (1);
	}
	printf("=== DEBUT DES TESTS GNL ===\n");
	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d : %s", i, line);
		free(line);
		i++;
	}

	line = get_next_line(fd);
	if (line == NULL)
		printf("\n[OK] GNL retourne bien NULL en fin de fichier.\n");
	else
	{
		printf("\n[ERREUR] GNL aurait du retourner NULL, mais a retourne : %s\n", line);
		free(line);
	}

	while ((line = get_next_line(fd)) != NULL)
		free(line);

	close(fd);

	printf("\n=== TEST DESCRIPTEUR INVALIDE (-1) ===\n");
	line = get_next_line(-1);
	if (line == NULL)
		printf("[OK] GNL a bien gere le fd -1 en retournant NULL.\n");
	else
	{
		printf("[ERREUR] GNL n'aurait pas du retourner de valeur pour fd -1.\n");
		free(line);
	}

	return (0);
}
