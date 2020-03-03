/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_idle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:52:05 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:54:21 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		handle_idle(t_mlx *mlx)
{
	if (mlx->mouse2 && mlx->zoom < mlx->maxzoom)
	{
		mlx->zoom += 0.2;
		mlx->idlezoom++;
		mlx->offsetx += (mlx->mousex - WIN_WIDTH / 5 - WIN_WIDTH / 2) / 50;
		mlx->offsety += (mlx->mousey - WIN_HEIGHT / 2) / 50;
		mlx->mouse2 = 1;
		mlx->re1 /= 1.02;
		mlx->re2 /= 1.02;
		mlx->lm1 /= 1.02;
		mlx->lm2 /= 1.02;
		mlx->offsetx *= 1.02;
		mlx->offsety *= 1.02;
		if (!(mlx->idlezoom % 15) && mlx->zoom < 160)
			mlx->iter += 1;
		handle_drawing(mlx);
	}
	return (0);
}
