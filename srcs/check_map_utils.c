/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:12:01 by gualee            #+#    #+#             */
/*   Updated: 2023/08/09 14:58:22 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_get_map_length(char **map)
{
	int	length;

	length = 0;
	while (map[length])
		length++;
	return (length);
}

int	ft_check_all_one(t_data *data, int i, int j)
{
	j = 0;
	while (data->game.map[i][j] != '\0')
	{
		if (data->game.map[i][j] != '1' && data->game.map[i][j] != ' ')
			ft_exit_all(data, "MAP BORDER ERROR\n", 1);
		j++;
	}

	return (0);
}

// void	ft_camera_fov(t_data *data, double dir_y, double plyr_y, double plyr_x)
// {
// 	data->game.found_player = 1;
// 	if (!data->game.found_player)
// 		ft_exit_all(data, "PLAYER ERROR\n", 1);
// 	data->player.dir.y = dir_y;
// 	data->player.cam_plane.x = plyr_x;
// 	data->player.cam_plane.y = plyr_y;
// 	data->game.found_player++;
// }

void	ft_check_everything(t_data *data, char **map, int i, int j)
{
	ft_check_symbol(data, map[i]);
	ft_check_player(data, map, i, j);
	ft_check_border(map, i, j);
}
