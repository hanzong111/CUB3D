/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_find_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:43:46 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/26 14:57:03 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_ray_dir(t_temp *temp)
{
	temp->facing.x = 0;
	temp->facing.y = 0;
	if (temp->ray_dir.x > 0)
		temp->facing.x = EAST;
	else
		temp->facing.x = WEST;
	if (temp->ray_dir.y > 0)
		temp->facing.y = NORTH;
	else
		temp->facing.y = SOUTH;
}

int	h_grid_wall_check(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
// 	printf("\n\nAt <%d,%d>\n", col->A.x, col->A.y);
// 	printf("is %d\n", col->A.x % WALL_H);
	if (tmp->ray_dir.y > 0)
		col->grid.y = (int)((col->A.y - 1) / WALL_H);
	else
		col->grid.y = (int)((col->A.y + 1) / WALL_H);
	col->grid.x = (int)(col->A.x / WALL_H);
	if (col->grid.x >= 0 && col->grid.y >= 0
		&& col->grid.x < col->grid_size.x
		&& col->grid.y < col->grid_size.y
		&& grid[col->grid.y][col->grid.x] == '1')
	{
		// printf("final grid<%d,%d>\n", col->grid.x, col->grid.y);
		v->x = (int)col->A.x;
		v->y = (int)col->A.y;
		return (1);
	}
	return (0);
}

int	h_find_final_intersection(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
	while (((int)(col->A.x) < (col->grid_size.x * WALL_H) && (int)(col->A.x) >= 0)
		&& ((int)(col->A.y)< (col->grid_size.y * WALL_H) && (int)(col->A.y)>= 0))
	{
		col->A.x += col->X_a;
		col->A.y += col->Y_a;
		if (h_grid_wall_check(tmp, col, grid, v))
			return (1);
	}
	return (0);
}

/*	Checking Horizontal Intersections	*/
void	find_horizontal(t_data *data, char **grid)
{
	data->temp.v1.hit = HORIZONTAL;
	data->col.alpha = atan(data->temp.ray_dir.y / data->temp.ray_dir.x);
	if (data->temp.ray_dir.y > 0)
		data->col.A.y = (int)(data->player.pos.y / WALL_H) * WALL_H;
	else if (data->temp.ray_dir.y < 0)
		data->col.A.y = (int)(data->player.pos.y / WALL_H) * WALL_H + 64;
	else if (fabs(((60 / SCREEN_W) * M_PI / 180) - data->temp.ray_dir.y) < __FLT_EPSILON__)
	{
		data->temp.v1.x = OUT_OF_BOUND;
		data->temp.v1.y = OUT_OF_BOUND;
		return ;
	}
	data->col.A.x = data->player.pos.x + (data->player.pos.y - data->col.A.y) / tan(data->col.alpha);
	if (h_grid_wall_check(&data->temp, &data->col, grid, &data->temp.v1))
		return ;
	if (data->temp.ray_dir.y > 0)
		data->col.Y_a = -WALL_H;
	else
		data->col.Y_a = WALL_H;
	data->col.X_a = (-data->col.Y_a / tan(data->col.alpha));
	if (h_find_final_intersection(&data->temp, &data->col, grid, &data->temp.v1))
		return ;
	data->temp.v1.x = OUT_OF_BOUND;
	data->temp.v1.y = OUT_OF_BOUND;
}

int	v_grid_wall_check(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
	if (tmp->ray_dir.x > 0)
		col->grid.x = (int)((col->A.x + 1) / WALL_H);
	else
		col->grid.x = (int)((col->A.x - 1) / WALL_H);
	col->grid.y = (int)(col->A.y / WALL_H);
	if (col->grid.x >= 0 && col->grid.y >= 0
		&& col->grid.x < col->grid_size.x
		&& col->grid.y < col->grid_size.y
		&& grid[col->grid.y][col->grid.x] == '1')
	{
		v->x = (int)col->A.x;
		v->y = (int)col->A.y;
		return (1);
	}
	return (0);
}

int	v_find_final_intersection(t_temp *tmp, t_collide *col, char **grid, t_ivct *v)
{
	while (((int)(col->A.x) < (col->grid_size.x * WALL_H) && (int)(col->A.x) >= 0)
		&& ((int)(col->A.y)< (col->grid_size.y * WALL_H) && (int)(col->A.y)>= 0))
	{
		col->A.x += col->X_a;
		col->A.y += col->Y_a;
		if (v_grid_wall_check(tmp, col, grid, v))
			return (1);
	}
	return (0);
}

/*	Checking Vertical Intersections	*/
void	find_vertical(t_data *data, char **grid)
{
	data->temp.v2.hit = VERTICAL;
	data->col.alpha = atan(data->temp.ray_dir.y / data->temp.ray_dir.x);
	if (data->temp.ray_dir.x > 0)
		data->col.A.x = (int)(data->player.pos.x / WALL_H) * WALL_H + 64;
	else if (data->temp.ray_dir.x < 0)
		data->col.A.x = (int)(data->player.pos.x / WALL_H) * WALL_H;
	else if (fabs(((60 / SCREEN_W) * M_PI / 180) - data->temp.ray_dir.x) < __FLT_EPSILON__)
	{
		data->temp.v2.x = OUT_OF_BOUND;
		data->temp.v2.y = OUT_OF_BOUND;
		return ;
	}
	data->col.A.y = data->player.pos.y + (data->player.pos.x - data->col.A.x) * tan(data->col.alpha);
	// printf("At grid <%d,%d>\n", data->col.A.x, data->col.A.y);
	// printf("At grid <%d,%d>\n", data->col.A.x / 64, data->col.A.y / 64);
	if (v_grid_wall_check(&data->temp, &data->col, grid, &data->temp.v2))
		return ;
	if (data->temp.ray_dir.x > 0)
		data->col.X_a = WALL_H;
	else
		data->col.X_a = -WALL_H;
	data->col.Y_a = (-data->col.X_a * tan(data->col.alpha));
	if (v_find_final_intersection(&data->temp, &data->col, grid, &data->temp.v2))
		return ;
	// printf("here\n");
	data->temp.v2.x = OUT_OF_BOUND;
	data->temp.v2.y = OUT_OF_BOUND;
}
