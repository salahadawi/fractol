/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:48:02 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:48:20 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	handle_mousewheelup(t_mlx *mlx, int x, int y)
{
	if (mlx->zoom < mlx->maxzoom)
	{
		mlx->zoom++;
		mlx->offsetx += (x + 50 - WIN_WIDTH * 0.75) / 10;
		mlx->offsety += (y - WIN_HEIGHT * 0.5) / 10;
		mlx->re1 /= 1.1;
		mlx->re2 /= 1.1;
		mlx->lm1 /= 1.1;
		mlx->lm2 /= 1.1;
		mlx->offsetx *= 1.1;
		mlx->offsety *= 1.1;
		if (!((int)mlx->zoom % 3))
			mlx->iter += 1;
	}
}

void	handle_mousewheeldown(t_mlx *mlx, int x, int y)
{
	mlx->zoom--;
	mlx->offsetx -= (x + 50 - WIN_WIDTH * 0.75) / 10;
	mlx->offsety -= (y - WIN_HEIGHT * 0.5) / 10;
	mlx->re1 *= 1.1;
	mlx->re2 *= 1.1;
	mlx->lm1 *= 1.1;
	mlx->lm2 *= 1.1;
	mlx->offsetx /= 1.1;
	mlx->offsety /= 1.1;
	if (!((int)mlx->zoom % 3))
		mlx->iter -= 1;
}

int		mouse_press(int key, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if (key == 1)
		mlx->mouse1 = 1;
	if (key == 2 && mlx->zoom < mlx->maxzoom)
	{
		mlx->zoom += 0.1;
		mlx->mouse2 = 1;
		mlx->re1 /= 1.01;
		mlx->re2 /= 1.01;
		mlx->lm1 /= 1.01;
		mlx->lm2 /= 1.01;
		mlx->offsetx *= 1.01;
		mlx->offsety *= 1.01;
	}
	if (key == 4)
		handle_mousewheeldown(mlx, x, y);
	if (key == 5)
		handle_mousewheelup(mlx, x, y);
	mlx->mousex = x;
	mlx->mousey = y;
	handle_drawing(mlx);
	return (0);
}

int		mouse_release(int key, int x, int y, void *param)
{
	t_mlx *mlx;

	(void)x;
	(void)y;
	mlx = param;
	if (key == 1)
		mlx->mouse1 = 0;
	if (key == 2)
		mlx->mouse2 = 0;
	handle_drawing(mlx);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if (mlx->mouse1)
	{
		if (x != mlx->mousex)
			mlx->offsetx -= x - mlx->mousex;
		if (y != mlx->mousey)
			mlx->offsety -= y - mlx->mousey;
		handle_drawing(mlx);
	}
	mlx->mousex = x;
	mlx->mousey = y;
	if (mlx->fractal == &julia)
	{
		if (mlx->mouse2)
			handle_idle(mlx);
		else
			handle_drawing(mlx);
	}
	return (0);
}
