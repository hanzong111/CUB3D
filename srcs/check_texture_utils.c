/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:12:08 by gualee            #+#    #+#             */
/*   Updated: 2023/08/09 17:37:32 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_textures(t_data *data)
{
	if (data->count.n_img == 1 && data->count.s_img == 1
		&&	data->count.e_img  == 1 && data->count.w_img == 1
		&& data->count.floor == 1 && data->count.sky == 1)
		return (1);
	return (0);
}

static void	ft_read_to_buff(char **buff, char **line, int fd)
{
	char	*new_line;
	char	*temp;

	temp = ft_strdup(*buff);
	free(*buff);
	*buff = NULL;

	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		temp = ft_strjoin(temp, new_line);
		if (ft_strchr(new_line, '\n'))
			break ;
	}

	*buff = temp;
	free(*line);
	*line = ft_strdup(*buff);
}

void	ft_get_texture_data(t_data *data, int fd)
{
	int		textures;
	char	*line;
	char	**split;

	textures = 0;
	line = get_next_line(fd);
	while (!textures && line)
	{
		split = ft_split(line, ' ');
		if (ft_check_line(data, split))
		{
			free(line);
			ft_free_split(split);
			ft_exit_all(data, "TEXTURE COLOUR ERROR 1\n", 1);
		}
		textures = ft_check_textures(data);
		free(line);
		ft_free_split(split);
		line = get_next_line(fd);
	}
	free(line);
	// if (!textures)
	// 	ft_exit_all(data, "TEXTURE COLOUR ERROR 2\n", 1);
}

void	ft_get_map_data(t_data *data, int fd)
{
	char	*line;
	char	*buff;
	char	*nullptr;

	nullptr = NULL;
	line = NULL;
	line = get_next_line(fd);
	printf("line is %s\n", line);
	while (line && !ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		free(line);
		ft_exit_all(data, "MAP ERROR : ???\n", 1);
	}
	buff = nullptr;
	ft_bzero(buff, 0);
	while (line)
		ft_read_to_buff(&buff, &line, fd);
	data->game.map = ft_split(buff, '\n');
	ft_check_valid_map(data);
	free(buff);
}

void	initialize_map(t_data *data, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_all(data, "MAP ERROR : Cant open passed map\n", 1);
	}
	if (ft_valid_cub_file(path))
	{
		close(fd);
		ft_exit_all(data, "MAP ERROR : File does not end in .CUB\n", 1);
	}
	ft_get_texture_data(data, fd);
	// ft_get_map_data(data, fd);
	ft_check_valid_map(data);
}