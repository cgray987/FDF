/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:27:56 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 15:33:19 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Set initial variable values, initialize window/image, zoom/rotation, shift
	init images
 */
void	init_fdf(t_fdf *data, char *str)
{
	char	*title;

	data->zoom = WIDTH / (data->width + 100);
	data->shift_x = (WIDTH / 2) - (.25 * data->width * data->zoom);
	data->shift_y = (HEIGHT / 2) - (.5 * data->height * data->zoom);
	data->rotate_x = 0;
	data->rotate_z = 0;
	data->rotate_y = 0;
	data->z_mod = 1;
	data->color_scheme.flag = '1';
	data->projection = 'I';
	title = ft_strjoin("FDF - ", str + 5);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, title, false);
	if (!data->mlx_ptr)
		ft_error();
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_ptr)
		ft_error();
	free(title);
}
// data->img_menu = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);

/* Controls rotation, zoom, z_mod limits */
void	data_limits(t_fdf *data)
{
	if (data->rotate_x > PI_2 || data->rotate_x < -PI_2)
		data->rotate_x = 0;
	if (data->rotate_y > PI_2 || data->rotate_y < -PI_2)
		data->rotate_y = 0;
	if (data->rotate_z > PI_2 || data->rotate_z < -PI_2)
		data->rotate_z = 0;
	if (data->zoom <= 2)
		data->zoom = 2;
	if (data->zoom > 100)
		data->zoom = 100;
	if (data->z_mod < 1)
		data->z_mod = 1;
	if (data->z_mod > 100)
		data->z_mod = 100;
}

/* sets rotation back to 0 */
void	clear_rot(t_fdf *data)
{
	data->rotate_x = 0;
	data->rotate_z = 0;
	data->rotate_y = 0;
}

/* clears image of previous drawings */
void	clean_img(mlx_image_t *image)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
			mlx_put_pixel(image, i, j, 0x00000000);
	}
}
/*
deletes image, draws on new image and push to window

void	reset_window(t_fdf *data)
{
	mlx_delete_image(data->mlx_ptr, data->img_ptr);
	mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	draw(data);
	mlx_image_to_window(data->mlx_ptr, data->img_ptr, 0, 0);
}
*/
/*
	if (data->shift_x > WIDTH)
		data->shift_x = WIDTH;
	if (data->shift_y > HEIGHT)
		data->shift_y = HEIGHT;
	if (data->shift_x < 2)
		data->shift_x = 2;
	if (data->shift_y < 2)
		data->shift_y = 2; */
