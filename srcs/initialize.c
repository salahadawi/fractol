/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:56:10 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:56:20 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	initialize_julia(t_mlx *mlx)
{
	mlx->zoom--;
	mlx->offsetx -= (-1400 + 50 - WIN_WIDTH * 0.75) / 10;
	mlx->offsety -= (200 - WIN_HEIGHT * 0.5) / 10;
	mlx->re1 *= 1.3;
	mlx->re2 *= 1.3;
	mlx->lm1 *= 1.3;
	mlx->lm2 *= 1.3;
	mlx->offsetx /= 1.3;
	mlx->offsety /= 1.3;
	if (!((int)mlx->zoom % 3))
		mlx->iter -= 1;
}

void	initialize_fractal(t_mlx *mlx)
{
	mlx->iter = 20;
	if (mlx->fractal == &julia)
		mlx->iter = 50;
	mlx->offsetx = 0;
	mlx->offsety = 0;
	mlx->re1 = -2;
	mlx->re2 = 1;
	mlx->lm1 = -1;
	mlx->lm2 = 1;
	mlx->zoom = 0;
	mlx->idlezoom = 0;
	mlx->multi = 1;
	mlx->palette = 0;
	mlx->drawgui = 1;
	mlx->maxzoom = 159;
	if (mlx->fractal == &mandelbrot)
		mlx->maxzoom = 163;
	mlx->lockmouse = 0;
	if (mlx->fractal == &julia)
		initialize_julia(mlx);
}

void	initialize_mlx(t_mlx *mlx, char *name)
{
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, WIN_WIDTH, WIN_HEIGHT, name);
	mlx->image_ptr = mlx_new_image(mlx->init, WIN_WIDTH, WIN_HEIGHT);
	mlx->image = mlx_get_data_addr(mlx->image_ptr, &(mlx->bpp),
	&(mlx->size_line), &(mlx->endian));
	mlx->mouse1 = 0;
	mlx->mouse2 = 0;
	initialize_fractal(mlx);
}
