/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/17 14:18:27 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	export DISPLAY=localhost:0.0	*/
/*	65307 || 53						*/
/* 	W  	  || 13						*/
/*	S  	  || 1						*/
/* 	A  	  || 0						*/
/*	D  	  || 2						*/
/*	keypress = 2					*/
/*	keyrelease = 3					*/

int	event(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		ft_printf("Esc pressed.\n");
		ft_printf("Exiting so_long ...\n");
		exit(0);
	}
	if (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY || keycode == D_KEY )
		move_player(data, keycode);
	if (keycode == LEFT_ARROW)
		data->player.dir = rotate_vector((TURN_SPEED)
				* M_PI / 180, data->player.dir);
	if (keycode == RIGHT_ARROW)
		data->player.dir = rotate_vector(-(TURN_SPEED)
				* M_PI / 180, data->player.dir);
	return (0);
}


int	sl_close_window(t_data *data)
{
	(void)data;
	ft_printf("Window closed.\n");
	ft_printf("Exiting cub3d...\n");
	exit(0);
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->temp.keycode >= 0)
		event(data->temp.keycode, data);
	raytracer(data, data->game.map);
	render_texture(data);
	mlx_put_image_to_window(data->mlx, data->window, data->final_img.img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	data->temp.keycode = keycode;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	(void)keycode;
	data->temp.keycode = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	(void)argc;
	initialize(&data);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "CUB3D");
	data.final_img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	data.final_img.w = SCREEN_W;
	data.final_img.h = SCREEN_H;
	initialize_map(&data, argv[1]);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.window, 2, 1L << 0, key_press, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release, &data);
	mlx_hook(data.window, ON_DESTROY, 0L, sl_close_window, &data);
	mlx_loop(data.mlx);
}
