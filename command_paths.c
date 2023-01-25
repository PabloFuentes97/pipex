/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/01/20 11:18:55 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_matrix(char **envp)
{
	int		cont;
	char	**path;

	cont = 0;
	while (envp[cont] && ft_strnstr(envp[cont], "PATH=",
			ft_strlen(envp[cont])) == 0)
		cont++;
	if (envp[cont] == NULL)
	{
		perror("No encontró el PATH\n");
		exit(1);
	}
	path = ft_split(ft_strnstr(envp[cont], "PATH=",
				ft_strlen(envp[cont])), ':');
	return (path);
}

char	*correct_path(char **paths, char *command)
{
	int		cont;
	char	*command_path;

	cont = 0;
	if (access(command, X_OK) == 0)
		return (command);
	while (paths[cont])
	{
		command_path = ft_strjoin(ft_strjoin(paths[cont], "/"), command);
		if (!command_path)
			return (NULL);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		cont++;
	}
	perror("No existe el comando buscado\n");
	exit(EXIT_FAILURE);
}
