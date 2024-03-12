/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:25:29 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 17:33:31 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
|-----------Program Structrure---------------|
1.	read map
	- get height of map -- how many lines
	- get width of map -- how many numbers in each line
	- allocate mem for int matrix using H x W
	- read map and place into matrix
		--ft_split && ft_atoi
2.	initialize varialbles
	- zoom/translation to center
	- rotations/z_mod
	-create window and image pointer
3. Draw on Screen
	-iterate thru int matrix
	-assign color to point based on scheme or map data
	-convert point to 3d
		-transform point
			- ISO/PARALLEL/TOP VIEW
			- FRONT VIEW/SIDE VIEW
		- Rotate point
			-translate each point to center
			-rotate based on axis
			-translate back
	-bresenham alg
		-point and next point
		-find steps (slopes) between each point, &
		normalize together
		-plot line between points in image
			-each pixel uses gradient between two points
4. Loop/Hooks
			🔲CONTROLS🔲
	Translate:				WASD
	Zoom:					Mousewheel
	Colors:					Z, X, C, V
							🌵 🔥 🧊 🌸
	Raise/Lower Height:		-/+
	Projections:
			ISOMETRIC:		1
			PARALLEL: 		2
			FRONT VIEW:		3
			TOP VIEW:		4
			SIDE VIEW:		5
	Rotations:				(NUMPAD KEYS)
							(-)		(+)
			X-AXIS:			5		8
			Y-AXIS:			4		6
			Z-AXIS:			7		9

	-zoom:multiplies points by value 1:100
	-shift: adds points by value
	-rotation: uses rotation matrix for each axis 0:360 deg
		-adds/subtracts 5 degrees per input
	-z_mod uses z_height / z_mod to change elevations
	-Projection uses different projgections to transform
	points.
		-ISO uses view angle of 30 degrees (PI/6)
		-PARALLEL uses view angle of 45 degrees (PI/4)
	-colors cycle through predetermined color schemes



|-----------------------------------------------|
*/
#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../lib/mlx/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265359
# define PI_2 6.28318530718

/* colors based on z_height
	-high: z_max = high
	-neutral: z_max > neutral > 0
	-low: 0 >= low
 */
typedef struct s_color_scheme
{
	int			flag;
	uint32_t	high;
	uint32_t	neutral;
	uint32_t	low;
}	t_color_scheme;

/*
	{x, y, z, color}
 */
typedef struct s_3d_vector
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}	t_3d_vector;

typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color;

/*
	General meta variables. Initialized in init.c,
	populated from the map in read_file.c
	modified by hooks.c (input)
	Contains window and img pointer needed for MLX42
 */
typedef struct s_fdf
{
	int				width;
	int				height;
	t_3d_vector		center;
	int				**z_matrix;
	int				z_max;
	int				z_min;
	int				zoom;
	int				shift_x;
	int				shift_y;
	float			rotate_x;
	float			rotate_y;
	float			rotate_z;
	float			z_mod;
	char			projection;
	int				**color_matrix;
	t_color_scheme	color_scheme;

	mlx_t			*mlx_ptr;
	mlx_image_t		*img_ptr;

}	t_fdf;

/* ------------------------FDF.C------------------------------ */
void			show_controls_terminal(void);
void			free_fdf(t_fdf *data);
int				main(int argc, char **argv);

/* ------------------------init.c------------------------------ */
void			init_fdf(t_fdf *data, char *str);
void			reset_window(t_fdf *data);
void			clean_img(mlx_image_t *image);
void			clear_rot(t_fdf *data);
void			data_limits(t_fdf *data);

/* ------------------------read_file.c------------------------------ */
void			read_file(char *file_name, t_fdf *data);
void			read_malloc(char *file_name, t_fdf *data);
void			z_lim(t_fdf *data);
void			find_origin(t_fdf *data);

/* ------------------------read_utils.c------------------------------ */
int				map_height(char *file_name);
int				map_width(char *file_name);
void			fill_matrix(int *z_matrix_line,
					int *color_mat_line, char *line);

/* ------------------------draw.c------------------------------ */
void			draw(t_fdf *data);
void			bresenham(t_3d_vector vec, t_3d_vector vec1, t_fdf *data);
t_3d_vector		transform(t_3d_vector p, t_fdf *data);

/* ------------------------projections.c------------------------------ */
t_3d_vector		iso_proj(t_3d_vector p, t_fdf *data);
t_3d_vector		para_proj(t_3d_vector p, t_fdf *data);
t_3d_vector		front_proj(t_3d_vector p, t_fdf *data);
t_3d_vector		right_proj(t_3d_vector p, t_fdf *data);
t_3d_vector		top_proj(t_3d_vector p, t_fdf *data);

/* ------------------------rotate.c------------------------------ */
t_3d_vector		rotate_all(t_3d_vector p, t_fdf *data);
t_3d_vector		rotate_z(t_3d_vector p, t_fdf *data);
t_3d_vector		rotate_y(t_3d_vector p, t_fdf *data);
t_3d_vector		rotate_x(t_3d_vector p, t_fdf *data);

/* ------------------------color.c------------------------------ */
void			color_schemes(t_fdf *data);
uint32_t		get_color(t_3d_vector vec, t_fdf *data);
int				color_from_str(char *str);
t_color			split_color(uint32_t rgba);
int				merge_color(int r, int g, int b, int a);

/* ------------------------grad.c------------------------------ */
uint32_t		grad_pt(t_3d_vector start, t_3d_vector end, t_3d_vector curr);
uint32_t		grad_pt_color(uint32_t a, uint32_t b, float position);
float			get_position(t_3d_vector start, t_3d_vector end, t_3d_vector curr);

/* ------------------------hooks.c------------------------------ */
void			menu_hook(t_fdf *data);
mlx_scrollfunc	zoom_scroll_hook(double xdelta, double ydelta, void *param);
mlx_keyfunc		key_hook_fdf(mlx_key_data_t keydata, void *param);
void			key_proj(mlx_key_data_t keydata, t_fdf *data);
void			key_shift(mlx_key_data_t keydata, t_fdf *data);

/* ------------------------hooks2.c------------------------------ */
void			key_colors(mlx_key_data_t keydata, t_fdf *data);
void			call_keys(mlx_key_data_t keydata, t_fdf *data);

/* ------------------------error.c------------------------------ */
int				filename_error(char *fd);
void			ft_error(void);

/* ------------------------trig.c------------------------------ */
float			rad(float deg);
float			deg(float rad);

/* ------------------------NO LONGER USED------------------------------ */
/* ------------------------matricies.c------------------------------ */
/* ------------------------NO LONGER USED------------------------------ */
/* t_3d_vector		angular_proj(t_3d_vector vec, t_fdf *data);
t_3d_vector	multiply_vector_x_matrix(t_3d_vector v, t_3d_matrix m);
t_3d_vector		multiply_vector_x_constant(t_3d_vector v, int n);
t_3d_matrix		rotation_matrix(float deg, char axis);
t_3d_vector	spherical_proj(t_3d_vector vec);

	// 3x4 Matrix
	// i- {x, y, z, color;
	// j-  x, y, z, color;
	// k-  x, y, z, color};
typedef struct s_3d_matrix
{
	t_3d_vector	i;
	t_3d_vector	j;
	t_3d_vector	k;
}	t_3d_matrix; */

#endif
