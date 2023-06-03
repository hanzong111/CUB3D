/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/06/03 23:41:06 by ojing-ha         ###   ########.fr       */
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

int	check_collision(char **grid, int x, int y)
{
	if (grid[y / 64][x / 64] == '1')
		return (0);
	return (1);
}

void	move_player_coordinates(t_data *data, int keycode, t_dvct dir)
{
	t_dvct	x_axis;
	double	alpha;
	int		x;
	int		y;

	x_axis.x = 1;
	x_axis.y = 0;
	alpha = angle_between_vectors(dir, x_axis);
	x = MOVE_SPEED * cos(alpha);
	y = MOVE_SPEED * sin(alpha);
	data->temp.ray_dir = dir;
	get_player_dir(&data->temp, &data->player);
	if (keycode == S_KEY || keycode == D_KEY)
	{
		x *= -1;
		y *= -1;
	}
	if (data->player.facing.y == NORTH)
	{
		if (check_collision(data->grid, data->player.pos.x + x, data->player.pos.y - y))
		{
			data->player.pos.x += x;
			data->player.pos.y -= y;
		}
	}
	else
	{
		if (check_collision(data->grid, data->player.pos.x + x, data->player.pos.y + y))
		{
			data->player.pos.x += x;
			data->player.pos.y += y;
		}
	}
}

int	event(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		ft_printf("Esc pressed.\n");
		ft_printf("Exiting so_long ...\n");
		exit(0);
	}
	if (keycode == W_KEY || keycode == S_KEY)
		move_player_coordinates(data, keycode, data->player.dir);
	if (keycode == A_KEY || keycode == D_KEY)
		move_player_coordinates(data, keycode,
			rotate_vector(M_PI / 2, data->player.dir));
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

t_rgb	get_color(t_wallinfo wall, t_render r)
{
	if (wall.wall_dir == NORTH)
		return (r.north);
	else if (wall.wall_dir == SOUTH)
		return (r.south);
	else if (wall.wall_dir == EAST)
		return (r.east);
	else
		return (r.west);
}

int	get_start_pixel_color(int	projected_h)
{
	if (projected_h >= SCREEN_H)
		return (0);
	return((SCREEN_H / 2) - (projected_h / 2));
}

void	draw_walls(t_rgb color, t_data_addr d, int	height, int width)
{
	while (height < SCREEN_H)
	{
		d.address[height * d.size_line + width * d.pixel_bits / 8] = color.b;
		d.address[height * d.size_line + width * d.pixel_bits / 8 + 1] = color.g;
		d.address[height * d.size_line + width * d.pixel_bits / 8 + 2] = color.r;
		height++;
	}
}

void	render_simple_color(t_data *data)
{
	int			x;
	int			start_pixel;
	t_rgb		color;
	t_data_addr	des;

	x = -1;
	des.address = mlx_get_data_addr(data->final_img.img, &des.pixel_bits,
						&des.size_line, &des.endian);
	draw_sky_floor(&data->render, des);
	while (++x < SCREEN_W)
	{
		color = get_color(data->wall_info[x], data->render);
		start_pixel = get_start_pixel_color(data->wall_info[x].projected_h);
		while (start_pixel < SCREEN_H && data->wall_info[x].projected_h >= 0)
		{
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8] = color.b;
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8 + 1] = color.g;
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8 + 2] = color.r;
		start_pixel++;
		data->wall_info[x].projected_h--;
		}
	}
}

int	render_next_frame(t_data *data)
{
	if (data->temp.keycode >= 0)
		event(data->temp.keycode, data);
	raytracer(data, data->grid);
	// render_simple_color(data);
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

int	move_mouse(int x, int y, t_data *data)
{
	printf("<%d,%d>\n", x, y);
	(void)data;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	data.grid = malloc(sizeof(char *) * 23);
	data.grid[0] = ft_strdup("111111111");
	data.grid[1] = ft_strdup("100000001");
	data.grid[2] = ft_strdup("111000101");
	data.grid[3] = ft_strdup("101000001");
	data.grid[4] = ft_strdup("100000001");
	data.grid[5] = ft_strdup("100000101");
	data.grid[6] = ft_strdup("1000P0001");
	data.grid[7] = ft_strdup("100000001");
	data.grid[8] = ft_strdup("100001001");
	data.grid[9] = ft_strdup("100000001");
	data.grid[10] = ft_strdup("100001001");
	data.grid[11] = ft_strdup("100001101");
	data.grid[12] = ft_strdup("100000001");
	data.grid[13] = ft_strdup("101000001");
	data.grid[14] = ft_strdup("100000001");
	data.grid[15] = ft_strdup("100100001");
	data.grid[16] = ft_strdup("100000001");
	data.grid[17] = ft_strdup("100010001");
	data.grid[18] = ft_strdup("100000001");
	data.grid[19] = ft_strdup("100000001");
	data.grid[20] = ft_strdup("100100001");
	data.grid[21] = ft_strdup("111111111");
	data.grid[22] = NULL;
	initialize(&data);
	(void)argc;
	(void)argv;
	
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "CUB3D");
	get_sprites(&data);
	data.final_img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	data.final_img.w = SCREEN_W;
	data.final_img.h = SCREEN_H;
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.window, 2, 1L<<0, key_press, &data);
	mlx_hook(data.window, 3, 1L<<1, key_release, &data);
	mlx_hook(data.window, ON_DESTROY, 0L, sl_close_window, &data);
	// mlx_hook(data.window, 6, 0, move_mouse, &data);
	// mlx_mouse_move(data.mlx, data.window, 4, 4);
	mlx_loop(data.mlx);

	// data.mlx = mlx_init();
	// data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "CUB3D");
	// data.final_img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	// data.final_img.w = SCREEN_W;
	// data.final_img.h = SCREEN_H;
	// raytracer(&data, data.grid);
	// render(&data);
	// mlx_put_image_to_window(data.mlx, data.window, data.final_img.img, 0, 0);
	// int x = -1;
	// while (++x <= 22)
	// 	free(data.grid[x]);
	// free(data.grid);
	// free(data.wall_info);
	// mlx_loop(data.mlx);
}
