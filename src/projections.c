/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:10:56 by cgray             #+#    #+#             */
/*   Updated: 2024/01/31 15:40:20 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Isometric View
expanded form rotation matrix
theta = 30 degrees in radians
*/
t_3d_vector	iso_proj(t_3d_vector p, t_fdf *data)
{
	float	t_x;
	float	t_y;
	float	theta;

	theta = rad(30);
	t_x = p.x;
	t_y = p.y;
	p.x = ((t_x - t_y) * cos(theta)) * data->zoom + data->shift_x;
	p.y = ((-p.z / data->z_mod) + (t_x + t_y)
			* sin(theta)) * data->zoom + data->shift_y;
	return (p);
}

/* Parallel View
expanded form rotation matrix
theta = 45 degrees in radians
*/
t_3d_vector	para_proj(t_3d_vector p, t_fdf *data)
{
	float	t_z;
	float	theta;

	theta = PI / 4;
	t_z = p.z;
	p.x = (p.x - (t_z / data->z_mod)) * cos(theta) * data->zoom + data->shift_x;
	p.y = (p.y - (t_z / data->z_mod)) * sin(theta) * data->zoom + data->shift_y;
	return (p);
}

/* Front view x = x, y = y*/
t_3d_vector	front_proj(t_3d_vector p, t_fdf *data)
{
	float	t_x;
	float	t_y;

	t_y = p.y;
	t_x = p.x;
	p.x = t_x * data->zoom + data->shift_x;
	p.y = t_y * data->zoom + data->shift_y;
	return (p);
}

/* Side view*/
t_3d_vector	right_proj(t_3d_vector p, t_fdf *data)
{
	float	t_z;
	float	t_y;

	t_y = p.y;
	t_z = p.z;
	p.x = -t_y * data->zoom + data->shift_x;
	p.y = (-t_z / data->z_mod) * data->zoom + data->shift_y;
	return (p);
}

/* Top down view */
t_3d_vector	top_proj(t_3d_vector p, t_fdf *data)
{
	float	t_z;
	float	t_x;

	t_x = p.x;
	t_z = p.z;
	p.x = t_x * data->zoom + data->shift_x;
	p.y = (-t_z / data->z_mod) * data->zoom + data->shift_y;
	return (p);
}
/*
t_3d_vector	spherical_proj(t_3d_vector vec)
{
	float	r;
	float	theta;
	float	phi;
	float	x2;
	float	y2;
	float	z2;

	x2 = vec.x * vec.x;
	y2 = vec.y * vec.y;
	z2 = vec.z * vec.z;

	r = sqrt(x2 + y2 + z2);
	theta = atan2(vec.y, vec.x);
	phi = atan(sqrt(x2 + y2) / vec.z);

	vec.x = r * sin(phi) * cos(theta);
	vec.y = r * sin(phi) * sin(theta);
	vec.z = r * cos(phi);
	return (vec);
} */
