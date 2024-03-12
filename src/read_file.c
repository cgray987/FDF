/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:50:59 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 17:33:12 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//reads map and places into fdf data matrix
void	find_origin(t_fdf *data)
{
	t_3d_vector	center;

	center.x = data->width / 2;
	center.y = data->height / 2;
	center.z = (data->z_max - data->z_min) / 2;
	data->center = center;
}

// finds min and max z value
void	z_lim(t_fdf *data)
{
	int	max;
	int	min;
	int	i;
	int	j;

	max = 0;
	min = 0;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->z_matrix[i][j] > max)
				max = data->z_matrix[i][j];
			if (data->z_matrix[i][j] < min)
				min = data->z_matrix[i][j];
			j++;
		}
		i++;
	}
	data->z_max = max;
	data->z_min = min;
}

/* mallocs matricies for height and colors
	- must malloc extra space in rows because of my shitty code
	  to prevent overwriting memory
		-printf("allocating %p\n", data->color_matrix[i]);
 */
void	read_malloc(char *file_name, t_fdf *data)
{
	int	i;

	data->height = map_height(file_name);
	data->width = map_width(file_name);
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	data->color_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	if (!data->z_matrix || !data->color_matrix)
		return ;
	i = 0;
	data->z_matrix[data->height] = NULL;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (data->width + 42));
		data->color_matrix[i] = (int *)ft_calloc((data->width + 1),
				sizeof(int) * 42);
		if (!data->z_matrix[i] || !data->color_matrix[i])
			return ;
		i++;
	}
}

/* reads fd and fills z_matrix and color_matrix in data.
also finds origin and z limits */
void	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	read_malloc(file_name, data);
	i = 0;
	fd = open(file_name, O_RDONLY, 0);
	while (i < data->height)
	{
		line = get_next_line(fd);
		fill_matrix(data->z_matrix[i], data->color_matrix[i], line);
		free(line);
		i++;
	}
	close(fd);
	data->z_matrix[i] = NULL;
	data->color_matrix[i] = NULL;
	z_lim(data);
	find_origin(data);
}
