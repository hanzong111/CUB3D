/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:12:08 by gualee            #+#    #+#             */
/*   Updated: 2023/09/17 22:47:38 by ojing-ha         ###   ########.fr       */
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
	load_map_to_array(data, fd);
	free(line);
}

void load_map_to_array(t_data *data, int fd)
{
    char *line;
    int i;
    char **map_arr;
    int j;

    map_arr = malloc(sizeof(char *) * (MAX_MAP_SIZE + 1));
    i = 0;
    while ((line = get_next_line(fd)) && i < MAX_MAP_SIZE)
    {
        int has_content = 0;
        for(j = 0; line[j] != '\0'; j++) {
            if(!isspace(line[j])) {
                has_content = 1;
                break;
            }
        }

        if(has_content) {
            int len = ft_strlen(line);
            if(line[len-1] == '\n') {
                line[len-1] = '\0';
            }
            
            map_arr[i] = line;
            i++;
        } else {
            free(line);
        }
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
	ft_check_valid_map(data);
	map_size(&data->col, data->game.map);
}