/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:54:10 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/13 21:42:32 by ojing-ha         ###   ########.fr       */
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

# define NORTH 999
# define SOUTH 888
# define EAST 777
# define WEST 666

# define DEF "\033[0;39m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"

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
	int	hit;
}	t_ivct;

//	Player Struct
typedef struct s_player
{
	t_ivct	pos;
	t_dvct	dir;
	t_ivct	facing;
}	t_player;

//	Collision Struct
typedef struct s_collide
{
	t_ivct	A;
	t_ivct	grid;
	int		X_a;
	int		Y_a;
	double	alpha;
	double	angle_per_line;
}	t_collide;

// Struct to store rgb value
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// // Image Struct 
typedef struct s_data_addr
{
	char	*address;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		pixel;
}	t_data_addr;

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}	t_img;

typedef struct s_temp
{
	t_ivct	v1;
	t_ivct	v2;
	t_ivct	final;
	t_dvct	ray_dir;
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
	double	projected_h;
	int		wall_dir;
	int		sprite_col;
}	t_wallinfo;

//	Render Struct
typedef struct s_render
{
	t_rgb	north;
	t_rgb	south;
	t_rgb	east;
	t_rgb	west;
	t_rgb	sky;
	t_rgb	floor;
}	t_render;

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
	t_wallinfo		*wall_info;
	t_info			info;
	t_render		render;
	t_img			final_img;
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
void	find_first_intersection(t_player *ply, t_temp *temp, t_collide *col, int dir);
int		find_final_intersection(t_collide *col, t_ivct *v, char grid[9][9]);

// Fill Wall Info Functions
void	get_player_dir(t_temp *temp, t_player *player);
int		get_wall_dir(t_temp *temp, t_player *player);
int		get_sprite_col(t_temp	*temp);
void	fill_in_wall_info(t_data *data, int x);

//	Vector Operation Functions
t_dvct	rotate_vector(double rad, t_dvct v);
double	dot_product(t_dvct v1, t_dvct v2);
double	magnitude(t_dvct v);
double	angle_between_vectors(t_dvct v1, t_dvct	v2);
double	calculate_distance(t_ivct ply, t_ivct v);

// Print Functions
void	print_wall_info(t_data *data, int x);

#endif