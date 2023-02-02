/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/02/02 10:03:53 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	while (cont < n && (s1[cont] || s2[cont]))
	{
		if (s1[cont] != s2[cont])
			return ((unsigned char)s1[cont] - (unsigned char)s2[cont]);
		cont++;
	}
	return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned long int		c1;
	unsigned long int		c2;

	if (to_find[0] == '\0')
		return ((char *)str);
	if (len == 0 && !str)
		return (0);
	c1 = 0;
	while (c1 < len && str[c1] != '\0')
	{
		c2 = 0;
		if ((str[c1 + c2]) && str[c1 + c2] == to_find[c2])
		{
			while ((str[c1 + c2])
				&& (str[c1 + c2] == to_find[c2]) && (c1 + c2) < len)
			{
				c2++;
				if (to_find[c2] == '\0')
					return ((char *)&str[c2]);
			}
		}
	c1++;
	}
	return (0);
}

void	free_matrix(char **matrix)
{
	int	cont;

	cont = 0;
	if (matrix)
	{
		while (matrix[cont])
		{
			free(matrix[cont]);
			cont++;
		}
		free(matrix);
	}
	matrix = NULL;
}

int	compare_here_doc(char *here_doc, char *lim)
{
	int		len;
	char	*here_doc_mod;
	int		cont;

	here_doc_mod = malloc(sizeof(char) * ft_strlen(here_doc));
	cont = 0;
	while (here_doc[cont] != '\n')
	{
		here_doc_mod[cont] = here_doc[cont];
		cont++;
	}
	here_doc_mod[cont] = '\0';
	if (ft_strlen(here_doc_mod) > ft_strlen(lim))
		len = ft_strlen(here_doc_mod);
	else
		len = ft_strlen(lim);
	free(here_doc_mod);
	return (len);
}

char	*free_join(char *buf, char *stash)
{
	char	*aux_stash;

	if (!buf | !stash)
		return (NULL);
	aux_stash = ft_strjoin(buf, stash);
	free(stash);
	return (aux_stash);
}
