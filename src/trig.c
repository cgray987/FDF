/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgray <cgray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:51:38 by cgray             #+#    #+#             */
/*   Updated: 2024/01/28 16:51:11 by cgray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* radians to degrees */
float	rad(float deg)
{
	return (deg * PI / 180);
}

/* degrees to radians */
float	deg(float rad)
{
	return (rad * (180 / PI));
}
