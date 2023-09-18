/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:14:06 by gualee            #+#    #+#             */
/*   Updated: 2023/09/19 00:14:06 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_start_pixel_texture(int projected_h)
{
	return ((SCREEN_H / 2) - (projected_h / 2));
}

void	fill_texture_pixel(t_data *data, t_data_addr *src,
	t_data_addr *des, t_texture_info *tex_info)
{
	des->address[tex_info->start_pixel * des->size_line
		+ tex_info->x * des->pixel_bits / 8]
		= src->address[(int)tex_info->y_step * src->size_line
		+ data->wall_info[tex_info->x].sprite_col * src->pixel_bits / 8];
	des->address[tex_info->start_pixel * des->size_line
		+ tex_info->x * des->pixel_bits / 8 + 1]
		= src->address[(int)tex_info->y_step * src->size_line
		+ data->wall_info[tex_info->x].sprite_col * src->pixel_bits / 8 + 1];
	des->address[tex_info->start_pixel * des->size_line
		+ tex_info->x * des->pixel_bits / 8 + 2]
		= src->address[(int)tex_info->y_step * src->size_line
		+ data->wall_info[tex_info->x].sprite_col * src->pixel_bits / 8 + 2];
}

void	update_texture_values(int *start_pixel, double *y_step,
	t_wallinfo *wall_info, double scale)
{
	(*start_pixel)++;
	wall_info->projected_h--;
	(*y_step) += scale;
}

// declare a variable of type t_texture_info
// set fields of tex_info
// pass a pointer to tex_info
void	render_texture_helper(t_data *data, t_data_addr *des,
	t_data_addr *src, int x)
{
	int				start_pixel;
	double			y_step;
	double			scale;
	t_texture_info	tex_info;

	start_pixel = ((SCREEN_H / 2) - ((int)data->wall_info[x].projected_h / 2));
	scale = 64 / data->wall_info[x].projected_h;
	y_step = 0;
	while (start_pixel < SCREEN_H && data->wall_info[x].projected_h > 0)
	{
		if (start_pixel < 0)
			update_texture_values(&start_pixel, &y_step,
				&data->wall_info[x], scale);
		else
		{
			tex_info.start_pixel = start_pixel;
			tex_info.x = x;
			tex_info.y_step = y_step;
			if ((int)y_step < 64)
				fill_texture_pixel(data, src, des, &tex_info);
			update_texture_values(&start_pixel, &y_step,
				&data->wall_info[x], scale);
		}
	}
}
