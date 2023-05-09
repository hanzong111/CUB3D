/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_find_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/09 23:29:46 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	To Check if grid that the ray hits is a wall or not.	*/
int	grid_wall_check(t_collide *col, char grid[9][9], t_ivct *v)
{
	col->grid.x = col->A.x / WALL_H;
	col->grid.y = col->A.y / WALL_H;
	if (col->grid.x >= 0 && col->grid.y >= 0
		&& grid[col->grid.y][col->grid.x] == '1')
	{
		v->x = col->A.x;
		v->y = col->A.y;
		return (1);
	}
	return (0);
}

void	find_first_intersection(t_player *ply, t_temp *temp,
		t_collide *col, int dir)
{
	if (dir == HORIZONTAL)
	{
		if (temp->ray_dir.y > 0)
		col->A.y = (int)(ply->pos.y / WALL_H) * WALL_H - 1;
		else if (temp->ray_dir.y < 0)
		col->A.y = (int)(ply->pos.y / WALL_H) * WALL_H + 64;
	}
	else if (dir == VERTICAL)
	{
		if (temp->ray_dir.x > 0)
		col->A.x = (int)(ply->pos.x / WALL_H) * WALL_H + 64;
		else if (temp->ray_dir.x < 0)
		col->A.x = (int)(ply->pos.x / WALL_H) * WALL_H - 1;
	}
}

int	find_final_intersection(t_collide *col, t_ivct *v, char grid[9][9])
{
	while ((col->A.x < SCREEN_W && col->A.x >= 0)
		&& (col->A.y < SCREEN_H && col->A.y >= 0))
	{
		col->A.x += col->X_a;
		col->A.y += col->Y_a;
		if (grid_wall_check(col, grid, v))
			return (1);
	}
	return (0);
}

/*	Checking Horizontal Intersections	*/
void	find_horizontal(t_player *ply, t_temp *temp,
		t_collide *col, char grid[9][9])
{
	temp->v1.hit = HORIZONTAL;
	col->alpha = atan(temp->ray_dir.y / temp->ray_dir.x);
	find_first_intersection(ply, temp, col, HORIZONTAL);
	if (fabs(((60 / SCREEN_W) * M_PI / 180) - temp->ray_dir.y) < __FLT_EPSILON__)
	{
		temp->v1.x = OUT_OF_BOUND;
		temp->v1.y = OUT_OF_BOUND;
		return ;
	}
	col->A.x = ply->pos.x + (ply->pos.y - col->A.y) / tan(col->alpha);
	if (grid_wall_check(col, grid, &temp->v1))
		return ;
	if (temp->ray_dir.y > 0)
		col->Y_a = -WALL_H;
	else
		col->Y_a = WALL_H;
	col->X_a = -col->Y_a / tan(col->alpha);
	if (find_final_intersection(col, &temp->v1, grid))
		return ;
	temp->v1.x = OUT_OF_BOUND;
	temp->v1.y = OUT_OF_BOUND;
}

/*	Checking Vertical Intersections	*/
void	find_vertical(t_player *ply, t_temp *temp,
		t_collide *col, char grid[9][9])
{
	temp->v2.hit = VERTICAL;
	col->alpha = atan(temp->ray_dir.y / temp->ray_dir.x);
	find_first_intersection(ply, temp, col, VERTICAL);
	/*	When ray is being rotated by rotation matrix , computer does not recognise 0.0000 as 0 */
	// if (temp->ray_dir.x < 0.01745 && temp->ray_dir.x > 0)
	// 	temp->ray_dir.x = 0;
	if (fabs(((60 / SCREEN_W) * M_PI / 180) - temp->ray_dir.x) < __FLT_EPSILON__)
	{
		temp->v2.x = OUT_OF_BOUND;
		temp->v2.y = OUT_OF_BOUND;
		return ;
	}
	col->A.y = ply->pos.y + (ply->pos.x - col->A.x) * tan(col->alpha);
	if (grid_wall_check(col, grid, &temp->v2))
		return ;
	if (temp->ray_dir.x > 0)
		col->X_a = WALL_H;
	else
		col->X_a = -WALL_H;
	col->Y_a = -col->X_a * tan(col->alpha);
	if (find_final_intersection(col, &temp->v2, grid))
		return ;
	temp->v2.x = OUT_OF_BOUND;
	temp->v2.y = OUT_OF_BOUND;
}
