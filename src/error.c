/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:32:40 by cgray             #+#    #+#             */
/*   Updated: 2024/02/02 14:08:51 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*Puts mlx error msg to terminal*/

void	ft_error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}
/*
Checks that fd has maps path and '.fdf' file extension
 */

int	filename_error(char *fd)
{
	size_t	filename_len;
	char	*filename;

	if (ft_strncmp(fd, "maps/", 5))
	{
		ft_printf("Missing maps path. ⛔🗺️\n");
		return (1);
	}
	filename = fd + 5;
	filename_len = ft_strlen(filename);
	if (filename_len < 4)
	{
		ft_printf("Filename too short to contain extension. 📉\n");
		return (1);
	}
	if (ft_strncmp(&filename[filename_len - 4], ".fdf", 4))
	{
		ft_printf("Filename has missing/incorrect extension. 🙈\n");
		return (1);
	}
	return (0);
}
