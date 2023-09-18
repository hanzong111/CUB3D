/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:12:01 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 19:27:15 by gualee           ###   ########.fr       */
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

void	ft_check_everything(t_data *data, char **map, int i, int j)
{
	ft_check_symbol(data, map[i]);
	ft_check_player(data, map, i, j);
	ft_check_border(map, i, j);
}

void	ft_check_player_helper(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dir.x = 0.00;
		data->player.dir.y = 1;
	}
	else if (direction == 'S')
	{
		data->player.dir.x = 0.00;
		data->player.dir.y = -1;
	}
	else if (direction == 'E')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
	}
	else if (direction == 'W')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
	}
}
