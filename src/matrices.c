/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:10:53 by cgray             #+#    #+#             */
/*   Updated: 2024/01/28 18:28:29 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*----------NO LONGER USED--------------------------------------*/

/* returns vector multiplied by an integer*/
/* t_3d_vector	multiply_vector_x_constant(t_3d_vector v, int n)
{
	v.x = n * v.x;
	v.y = n * v.y;
	v.z = n * v.z;
	return (v);
} */

/* returns vector product of vector x matrix */
/* t_3d_vector	multiply_vector_x_matrix(t_3d_vector v, t_3d_matrix m)
{
	float	*lv;

	lv = (float [3]){v.x, v.y, v.z};
	v.x = lv[0] * m.i.x + lv[1] * m.i.y + lv[2] * m.i.z;
	v.y = lv[0] * m.j.x + lv[1] * m.j.y + lv[2] * m.j.z;
	v.z = lv[0] * m.k.x + lv[1] * m.k.y + lv[2] * m.k.z;
	return (v);
} */

/*returns 3d rotation matrix given rotation angle and the axis to
rotate about
 */
/* t_3d_matrix	rotation_matrix(float deg, char axis)
{
	if (axis == 'x')
		return ((t_3d_matrix){
			(t_3d_vector){1, 0, 0, 0},
			(t_3d_vector){0, cos(deg), -sin(deg), 0},
			(t_3d_vector){0, sin(deg), cos(deg), 0}});
	if (axis == 'y')
		return ((t_3d_matrix){
			(t_3d_vector){cos(deg), 0, -sin(deg), 0},
			(t_3d_vector){0, 1, 0, 0},
			(t_3d_vector){sin(deg), 0, cos(deg), 0}});
	if (axis == 'z')
		return ((t_3d_matrix){
			(t_3d_vector){cos(deg), -sin(deg), 0, 0},
			(t_3d_vector){sin(deg), cos(deg), 0, 0},
			(t_3d_vector){0, 0, 1, 0}});
	else
		return ((t_3d_matrix){
			(t_3d_vector){1, 0, 0, 0},
			(t_3d_vector){0, 1, 0, 0},
			(t_3d_vector){0, 0, 1, 0}});
} */

/* t_3d_vector	sub_vector(t_3d_vector v1, t_3d_vector v2)
{
	t_3d_vector	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

t_3d_vector	add_vector(t_3d_vector v1, t_3d_vector v2)
{
	t_3d_vector	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

void	multiply_matrix_x_matrix(int m1[4][4], int m2[4][4], int res[4][4])
{
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				res[i][j] += m1[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}
//multiplies vector {x,y,z,} by 3x3 rotation matrix for each axis
t_3d_vector	angular_proj(t_3d_vector vec, t_fdf *data)
{
	int		center[4][4];
	int		neg_center[4][4];
	int		rotation[4][4];
	int		res[4][4];


	center = {{1, 0, 0, data->center.x}
	{0, 1, 0, data->center.y}
	{0, 0, 1, data->center.z}
	{0, 0, 0, 1}};
	neg_center = {{1, 0, 0, -data->center.x}
	{0, 1, 0, -data->center.y}
	{0, 0, 1, -data->center.z}
	{0, 0, 0, 1}};

	vec = multiply_vector_x_matrix(vec, rotation_matrix(data->rotate_z, 'z'));
	vec = multiply_vector_x_matrix(vec, rotation_matrix(data->rotate_x, 'x'));
	vec = multiply_vector_x_matrix(vec, rotation_matrix(data->rotate_y, 'y'));
	rotation = {multiply_vector_x_matrix(vec,
			rotation_matrix(data->rotate_z, 'z')),
		multiply_vector_x_matrix(vec, rotation_matrix(data->rotate_x, 'x')),
		multiply_vector_x_matrix(vec, rotation_matrix(data->rotate_y, 'y')),
		{0, 0, 0, 1}};
	res = multiply_matrix_x_matrix(center, rotation, res);
	res = multiply_matrix_x_matrix(res, neg_center, res);

	return (vec);
} */
