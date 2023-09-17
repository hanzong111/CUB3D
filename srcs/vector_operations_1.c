/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:21:59 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/17 22:54:54 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_dvct	rotate_vector(double rad, t_dvct v)
{
	t_dvct	temp;

	temp.x = cos(rad) * v.x - sin(rad) * v.y;
	temp.y = sin(rad) * v.x + cos(rad) * v.y;
	return (temp);
}

double	dot_product(t_dvct v1, t_dvct v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	magnitude(t_dvct v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	angle_between_vectors(t_dvct v1, t_dvct	v2)
{
	return (acos(dot_product(v1, v2) / (magnitude(v1) * magnitude(v2))));
}

/*	To Calculate Distance between player and a point.	*/
double	calculate_distance(t_ivct ply, t_ivct v)
{
	return (sqrt((ply.x - v.x) * (ply.x - v.x)
			+ (ply.y - v.y) * (ply.y - v.y)));
}
