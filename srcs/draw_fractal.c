/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:55:02 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:55:38 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*draw_fractal(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = ((t_thread*)param)->mlx;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = ((t_thread*)param)->thread;
		while (xy[0] < WIN_WIDTH)
		{
			color = mlx->fractal(xy[0], xy[1], mlx);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	handle_drawing(t_mlx *mlx)
{
	create_threads(mlx);
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image_ptr, 0, 0);
	if (mlx->drawgui)
		handle_gui(mlx);
}

void	handle_graphics(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, check_key, (void*)mlx);
	mlx_hook(mlx->window, 4, 0, mouse_press, (void*)mlx);
	mlx_hook(mlx->window, 5, 0, mouse_release, (void*)mlx);
	mlx_hook(mlx->window, 6, 0, mouse_move, (void*)mlx);
	mlx_loop_hook(mlx->init, handle_idle, (void*)mlx);
	handle_drawing(mlx);
	mlx_loop(mlx->init);
}

void	draw_pixel(int x, int y, int color, t_mlx *mlx)
{
	int r;
	int g;
	int b;

	if (x <= 0 || y <= 0 || WIN_WIDTH <= x || WIN_HEIGHT <= y)
		return ;
	r = color % 256;
	g = color / 256 % 256;
	b = color / 256 / 256 % 256;
	mlx->image[x * 4 + y * mlx->size_line] = r;
	mlx->image[x * 4 + y * mlx->size_line + 1] = g;
	mlx->image[x * 4 + y * mlx->size_line + 2] = b;
}

int		rgb(int r, int g, int b)
{
	int n;

	n = r * 256 * 256;
	n += g * 256;
	n += b;
	return (n);
}
