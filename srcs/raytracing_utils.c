/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:41:43 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/05 17:01:50 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	Grid_Wall_Check(t_collide *col, t_temp *temp, char grid[9][9])
{
	col->grid.x = col->A.x / WALL_H;
	col->grid.y = col->A.y / WALL_H;
	if (grid[col->grid.x][col->grid.y] == '1')
	{
		temp->v1.x = col->A.x;
		temp->v1.y = col->A.y;
		return (1);
	}
	return (0);
}

void	find_horizontal(t_player *ply, t_temp *temp, t_collide *col, char grid[9][9])
{
	col->alpha = atan(ply->dir.y / ply->dir.x);
	if (ply->dir.y > 0)
		col->A.y = (int)(ply->pos.y / WALL_H) * WALL_H - 1;
	else if (ply->dir.y < 0)
		col->A.y = (int)(ply->pos.y / WALL_H) * WALL_H + 64;
	else
	{
		temp->v1.x = OUT_OF_BOUND;
		temp->v1.y = OUT_OF_BOUND;
		return ;
	}
	col->A.x = ply->pos.x + (ply->pos.y - col->A.y)/tan(col->alpha);
	if (Grid_Wall_Check(col, temp, grid))
			return ;
	if (ply->dir.y > 0)
		col->Y_a = -WALL_H;
	else
		col->Y_a = WALL_H;
	col->X_a = WALL_H / tan(col->alpha);
	while (col->A.x < SCREEN_W && col->A.y < SCREEN_H)
	{
		col->A.x += col->X_a;
		col->A.y += col->Y_a;
		if (Grid_Wall_Check(col, temp, grid))
			return ;
	}
	temp->v1.x = OUT_OF_BOUND;
	temp->v1.y = OUT_OF_BOUND;
	printf("X_a is %d\nY_a is %d\n", col->X_a, col->Y_a);
}
