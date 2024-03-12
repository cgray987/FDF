/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:18:25 by cgray             #+#    #+#             */
/*   Updated: 2024/01/28 19:20:45 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// make vector from int coords
t_3d_vector	make_point(int x, int y, int z)
{
	t_3d_vector	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

//expanded x rotation matrix
t_3d_vector	rotate_x(t_3d_vector p, t_fdf *data)
{
	float	t_z;
	float	t_y;

	t_z = p.z / data->z_mod;
	t_y = p.y;
	p.y = t_y * cos(data->rotate_x) + t_z * sin(data->rotate_x);
	p.z = -t_y * sin(data->rotate_x) + t_z * cos(data->rotate_x);
	return (p);
}

//expanded y rotation matrix
t_3d_vector	rotate_y(t_3d_vector p, t_fdf *data)
{
	float	t_z;
	float	t_x;

	t_z = p.z / data->z_mod;
	t_x = p.x;
	p.x = t_x * cos(data->rotate_y) + t_z * sin(data->rotate_y);
	p.z = -t_x * sin(data->rotate_y) + t_z * cos(data->rotate_y);
	return (p);
}

//expanded z rotation matrix
t_3d_vector	rotate_z(t_3d_vector p, t_fdf *data)
{
	float	t_x;
	float	t_y;

	t_x = p.x;
	t_y = p.y;
	p.x = t_x * cos(data->rotate_z) - t_y * sin(data->rotate_z);
	p.y = t_x * sin(data->rotate_z) + t_y * cos(data->rotate_z);
	return (p);
}

/*
translates point to origin, calls rotation functions and
translates back to previous position. (rotation about center)
*/
t_3d_vector	rotate_all(t_3d_vector p, t_fdf *data)
{
	p.x -= data->center.x;
	p.y -= data->center.y;
	p.z -= data->center.z;
	p = rotate_z(p, data);
	p = rotate_y(p, data);
	p = rotate_x(p, data);
	p.x += data->center.x;
	p.y += data->center.y;
	p.z += data->center.z;
	return (p);
}
