/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:01:10 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/17 22:54:51 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_sky_floor(t_render *render, t_data_addr d)
{
	t_rgb	color;
	int		x;
	int		y;

	y = -1;
	while (++y < SCREEN_H)
	{
		if (y < (SCREEN_H / 2))
			color = render->sky;
		else
			color = render->floor;
		x = -1;
		while (++x < SCREEN_W)
		{
			d.address[y * d.size_line + x * d.pixel_bits / 8] = color.b;
			d.address[y * d.size_line + x * d.pixel_bits / 8 + 1] = color.g;
			d.address[y * d.size_line + x * d.pixel_bits / 8 + 2] = color.r;
		}
	}
}

t_img	get_texture(t_wallinfo wall, t_sprites s)
{
	if (wall.wall_dir == NORTH)
		return (s.n_img);
	else if (wall.wall_dir == SOUTH)
		return (s.s_img);
	else if (wall.wall_dir == EAST)
		return (s.e_img);
	else
		return (s.w_img);
}

int	get_start_pixel_texture(int	projected_h)
{
	return((SCREEN_H / 2) - (projected_h / 2));
}

void	render_texture(t_data *data)
{
	int			x;
	int			start_pixel;
	double		y_step;
	double		scale;
	t_img		img;
	t_data_addr	src;
	t_data_addr	des;

	x = -1;
	des.address = mlx_get_data_addr(data->final_img.img, &des.pixel_bits,
						&des.size_line, &des.endian);
	draw_sky_floor(&data->render, des);
	while (++x < SCREEN_W)
	{
		if (isnan(data->wall_info[x].projected_h) || data->wall_info[x].projected_h <= 0)
	{
		printf("wall height error !!!\n");
		exit (0);
	}
		img = get_texture(data->wall_info[x], data->sprites);
		src.address = mlx_get_data_addr(img.img, &src.pixel_bits,
						&src.size_line, &src.endian);
		start_pixel = ((SCREEN_H / 2) - ((int)data->wall_info[x].projected_h / 2));
		scale = 64 / data->wall_info[x].projected_h;
		y_step = 0;
		while (start_pixel < SCREEN_H && data->wall_info[x].projected_h >= 0)
		{
			if (start_pixel < 0)
			{
				start_pixel++;
				data->wall_info[x].projected_h--;
				y_step += scale;
			}
			else
			{
				if ((int)y_step < 64)
				{
					des.address[start_pixel * des.size_line
						+ x * des.pixel_bits / 8] = src.address[(int)y_step * src.size_line
						+ data->wall_info[x].sprite_col * src.pixel_bits / 8];
					des.address[start_pixel * des.size_line
						+ x * des.pixel_bits / 8 + 1] = src.address[(int)y_step * src.size_line
						+ data->wall_info[x].sprite_col * src.pixel_bits / 8 + 1];
					des.address[start_pixel * des.size_line
						+ x * des.pixel_bits / 8 + 2] = src.address[(int)y_step * src.size_line
						+ data->wall_info[x].sprite_col * src.pixel_bits / 8 + 2];
				}
				start_pixel++;
				data->wall_info[x].projected_h--;
				y_step += scale;
			}
		}
	}

}
