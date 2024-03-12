/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:40:45 by cgray             #+#    #+#             */
/*   Updated: 2024/01/31 14:49:30 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* handle keys for color schemes */
void	key_colors(mlx_key_data_t keydata, t_fdf *data)
{
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		data->color_scheme.flag = '1';
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		data->color_scheme.flag = '2';
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		data->color_scheme.flag = '3';
	if (keydata.key == MLX_KEY_V && keydata.action == MLX_PRESS)
		data->color_scheme.flag = '4';
}

void	call_keys(mlx_key_data_t keydata, t_fdf *data)
{
	key_shift(keydata, data);
	key_proj(keydata, data);
	key_colors(keydata, data);
	clean_img(data->img_ptr);
}
