/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/01/13 13:32:22 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_bonus(int argc, char **argv, char **address_args)
{
	int	cont;

	cont = 2;
	if (ft_strncmp(argv[1], "here_doc",
			ft_strlen(argv[1]) + 1) == 0 && argc >= 6)
	{
		here_doc(argv[2]);
		cont = 3;
	}
	else
		open_read_file(argv[1]);
	while (cont < argc - 2)
	{
		child(ft_split(argv[cont], ' '), address_args);
		cont++;
	}
	last_child(ft_split(argv[argc - 2], ' '), address_args, argv[argc - 1]);
	return (0);
}
