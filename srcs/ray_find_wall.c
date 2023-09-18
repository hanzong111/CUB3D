/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_find_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:43:46 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:32:14 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	h_find_final_intersection(t_temp *tmp,
	t_collide *col, char **grid, t_ivct *v)
{
	if (tmp->ray_dir.y > 0)
		col->grid.y = (int)((col->a.y - 1) / WALL_H);
	else
		col->grid.y = (int)((col->a.y + 1) / WALL_H);
	col->grid.x = (int)(col->a.x / WALL_H);
	while ((int)(col->a.x) >= 0 && (int)(col->a.y) >= 0
		&& (int)(col->a.y) < (col->grid_size.y * WALL_H)
		&& (int)(col->a.x) < (col->row_length[col->grid.y] * WALL_H))
	{
		col->a.x += col->x_a;
		col->a.y += col->y_a;
		if (h_grid_wall_check(tmp, col, grid, v))
			return (1);
		if (tmp->ray_dir.y > 0)
			col->grid.y = (int)((col->a.y - 1) / WALL_H);
		else
			col->grid.y = (int)((col->a.y + 1) / WALL_H);
		col->grid.x = (int)(col->a.x / WALL_H);
	}
	return (0);
}

/*	Checking Horizontal Intersections	*/
void	find_horizontal(t_data *data, char **grid)
{
	data->temp.v1.hit = HORIZONTAL;
	init_horizontal(data);
	if (h_grid_wall_check(&data->temp, &data->col, grid, &data->temp.v1))
		return ;
	if (data->temp.ray_dir.y > 0)
		data->col.y_a = -WALL_H;
	else
		data->col.y_a = WALL_H;
	data->col.x_a = (-data->col.y_a / tan(data->col.alpha));
	if (h_find_final_intersection(&data->temp, &data->col,
			grid, &data->temp.v1))
		return ;
	data->temp.v1.x = OUT_OF_BOUND;
	data->temp.v1.y = OUT_OF_BOUND;
}

int	v_find_final_intersection(t_temp *tmp, t_collide *col,
		char **grid, t_ivct *v)
{
	if (tmp->ray_dir.x > 0)
		col->grid.x = (int)((col->a.x + 1) / WALL_H);
	else
		col->grid.x = (int)((col->a.x - 1) / WALL_H);
	col->grid.y = (int)(col->a.y / WALL_H);
	while ((int)(col->a.x) >= 0 && (int)(col->a.y) >= 0
		&& (int)(col->a.y) < (col->grid_size.y * WALL_H)
		&& (int)(col->a.x) < (col->row_length[col->grid.y] * WALL_H))
	{
		col->a.x += col->x_a;
		col->a.y += col->y_a;
		if (v_grid_wall_check(tmp, col, grid, v))
			return (1);
		if (tmp->ray_dir.x > 0)
			col->grid.x = (int)((col->a.x + 1) / WALL_H);
		else
			col->grid.x = (int)((col->a.x - 1) / WALL_H);
		col->grid.y = (int)(col->a.y / WALL_H);
	}
	return (0);
}

/*	Checking Vertical Intersections	*/
void	find_vertical(t_data *data, char **grid)
{
	data->temp.v2.hit = VERTICAL;
	init_vertical(data);
	if (v_grid_wall_check(&data->temp, &data->col, grid, &data->temp.v2))
		return ;
	if (data->temp.ray_dir.x > 0)
		data->col.x_a = WALL_H;
	else
		data->col.x_a = -WALL_H;
	data->col.y_a = (-data->col.x_a * tan(data->col.alpha));
	if (v_find_final_intersection(&data->temp,
			&data->col, grid, &data->temp.v2))
		return ;
	data->temp.v2.x = OUT_OF_BOUND;
	data->temp.v2.y = OUT_OF_BOUND;
}
