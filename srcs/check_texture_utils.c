/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:12:08 by gualee            #+#    #+#             */
/*   Updated: 2023/09/16 21:41:16 by ojing-ha         ###   ########.fr       */
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

// static void	ft_read_to_buff(char **buff, char **line, int fd)
// {
// 	char	*new_line;
// 	char	*temp;

// 	temp = ft_strdup(*buff);
// 	free(*buff);
// 	*buff = NULL;

// 	while (1)
// 	{
// 		new_line = get_next_line(fd);
// 		if (!new_line)
// 			break ;
// 		temp = ft_strjoin(temp, new_line);
// 		if (ft_strchr(new_line, '\n'))
// 			break ;
// 	}

// 	*buff = temp;
// 	free(*line);
// 	*line = ft_strdup(*buff);
// }

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

void	load_map_to_array(t_data *data, char *file_path)
{
	int		fd;
	char	*line;
	int		i;
	char	**map_arr;

	if (!(file_path) || (ft_strlen(file_path) < 5) ||
		(ft_strncmp(file_path + ft_strlen(file_path) - 4, ".cub", 4)))
		ft_exit_all(data, "Invalid file extension. Use .cub file.\n", 1);

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		ft_exit_all(data, "Error opening file.\n", 1);

	map_arr = malloc(sizeof(char *) * (MAX_MAP_SIZE + 1));
	i = 0;
	while ((line = get_next_line(fd)) && i < MAX_MAP_SIZE)
	{
		map_arr[i] = line;
		i++;
	}
	map_arr[i] = NULL;
	data->game.map = map_arr;
	close(fd);
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
	load_map_to_array(data, path);

	printf("Map Generation Starts\n");
	int i = 0;
	while (data->game.map[i] != NULL)
	{
		printf("%s", data->game.map[i]);
		i++;
	}
	printf("Map Generation Ends\n");

	ft_check_valid_map(data);
	map_size(&data->col, data->game.map);
}