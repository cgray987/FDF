/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:48:17 by cgray             #+#    #+#             */
/*   Updated: 2024/01/31 15:05:15 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* rotate in all axes and project points */
t_3d_vector	transform(t_3d_vector p, t_fdf *data)
{
	p = rotate_all(p, data);
	if (data->projection == 'I')
		p = iso_proj(p, data);
	if (data->projection == 'P')
		p = para_proj(p, data);
	if (data->projection == 'T')
		p = top_proj(p, data);
	if (data->projection == 'R')
		p = right_proj(p, data);
	if (data->projection == 'F')
		p = front_proj(p, data);
	return (p);
}

/* given two sets of coords, find fastest way to draw from one to the other.
before drawing:
	-find corresponding z altitude/color
	-project coords based selected projection
		-zoom and shift handled in projections
*/
void	bresenham(t_3d_vector vec, t_3d_vector vec1, t_fdf *data)
{
	float		x_step;
	float		y_step;
	float		max;
	t_3d_vector	start;

	vec.z = (float)data->z_matrix[(int)vec.y][(int)vec.x];
	vec1.z = (float)data->z_matrix[(int)vec1.y][(int)vec1.x];
	vec.color = get_color(vec, data);
	vec1.color = get_color(vec1, data);
	vec = transform(vec, data);
	vec1 = transform(vec1, data);
	x_step = vec1.x - vec.x;
	y_step = vec1.y - vec.y;
	max = ft_max(ft_abs(x_step), ft_abs(y_step));
	x_step /= max;
	y_step /= max;
	start = vec;
	while ((int)(vec.x - vec1.x) || (int)(vec.y - vec1.y))
	{
		if ((vec.x > 0 && vec.y > 0) && (vec.x < WIDTH && vec.y < HEIGHT))
			mlx_put_pixel(data->img_ptr, vec.x, vec.y,
				grad_pt(start, vec1, vec));
		vec.x += x_step;
		vec.y += y_step;
	}
}

/* iterate through map values
	uses bresenham's alg to draw lines between points
	put image to window, call menu
 */
void	draw(t_fdf *data)
{
	t_3d_vector	p0;
	t_3d_vector	p1_x;
	t_3d_vector	p1_y;

	p0 = (t_3d_vector){0, 0, 0, 0};
	while (p0.y < data->height)
	{
		p0.x = 0;
		while (p0.x < data->width)
		{
			p1_x = (t_3d_vector){p0.x + 1, p0.y, 0, 0};
			p1_y = (t_3d_vector){p0.x, p0.y + 1, 0, 0};
			if (p1_x.x < data->width)
				bresenham(p0, p1_x, data);
			if (p1_y.y < data->height)
				bresenham(p0, p1_y, data);
			p0.x++;
		}
		p0.y++;
	}
	mlx_image_to_window(data->mlx_ptr, data->img_ptr, 0, 0);
}
