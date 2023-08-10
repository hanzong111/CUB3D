/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:40:05 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/08/09 16:40:20 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	convert(t_data *data, char *path, t_img *img)
// {
// 	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->w, &img->h);
// }

// void	get_sprites(t_data *data)
// {
// 	// convert(data, "sprites/bb.xpm", &data->sprites.n_img);
// 	// convert(data, "sprites/bb.xpm", &data->sprites.s_img);
// 	// convert(data, "sprites/bb.xpm", &data->sprites.e_img);
// 	// convert(data, "sprites/bb.xpm", &data->sprites.w_img);
// 	convert(data, "sprites/1.xpm", &data->sprites.n_img);
// 	convert(data, "sprites/2.xpm", &data->sprites.s_img);
// 	convert(data, "sprites/3.xpm", &data->sprites.e_img);
// 	convert(data, "sprites/4.xpm", &data->sprites.w_img);
// }

void	get_sprites(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		printf("SPRITE ERROR\n");
		ft_exit("SPRITE ERROR\n", 1);
	}
	// img->addr_data.address = mlx_get_data_addr(img->img,
	// 		&img->addr_data.pixel_bits,
	// 		&img->addr_data.size_line,
	// 		&img->addr_data.endian);
}
