/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:40:05 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/06/03 15:25:22 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	convert(t_data *data, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->w, &img->h);
}

void	get_sprites(t_data *data)
{
	convert(data, "sprites/bb.xpm", &data->sprites.n_img);
	convert(data, "sprites/bb.xpm", &data->sprites.s_img);
	convert(data, "sprites/bb.xpm", &data->sprites.e_img);
	convert(data, "sprites/bb.xpm", &data->sprites.w_img);
	// convert(data, "sprites/1.xpm", &data->sprites.n_img);
	// convert(data, "sprites/2.xpm", &data->sprites.s_img);
	// convert(data, "sprites/3.xpm", &data->sprites.e_img);
	// convert(data, "sprites/4.xpm", &data->sprites.w_img);
}