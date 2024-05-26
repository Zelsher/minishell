/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:09:43 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 21:31:44 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	return_parse_error(t_command *command)
{
	command->invalid = 1;
	return ;
}

void	create_file_name(size_t nb, char *file_name, size_t temp, size_t count)
{
	int	i;

	file_name[(ft_nbrlen(nb) + 10)] = '\0';
	ft_strcpy(file_name, ".temp_file");
	i = 0;
	while (nb != 0)
	{
		temp = nb;
		count = 1;
		while (temp >= 10)
		{
			temp /= 10;
			count *= 10;
		}
		file_name[10 + i] = temp + '0';
		nb -= temp * count;
		while (count > nb * 10 && count != 1)
		{
			i++;
			count /= 10;
			file_name[10 + i] = '0';
		}
		i++;
	}
}

char	*generate_file(size_t *count)
{
	char	*file_name;

	file_name = NULL;
	while (!file_name)
	{
		file_name = malloc(sizeof(char) * ft_nbrlen(*count) + 11);
		if (!file_name)
			return (NULL);
		create_file_name(*count, file_name, 0, 0);
		if (!access(file_name, F_OK))
		{
			free(file_name);
			file_name = NULL;
			printf("acces\n");
		}
		*count += 1;
	}
	return (file_name);
}
