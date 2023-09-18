/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_quit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:11:35 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 20:56:35 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_split(char **split)
{
	char	*temp;
	char	**copy;	

	copy = split;
	while (*split)
	{
		temp = *split;
		split++;
		free(temp);
	}
	free(copy);
}

void	ft_exit(char *str, int status)
{
	if (str)
		ft_putstr_fd(str, 0);
	exit(status);
}

void	ft_exit_all(t_data *data, char *str, int status)
{
	(void)data;
	ft_exit(str, status);
}

int	ft_valid_cub_file(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (!path)
		ft_exit_all(NULL, ".CUB FILE ERROR\n", 1);
	if (len < 5)
		ft_exit_all(NULL, ".CUB FILE ERROR\n", 1);
	if (ft_strncmp(path + len - 4, ".cub", len) != 0)
		ft_exit_all(NULL, ".CUB FILE ERROR\n", 1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}
