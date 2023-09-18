/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_find_wall_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:15:07 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 21:15:07 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	h_grid_wall_check(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
	if (tmp->ray_dir.y > 0)
		col->grid.y = (int)((col->a.y - 1) / WALL_H);
	else
		col->grid.y = (int)((col->a.y + 1) / WALL_H);
	col->grid.x = (int)(col->a.x / WALL_H);
	if (col->grid.x >= 0 && col->grid.y >= 0
		&& col->grid.y < col->grid_size.y
		&& col->grid.x < col->row_length[col->grid.y]
		&& grid[col->grid.y][col->grid.x] == '1')
	{
		v->x = (int)col->a.x;
		v->y = (int)col->a.y;
		return (1);
	}
	return (0);
}

void	init_horizontal(t_data *data)
{
	data->col.alpha = atan(data->temp.ray_dir.y / data->temp.ray_dir.x);
	if (data->temp.ray_dir.y > 0)
		data->col.a.y = (int)(data->player.pos.y / WALL_H) * WALL_H;
	else if (data->temp.ray_dir.y < 0)
		data->col.a.y = (int)(data->player.pos.y / WALL_H) * WALL_H + 64;
	else if (fabs(((data->info.player_fov / SCREEN_W) * M_PI / 180)
			- data->temp.ray_dir.y) < __FLT_EPSILON__)
	{
		data->temp.v1.x = OUT_OF_BOUND;
		data->temp.v1.y = OUT_OF_BOUND;
		return ;
	}
	data->col.a.x = data->player.pos.x
		+ (data->player.pos.y - data->col.a.y) / tan(data->col.alpha);
}

int	v_grid_wall_check(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
	if (tmp->ray_dir.x > 0)
		col->grid.x = (int)((col->a.x + 1) / WALL_H);
	else
		col->grid.x = (int)((col->a.x - 1) / WALL_H);
	col->grid.y = (int)(col->a.y / WALL_H);
	if (col->grid.x >= 0 && col->grid.y >= 0
		&& col->grid.y < col->grid_size.y
		&& col->grid.x < col->row_length[col->grid.y]
		&& grid[col->grid.y][col->grid.x] == '1')
	{
		v->x = (int)col->a.x;
		v->y = (int)col->a.y;
		return (1);
	}
	return (0);
}

void	init_vertical(t_data *data)
{
	data->col.alpha = atan(data->temp.ray_dir.y / data->temp.ray_dir.x);
	if (data->temp.ray_dir.x > 0)
		data->col.a.x = (int)(data->player.pos.x / WALL_H) * WALL_H + 64;
	else if (data->temp.ray_dir.x < 0)
		data->col.a.x = (int)(data->player.pos.x / WALL_H) * WALL_H;
	else if (fabs(((data->info.player_fov / SCREEN_W) * M_PI / 180)
			- data->temp.ray_dir.x) < __FLT_EPSILON__)
	{
		data->temp.v2.x = OUT_OF_BOUND;
		data->temp.v2.y = OUT_OF_BOUND;
		return ;
	}
	data->col.a.y = data->player.pos.y
		+ (data->player.pos.x - data->col.a.x) * tan(data->col.alpha);
}
