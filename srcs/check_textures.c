/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:04:55 by gualee            #+#    #+#             */
/*   Updated: 2023/08/09 16:40:10 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_process_texture(t_data *data, char *direction, char **split)
{
	char	*line;

	line = ft_strtrim(split[1], "\n");
	if (!ft_strcmp(direction, "NO"))
	{
		get_sprites(data, &data->sprites.n_img, line);
		data->count.n_img = 1;
		printf("North sprites saved!!\n");
	}
	else if (!ft_strcmp(direction, "SO"))
	{
		get_sprites(data, &data->sprites.s_img, line);
		data->count.s_img = 1;
		printf("South sprites saved!!\n");
	}
	else if (!ft_strcmp(direction, "EA"))
	{
		get_sprites(data, &data->sprites.e_img, line);
		data->count.e_img = 1;
		printf("East sprites saved!!\n");
	}
	else if (!ft_strcmp(direction, "WE"))
	{
		get_sprites(data, &data->sprites.w_img, line);
		data->count.w_img = 1;
		printf("West sprites saved!!\n");
	}
	else
	{
		printf("No Sprites Saved!!\n");
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

static int	ft_process_colour(t_data *data, char *direction, char **split)
{
	char	**colour;
	int		r;
	int		g;
	int		b;

	colour = ft_split(split[1], ',');
	r = ft_atoi(colour[0]);
	g = ft_atoi(colour[1]);
	b = ft_atoi(colour[2]);
	if (!ft_strcmp(direction, "F"))
	{
		data->render.floor.r = r;
		data->render.floor.g = g;
		data->render.floor.b = b;
		data->count.floor = 1;
		printf("Floor color saved !!\n");
	}
	else if (!ft_strcmp(direction, "C"))
	{
		data->render.sky.r = r;
		data->render.sky.g = g;
		data->render.sky.b = b;
		data->count.sky = 1;
		printf("Sky color saved !!\n");
	}
	else
		return (1);
	return (0);
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
