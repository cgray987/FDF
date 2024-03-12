/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:38 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 14:21:18 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Sets predetermined color schemes
	Keys- z, x, c, v
 */
void	color_schemes(t_fdf *data)
{
	if (data->color_scheme.flag == '1')
	{
		data->color_scheme.high = 0x09ed05FF;
		data->color_scheme.neutral = 0xC28F8FFF;
		data->color_scheme.low = 0xFFFFFFFF;
	}
	if (data->color_scheme.flag == '2')
	{
		data->color_scheme.high = 0xff002bFF;
		data->color_scheme.neutral = 0xFFe600FF;
		data->color_scheme.low = 0x010101FF;
	}
	if (data->color_scheme.flag == '3')
	{
		data->color_scheme.high = 0xb4eaf0FF;
		data->color_scheme.neutral = 0x3d4f91FF;
		data->color_scheme.low = 0xdb84d5FF;
	}
	if (data->color_scheme.flag == '4')
	{
		data->color_scheme.high = 0xff0088FF;
		data->color_scheme.neutral = 0x4ca63cFF;
		data->color_scheme.low = 0xFFFFFFFF;
	}
}

/*
	returns color based on map color,
	if no map color, retrieve from color scheme
	--do not like this method, would rather use gradient
		between z_min and z_max
 */
uint32_t	get_color(t_3d_vector vec, t_fdf *data)
{
	uint32_t	color;

	color = 0xFFFFFFFF;
	color_schemes(data);
	if (data->color_matrix[(int)vec.y][(int)vec.x] != 0)
	{
		color = data->color_matrix[(int)vec.y][(int)vec.x];
		return (color);
	}
	else if (vec.z == data->z_max)
		color = data->color_scheme.high;
	else if (vec.z >= data->z_min)
		color = data->color_scheme.low;
	else
		color = data->color_scheme.neutral;
	return (color);
}

/* given individual rgba values, return int color */
int	merge_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* splits int color into t_color struct */
t_color	split_color(uint32_t rgba)
{
	t_color	color;

	color = (t_color){0, 0, 0, 0};
	if (rgba > 0xFFFFFF)
		color.a = 8;
	color.r = (rgba >> (16 + color.a)) & 0xFF;
	color.g = (rgba >> (8 + color.a)) & 0xFF;
	color.b = (rgba >> (color.a)) & 0xFF;
	if (color.a)
		color.a = rgba & 0xFF;
	return (color);
}

/* returns int color from given string
checks that string has '0x'
checks if color has alpha value
returns white if color not found in str */
int	color_from_str(char *str)
{
	t_color	color;

	if (str && str + 2)
	{
		color = split_color(ft_atoi_base(str + 2, 16));
		if (ft_strlen(str + 2) > 0 && ft_strlen(str + 2) < 7)
			color.a = 0xFF;
		return (merge_color(color.r, color.g, color.b, color.a));
	}
	return (merge_color(0xFF, 0xFF, 0xFF, 0xFF));
}
