/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:04:55 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 20:52:46 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_process_texture_helper(t_data *data, char *direction, char *line)
{
	if (!ft_strcmp(direction, "NO"))
	{
		get_sprites(data, &data->sprites.n_img, line);
		data->count.n_img = 1;
	}
	else if (!ft_strcmp(direction, "SO"))
	{
		get_sprites(data, &data->sprites.s_img, line);
		data->count.s_img = 1;
	}
	else if (!ft_strcmp(direction, "EA"))
	{
		get_sprites(data, &data->sprites.e_img, line);
		data->count.e_img = 1;
	}
	else if (!ft_strcmp(direction, "WE"))
	{
		get_sprites(data, &data->sprites.w_img, line);
		data->count.w_img = 1;
	}
	else
		return (1);
	return (0);
}

static int	ft_process_texture(t_data *data, char *direction, char **split)
{
	int		result;
	char	*line;

	line = ft_strtrim(split[1], "\n");
	result = ft_process_texture_helper(data, direction, line);
	free(line);
	return (result);
}

static void	set_colours(t_data *data, char *direction, t_rgb colour)
{
	if (!ft_strcmp(direction, "F"))
	{
		data->render.floor = colour;
		data->count.floor = 1;
	}
	else if (!ft_strcmp(direction, "C"))
	{
		data->render.sky = colour;
		data->count.sky = 1;
	}
}

static int	ft_process_colour(t_data *data, char *direction, char **split)
{
	char	**colour;
	t_rgb	colour_struct;

	colour = ft_split(split[1], ',');
	colour_struct.r = ft_atoi(colour[0]);
	colour_struct.g = ft_atoi(colour[1]);
	colour_struct.b = ft_atoi(colour[2]);
	free(colour[0]);
	free(colour[1]);
	free(colour[2]);
	free(colour);
	if (!ft_strcmp(direction, "F") || !ft_strcmp(direction, "C"))
	{
		set_colours(data, direction, colour_struct);
		return (0);
	}
	return (1);
}

int	ft_check_line(t_data *data, char **split)
{
	if (!ft_strcmp(split[0], "NO")
		|| !ft_strcmp(split[0], "SO")
		|| !ft_strcmp(split[0], "EA")
		|| !ft_strcmp(split[0], "WE"))
		return (ft_process_texture(data, split[0], split));
	else if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
		return (ft_process_colour(data, split[0], split));
	else if (!ft_strcmp(split[0], "\n"))
		return (0);
	return (1);
}
