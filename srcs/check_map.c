/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:47:32 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 19:26:38 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_check_symbol(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			ft_exit_all(data, "MAP SYMBOL ERROR\n", 1);
	}
}

static int	ft_check_space(char **map, int i, int j)
{
	int	row_above;
	int	row_below;
	int	left_column;
	int	right_column;
	int	row_length;

	row_above = i - 1;
	row_below = i + 1;
	left_column = j - 1;
	right_column = j + 1;
	if (map[i][j] != ' ')
		return (0);
	row_length = (int)ft_strlen(map[i]);
	if (row_above >= 0 && j < row_length && map[row_above][j] == '0')
		ft_exit("SPACE ERROR\n", 1);
	if (row_below < (int)ft_strlen(map[i + 1]) && j < row_length
		&& map[row_below][j] == '0')
		ft_exit("SPACE ERROR\n", 1);
	if (left_column >= 0 && map[i][left_column] == '0')
		ft_exit("SPACE ERROR\n", 1);
	if (right_column < row_length && map[i][right_column] == '0')
		ft_exit("SPACE ERROR\n", 1);
	return (1);
}

void	ft_check_border(char **map, int i, int j)
{
	int	top_row_length;
	int	curr_row_length;
	int	bot_row_length;

	top_row_length = (int)ft_strlen(map[i - 1]);
	curr_row_length = (int)ft_strlen(map[i]);
	bot_row_length = (int)ft_strlen(map[i + 1]);
	if (ft_check_space(map, i, j))
		return ;
	if ((curr_row_length > top_row_length
			&& j >= top_row_length && map[i][j] != '1')
			|| (j < top_row_length && map[i - 1][j] == ' ' && map[i][j] != '1')
			|| (curr_row_length > bot_row_length && j >= bot_row_length
			&& map[i][j] != '1')
			|| (j < bot_row_length && map[i + 1][j] == ' ' && map[i][j] != '1'))
		ft_exit("MAP GOT LUBANG\n", 1);
}

int	ft_check_player(t_data *data, char **map, int i, int j)
{
	char	dir_ij;

	dir_ij = map[i][j];
	if (map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'E' || map[i][j] == 'W')
	{
		ft_check_player_helper(data, dir_ij);
		data->game.found_player++;
		data->player.pos.x = j * WALL_H + (WALL_H / 2);
		data->player.pos.y = i * WALL_H + (WALL_H / 2);
	}
	return (1);
}

void	ft_check_valid_map(t_data *data)
{
	int		i;
	int		j;
	int		len;
	char	**map;

	i = -1;
	len = ft_get_map_length(data->game.map);
	map = data->game.map;
	data->game.found_player = 0;
	while (++i < len)
	{
		j = -1;
		while (map[i][++j] && map[i][j] == ' ')
			;
		if ((i == 0 || i == len - 1) && !ft_check_all_one(data, i, j))
			continue ;
		if (map[i][j--] != '1')
			ft_exit_all(data, "MAP ERROR, LEFT\n", 1);
		if (map[i][ft_strlen(map[i]) - 1] != '1')
			ft_exit_all(data, "MAP ERROR, RIGHT\n", 1);
		while (map[i][++j])
			ft_check_everything(data, map, i, j);
	}
	if (data->game.found_player != 1)
		ft_exit_all(data, "PLAYER ERROR\n", 1);
}
