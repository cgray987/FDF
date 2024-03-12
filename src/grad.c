/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:43:59 by cgray             #+#    #+#             */
/*   Updated: 2024/01/28 16:49:10 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_position(t_3d_vector start, t_3d_vector end, t_3d_vector curr)
{
	float	diag_full;
	float	diag_first_part;

	diag_full = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	diag_first_part = sqrt(pow(curr.x - start.x, 2) + pow(curr.y - start.y, 2));
	if (diag_full)
		return (diag_first_part / diag_full);
	return (1);
}

uint32_t	grad_pt_color(uint32_t a, uint32_t b, float position)
{
	t_color	a_rgba;
	t_color	b_rgba;
	t_color	color;

	a_rgba = split_color(a);
	b_rgba = split_color(b);
	color.r = round(a_rgba.r * (1 - position) + b_rgba.r * position);
	color.g = round(a_rgba.g * (1 - position) + b_rgba.g * position);
	color.b = round(a_rgba.b * (1 - position) + b_rgba.b * position);
	color.a = round(a_rgba.a * (1 - position) + b_rgba.a * position);
	return (merge_color(color.r, color.g, color.b, color.a));
}

uint32_t	grad_pt(t_3d_vector start, t_3d_vector end, t_3d_vector curr)
{
	float	position;

	position = get_position(start, end, curr);
	return (grad_pt_color(start.color, end.color, position));
}
