/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/16 21:43:44 by ojing-ha         ###   ########.fr       */
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

int	check_collision(char **grid, double x, double y)
{
	if (grid[(int)y / 64][(int)x / 64] == '1')
		return (0);
	return (1);
}

void	move_player(t_data *data, int keycode)
{
	t_dvct	move_dir;

	move_dir.x = 0;
	move_dir.y = 0;
	if (keycode == W_KEY)
		move_dir = rotate_vector(0, data->player.dir);
	else if (keycode == A_KEY)
		move_dir = rotate_vector(90 * M_PI / 180 , data->player.dir);
	else if (keycode == D_KEY)
		move_dir = rotate_vector(-90 * M_PI / 180 , data->player.dir);
	else if (keycode == S_KEY)
		move_dir = rotate_vector(180 * M_PI / 180 , data->player.dir);
	move_dir.x *= MOVE_SPEED;
	move_dir.y *= MOVE_SPEED;
	move_dir.y *= -1;
	if (check_collision(data->game.map, (data->player.pos.x + (int)move_dir.x), (data->player.pos.y + (int)move_dir.y)))
	{
		data->player.pos.x = (data->player.pos.x + (int)move_dir.x);
		data->player.pos.y = (data->player.pos.y + (int)move_dir.y);
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
	raytracer(data, data->game.map);
	// render_simple_color(data);
	// printf("Player is at <%d, %d>\n", data->player.pos.x / 64 , data->player.pos.y / 64);
	// printf("It is in a %c\n", data->grid[data->player.pos.y / 64][data->player.pos.x / 64]);
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

void	convert(t_data *data, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->w, &img->h);
	printf("ptr is %p\n", img->img);
	if (!img->img)
	{
		printf("no sprites!!\n");
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	t_data			data;

// data.game.map = malloc(sizeof(char *) * 23);
// 	data.game.map[0] = ft_strdup("111111111111");
// 	data.game.map[1] = ft_strdup("1000001100001");
// 	data.game.map[2] = ft_strdup("111001111100111111111111");
// 	data.game.map[3] = ft_strdup("101001   100000000000011");
// 	data.game.map[4] = ft_strdup("100001111100000000000001");
// 	data.game.map[5] = ft_strdup("100000000000000000000001");
// 	data.game.map[6] = ft_strdup("1000W0001111111111111111");
// 	data.game.map[7] = ft_strdup("100000001");
// 	data.game.map[8] = ft_strdup("100001001");
// 	data.game.map[9] = ft_strdup("100000001");
// 	data.game.map[10] = ft_strdup("100001001");
// 	data.game.map[11] = ft_strdup("100001101");
// 	data.game.map[12] = ft_strdup("100000001");
// 	data.game.map[13] = ft_strdup("101000001");
// 	data.game.map[14] = ft_strdup("100000001");
// 	data.game.map[15] = ft_strdup("100100001");
// 	data.game.map[16] = ft_strdup("100000001");
// 	data.game.map[17] = ft_strdup("100010001");
// 	data.game.map[18] = ft_strdup("100000001");
// 	data.game.map[19] = ft_strdup("100000001");
// 	data.game.map[20] = ft_strdup("100100001");
// 	data.game.map[21] = ft_strdup("111111111");
// 	data.game.map[22] = NULL;

	data.render.sky.r = -1;
	data.render.sky.g = -1;
	data.render.sky.b = -1;
	data.render.floor.r = -1;
	data.render.floor.g = -1;
	data.render.floor.b = -1;
	data.sprites.n_img.img = NULL;
	data.sprites.s_img.img = NULL;
	data.sprites.e_img.img = NULL;
	data.sprites.w_img.img = NULL;
	data.count.n_img = 0;
	data.count.s_img = 0;
	data.count.e_img = 0;
	data.count.w_img = 0;
	data.count.sky = 0;
	data.count.floor = 0;
	
	data.mlx = mlx_init();
	// data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "CUB3D");
	initialize_map(&data, argv[1]);
	initialize(&data);
	(void)argc;
	(void)argv;

	// get_sprites(&data);
	// data.final_img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	// data.final_img.w = SCREEN_W;
	// data.final_img.h = SCREEN_H;
	// mlx_loop_hook(data.mlx, render_next_frame, &data);
	// mlx_hook(data.window, 2, 1L << 0, key_press, &data);
	// mlx_hook(data.window, 3, 1L << 1, key_release, &data);
	// mlx_hook(data.window, ON_DESTROY, 0L, sl_close_window, &data);
	// mlx_loop(data.mlx);
}
// mlx_hook(data.window, 6, 0, move_mouse, &data);
// mlx_mouse_move(data.mlx, data.window, 4, 4);

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
