/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/02/02 10:03:28 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_read_file(char *file_input)
{
	int	fd;

	fd = open(file_input, O_RDONLY, 0666);
	if (fd < 0)
	{
		perror("Archivo de entrada no existe o falló al abrirse\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	if (ft_strncmp(file_input, "here_doc.txt", ft_strlen("here_doc.txt")) == 0)
		unlink(file_input);
	else
		close(fd);
}

void	here_doc(char *lim)
{
	char	*line;
	int		here_doc;
	int		len;

	here_doc = open("here_doc.txt", O_CREAT | O_RDWR
			| O_APPEND | O_TRUNC, 0666);
	if (here_doc < 0)
	{
		perror("Archivo here_doc no pudo crearse y abrirse\n");
		exit(EXIT_FAILURE);
	}
	write(1, "pipe heredoc> ", 14);
	line = get_next_line(0);
	len = compare_here_doc(line, lim);
	while (ft_strncmp(line, lim, len) != 0)
	{
		write(here_doc, line, ft_strlen(line));
		free(line);
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		len = compare_here_doc(line, lim);
	}
	free(line);
	close(here_doc);
	open_read_file("here_doc.txt");
}

void	child(char **arg, char **address_args)
{
	int		pid;
	char	*command_path;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		command_path = correct_path(address_args, arg[0]);
		if (execve(command_path, arg, NULL) < 0)
		{
			free(command_path);
			perror("Hubo un problema al intentar ejecutar el comando\n");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	free_matrix(arg);
}

void	last_child(char **arg, char **address_args, char *output)
{
	char	*command_path;
	int		fd;
	int		pid;

	fd = open(output, O_CREAT | O_WRONLY | O_TRUNC | O_NOFOLLOW, 0666);
	if (fd < 0)
	{
		perror("Hubo un problema al abrir o crear el output\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		command_path = correct_path(address_args, arg[0]);
		if (execve(command_path, arg, NULL) < 0)
		{
			free(command_path);
			perror("Hubo un problema al intentar ejecutar el comando\n");
			exit(EXIT_FAILURE);
		}	
	}
	waitpid(pid, NULL, 0);
	free_matrix(arg);
}
