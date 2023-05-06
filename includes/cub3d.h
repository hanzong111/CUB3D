/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:54:10 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/06 16:34:52 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include <mlx.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
// Dont Change This :(
# define SCREEN_W 1024
# define SCREEN_H 768
# define WALL_H 64
# define OUT_OF_BOUND 99999
# define HORIZONTAL 80
# define VERTICAL 90

// Some Events
# define MOVE_UP 1
# define MOVE_DOWN 2
# define MOVE_LEFT 3
# define MOVE_RIGHT 4

# define EXIT_CLOSED 1
# define EXIT_OPENED 2

// Event definition
# define ON_DESTROY 17

// Double Vector struct 
typedef struct s_dvct
{
	double	x;
	double	y;
}	t_dvct;

// Int Vector struct
typedef struct s_ivct
{
	int	x;
	int	y;
}	t_ivct;

//	Player Struct
typedef struct s_player
{
	t_ivct	pos;
	t_dvct	dir;
}	t_player;

//	Collision Struct
typedef struct s_collide
{
	t_ivct	A;
	t_ivct	grid;
	int		X_a;
	int		Y_a;
	double	alpha;
}	t_collide;

// // Image Struct 
// typedef struct s_cb_data_addr
// {
// 	char	*address;
// 	int		pixel_bits;
// 	int		size_line;
// 	int		endian;
// 	int		pixel;
// }	t_cb_data_addr;

// typedef struct s_cb_img
// {
// 	void	*img;
// 	int		w;
// 	int		h;
// }	t_cb_img;

typedef struct s_temp
{
	t_ivct	v1;
	t_ivct	v2;
	t_ivct	final;
}	t_temp;

//	pre-defined attributes
typedef struct s_info
{
	int		player_height;
	double	player_fov;
	double	d_to_plane;
	double	angle_between_rays;
}	t_info;

//	Struct to store each wall informations
typedef struct s_wallinfo
{
	int		actual_h;
	int		projected_h;
	int		wall_dir;
}	t_wallinfo;

// Main Global Struct 
typedef struct s_data
{
	void			*mlx;
	void			*window;
	int				start_x;
	int				start_y;
	int				enemy_state;

	t_temp			temp;
	t_player		player;
	t_collide		col;
	t_wallinfo		wall_info[SCREEN_W];
	t_info			info;
}	t_data;

void	initialize(t_data *data);
void	raytracer(t_data *data, char grid[9][9]);

// Ray_find_wall Functions
t_ivct	ray_find_wall(t_data *data, char grid[9][9]);
void	find_horizontal(t_player *ply, t_temp *temp,
			t_collide *col, char grid[9][9]);
void	find_vertical(t_player *ply, t_temp *temp,
			t_collide *col, char grid[9][9]);
int		grid_wall_check(t_collide *col, char grid[9][9], t_ivct *v);
void	find_first_intersection(t_player *ply, t_collide *col, int dir);
int		find_final_intersection(t_collide *col, t_ivct *v, char grid[9][9]);

// Raytracing Utils Functions
double	calculate_distance(t_ivct ply, t_ivct v);
#endif