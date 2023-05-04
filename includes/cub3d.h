/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:54:10 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/04 13:57:34 by ojing-ha         ###   ########.fr       */
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
	t_dvct	pos;
	t_dvct	dir;
}	t_player;

// Image Struct 
typedef struct s_cb_data_addr
{
	char	*address;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		pixel;
}	t_cb_data_addr;

typedef struct s_cb_img
{
	void	*img;
	int		w;
	int		h;
}	t_cb_img;

typedef struct s_cb_player
{
	int				x;
	int				y;
	int				state;
}	t_cb_player;

// Main Global Struct 
typedef struct s_data
{
	void			*mlx;
	void			*window;
	int				start_x;
	int				start_y;
	int				enemy_state;
}	t_data;

#endif