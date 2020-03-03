/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_julia_mouse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:58:55 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:59:04 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	handle_julia_mouse(long double *x, long double *y, t_mlx *mlx)
{
	if (!mlx->lockmouse)
	{
		*x = (mlx->mousex - WIN_WIDTH / 2) * 0.003;
		*y = (mlx->mousey - WIN_HEIGHT / 2) * 0.003;
		mlx->xyold[0] = *x;
		mlx->xyold[1] = *y;
	}
	else
	{
		*x = mlx->xyold[0];
		*y = mlx->xyold[1];
	}
}
