/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:55:02 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 17:30:45 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_controls_terminal(void)
{
	ft_printf("\t🔲CONTROLS🔲\n");
	ft_printf("Translate:\t\tWASD\n");
	ft_printf("Zoom:\t\t\tMousewheel\n");
	ft_printf("Colors:\t\t\tZ, X, C, V\n");
	ft_printf("\t\t\t🌵 🔥 🧊 🌸\n");
	ft_printf("Raise/Lower Height:\t-/+\n");
	ft_printf("Projections: \n\tISOMETRIC:\t1\n");
	ft_printf("\tPARALLEL:\t2\n");
	ft_printf("\tFRONT VIEW:\t3\n");
	ft_printf("\tTOP VIEW:\t4\n");
	ft_printf("\tSIDE VIEW:\t5\n");
	ft_printf("Rotations:\t\t(NUMPAD KEYS)\n");
	ft_printf("\t\t\t(-)\t(+)\n");
	ft_printf("\tX-AXIS:\t\t5\t8\n");
	ft_printf("\tY-AXIS:\t\t4\t6\n");
	ft_printf("\tZ-AXIS:\t\t7\t9\n");
}

/* frees t_fdf data
	-z_matrix and color_matrix malloc'd in read_malloc
	-printf("Freeing color_matrix[%d] = %p\n", i,data->color_matrix[i]);
 */
void	free_fdf(t_fdf *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->z_matrix[i]);
		free((void *)data->color_matrix[i]);
		i++;
	}
	free(data->z_matrix);
	free(data->color_matrix);
	free(data);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc == 2)
	{
		if (filename_error(argv[1]) == 1)
			return (1);
		show_controls_terminal();
		data = (t_fdf *)malloc(sizeof(t_fdf));
		read_file(argv[1], data);
		init_fdf(data, argv[1]);
		draw(data);
		mlx_scroll_hook(data->mlx_ptr, (void *)zoom_scroll_hook, (void *)data);
		mlx_key_hook(data->mlx_ptr, (void *)key_hook_fdf, (void *)data);
		mlx_loop(data->mlx_ptr);
		mlx_terminate(data->mlx_ptr);
		free_fdf(data);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_printf("Not enough arguments.\n");
		return (EXIT_FAILURE);
	}
}
/* print map
	int i;
	int j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			printf("%3d", data->z_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	} */
