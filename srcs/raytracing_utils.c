/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:41:43 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/06 14:47:39 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	To Calculate Distance between player and a point.	*/
double	calculate_distance(t_ivct ply, t_ivct v)
{
	return (sqrt((ply.x - v.x) * (ply.x - v.x)
			+ (ply.y - v.y) * (ply.y - v.y)));
}
