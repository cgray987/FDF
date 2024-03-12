/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:28:07 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 17:33:49 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//counts number of rows in map
int	map_height(char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (height);
}

//counts number of columns in map (assumes map size is rectangular)
int	map_width(char *file_name)
{
	char	*line;
	int		fd;
	int		width;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	width = ft_count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

//fills z_matrix and color matrix from map data
void	fill_matrix(int *z_matrix_line, int *color_mat_line,
			char *line)
{
	char	**matrix;
	int		i;
	char	**element;

	i = 0;
	matrix = ft_split(line, ' ');
	while (matrix[i])
	{
		element = ft_split(matrix[i], ',');
		if (element[1])
		{
			color_mat_line[i] = color_from_str(element[1]);
			free(element[1]);
		}
		z_matrix_line[i] = ft_atoi(matrix[i]);
		free(matrix[i]);
		free(element[0]);
		free(element);
		i++;
	}
	free(matrix);
}
