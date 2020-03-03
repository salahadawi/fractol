/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:48:56 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:49:19 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		check_key(int key, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if (key == 53)
		exit(0);
	if (key == 126)
		mlx->iter += 1;
	if (key == 125)
		mlx->iter -= 1;
	if (key == 92 || key == 89)
		handle_multi(mlx, key);
	if (key == 86 || key == 88)
		handle_palette(mlx, key);
	if (key == 82)
		handle_reset(mlx);
	if (key == 87)
		mlx->drawgui = !(mlx->drawgui);
	if (key == 91)
		mlx->lockmouse = !(mlx->lockmouse);
	handle_drawing(mlx);
	return (0);
}

void	handle_reset(t_mlx *mlx)
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
	mlx->lockmouse = 0;
	if (mlx->fractal == &julia)
		initialize_julia(mlx);
}

void	handle_multi(t_mlx *mlx, int key)
{
	if (key == 92)
	{
		if (mlx->multi < 3)
			mlx->multi += 0.05;
		else if (mlx->multi < 4)
			mlx->multi += 0.1;
		else if (mlx->multi < 5)
			mlx->multi += 0.2;
		else
			mlx->multi += 0.4;
	}
	else if (key == 89)
	{
		if (mlx->multi < 3)
			mlx->multi -= 0.05;
		else if (mlx->multi < 4)
			mlx->multi -= 0.1;
		else if (mlx->multi < 5)
			mlx->multi -= 0.2;
		else
			mlx->multi -= 0.4;
	}
}

void	handle_palette(t_mlx *mlx, int key)
{
	if (key == 86 && 0 < mlx->palette)
		mlx->palette--;
	else if (key == 88 && mlx->palette < 7)
		mlx->palette++;
}
