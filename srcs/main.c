/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:50:35 by sadawi            #+#    #+#             */
/*   Updated: 2020/02/26 14:00:11 by sadawi           ###   ########.fr       */
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
	handle_drawing(mlx);
	return (0);
}

int		mouse_press(int key, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if (key == 1)
	{
		mlx->mouse1 = 1;
		mlx->mousex = x;
		mlx->mousey = y;
	}
	if (key == 2)
		mlx->mouse2 = 1;
	if (key == 4)
		mlx->zoom -= 0.1;
	if (key == 5)
		mlx->zoom += 0.1;
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

void	handle_mouse1_move(int x, int y, t_mlx *mlx)
{
	if (x != mlx->mousex)
		mlx->offsetx -= x - mlx->mousex;
	if (y != mlx->mousey)
		mlx->offsety -= y - mlx->mousey;
}

int		mouse_move(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if (mlx->mouse1)
	{
		handle_mouse1_move(x, y, mlx);
		handle_drawing(mlx);
	}
	// if (mlx->mouse2)
	// 	handle_mouse2_move(x, y, mlx);
	mlx->mousex = x;
	mlx->mousey = y;
	return (0);
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

double	scale(double oldmin, double oldmax, double newmin, double newmax)
{
	double slope;

	slope = 1.0 * (newmax - newmin) / (oldmax - oldmin);
	return (slope);
}

// int	burning_ship(int x, int y, t_mlx *mlx)
// {
// 	double xy_scaled[2];
// 	double *xy;
// 	int *i;
// 	double xtmp;

// 	x -= WIN_WIDTH / 3 * 2;
// 	y -= WIN_HEIGHT / 2;
// 	xy_scaled[0] = scale(x, 0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
// 	xy_scaled[1] = scale(y, 0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
// 	xy = (double[2]){0., 0.};
// 	i = (int[2]){0, mlx->iter};
// 	while (xy[0] * xy[0] + xy[1] * xy[1] <= 2 * 2 && i[0] < i[1])
// 	{
// 		if (xy[0] < 0)
// 			xy[0] *= -1;
// 		if (xy[1] < 0)
// 			xy[1] *= -1;
// 		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + xy_scaled[0];
// 		xy[1] = 2 * xy[0] * xy[1] + xy_scaled[1];
// 		xy[0] = xtmp;
// 		i[0]++;
// 	}
// 	if (i[0] == mlx->iter)
// 		return (0);
// 	else
// 		return (0x00F0F * i[0]);
// }

int	mandelbrot(int x, int y, t_mlx *mlx, double slope[2])
{
	double xy_scaled[2];
	double *xy;
	int *i;
	double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	xy_scaled[0] = -2 * mlx->zoom + slope[0] * x;
	xy_scaled[1] = -1 * mlx->zoom + slope[1] * y;
	xy = (double[2]){0., 0.};
	i = (int[2]){0, mlx->iter};
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 4 && i[0] < i[1])
	{
		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + xy_scaled[0];
		xy[1] = 2 * xy[0] * xy[1] + xy_scaled[1];
		xy[0] = xtmp;
		i[0]++;
	}
	if (i[0] == mlx->iter)
		return (0);
	else
		return (0x00B0B * i[0]);
}

void	*draw_fractal(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 0;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal1(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 1;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal2(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 2;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal3(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 3;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal4(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 4;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal5(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 5;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal6(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 6;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	*draw_fractal7(void *param)
{
	t_mlx *mlx;
	int color;
	int xy[2];
	double slope[2];

	mlx = param;
	xy[1] = 0;
	slope[0] = scale(0, WIN_WIDTH, -2 * mlx->zoom, 1 * mlx->zoom);
	slope[1] = scale(0, WIN_HEIGHT, -1 * mlx->zoom, 1 * mlx->zoom);
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 7;
		while (xy[0] < WIN_WIDTH)
		{
			color = mandelbrot(xy[0], xy[1], mlx, slope);
			draw_pixel(xy[0], xy[1], color, mlx);
			xy[0] += THREADS;
		}
		xy[1]++;
	}
	return (NULL);
}

void	handle_drawing(t_mlx *mlx)
{
	pthread_t thread_id[THREADS];
	int i;
	int ret;

	i = 0;
	while (i < THREADS)
	{
		mlx->thread = i;
		if (i == 0)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal, mlx);
		else if (i == 1)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal1, mlx);
		else if (i == 2)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal2, mlx);
		else if (i == 3)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal3, mlx);
		else if (i == 4)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal4, mlx);
		else if (i == 5)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal5, mlx);
		else if (i == 6)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal6, mlx);
		else if (i == 7)
			ret = pthread_create(&thread_id[i], NULL, draw_fractal7, mlx);
		if (ret)
			ft_printf("Error: Thread %d\n", i);
			i++;
	}
	//draw_fractal(mlx);
	i = 0;
	while (i < THREADS)
	 	pthread_join(thread_id[i++], NULL);
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image_ptr, 0, 0);
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
	mlx->zoom = 1;
	mlx->iter = 10;
	mlx->offsetx = 0;
	mlx->offsety = 0;
}

void	handle_graphics(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, check_key, (void*)mlx);
	mlx_hook(mlx->window, 4, 0, mouse_press, (void*)mlx);
	mlx_hook(mlx->window, 5, 0, mouse_release, (void*)mlx);
	mlx_hook(mlx->window, 6, 0, mouse_move, (void*)mlx);
	//mlx_hook(mlx->window, 12, 0, handle_idle, (void*)mlx);
	//mlx_loop_hook(mlx->init, handle_idle, (void*)mlx);
	handle_drawing(mlx);
	mlx_loop(mlx->init);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		handle_error(3);
	initialize_mlx(mlx, argv[1]);
	if (argc != 2)
		handle_error(1);
	handle_graphics(mlx);
	return (0);
}

//multithreading might work by not letting threads exit
//zoom always zooms in fractal center
//how many threads is optimal?
