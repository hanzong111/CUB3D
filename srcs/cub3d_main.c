/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/04 14:47:32 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	export DISPLAY=localhost:0.0	*/
/*	65307 || 53						*/
/* 	W  	  || 13						*/
/*	S  	  || 1						*/
/* 	A  	  || 0						*/
/*	D  	  || 2						*/

// int	event(int keycode, t_data *data)
// {
// 	if (keycode == 65307)
// 	{
// 		ft_printf("Esc pressed.\n");
// 		ft_printf("Exiting so_long ...\n");
// 		exit(0);
// 	}
// 	if (keycode == 'w')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_UP));
// 	if (keycode == 's')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_DOWN));
// 	if (keycode == 'a')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_LEFT));
// 	if (keycode == 'd')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_RIGHT));
// 	return (0);
// }

// int	render_next_frame(t_data *data)
// {
// 	static int	tick;

// 	tick++;
// 	check_move_list(data);
// 	choose_frame(tick, data);
// 	render_map(data);
// 	if (data->map.enemy != 0)
// 		add_enemy(data);
// 	generate_ui(data);
// 	mlx_put_image_to_window(data->mlx, data->window, data->final_img.img, 0, 0);
// 	mlx_destroy_image(data->mlx, data->final_img.img);
// 	return (0);
// }

int	sl_close_window(t_data *data)
{
	data->start_x = 3;
	ft_printf("Window closed.\n");
	ft_printf("Exiting cub3d...\n");
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	// char			grid[9][9] = 
	// {	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', 'P', '0', '0', '0', '1'},
	// 	{'1', '1', '1', '1', '1', '1', '1', '1', '1'}};
	t_player	player;
	player.pos.x = 4;
	player.pos.y = 7;
	player.dir.x = 0;
	player.dir.y = 1;
	printf("x is %f\ny is %f\n", player.pos.x, player.pos.y);
	(void)argc;
	(void)argv;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "so_long");
	// mlx_loop_hook(data.mlx, render_next_frame, &data);
	// mlx_key_hook(data.window, event, &data);
	mlx_hook(data.window, ON_DESTROY, 0L, sl_close_window, &data);
	mlx_loop(data.mlx);
}
