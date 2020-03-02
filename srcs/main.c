/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:50:35 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/02 20:00:33 by sadawi           ###   ########.fr       */
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

void	handle_reset(t_mlx *mlx)
{
	mlx->iter = 20;
	if (mlx->fractal == &julia)
		mlx->iter = 60;
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

int		rgb(int r, int g, int b)
{
	int n;

	n = r * 256 * 256;
	n += g * 256;
	n += b;
	return (n);
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

long double	scale(int n, long double old[2], long double new[2])
{
	long double result;

	result = (new[1] - new[0]) * (n - old[0]) / (old[1] - old[0]) + new[0];
	return (result);
}

int		palette1(int i, t_mlx *mlx)
{
	if (mlx->palette == 0)
	{
		if (i == mlx->iter)
			return (0);
		return (0x02090F * i);
	}
	if (mlx->palette == 1)
	{
		if (i == mlx->iter)
			return (0);
		return (0xFFFFFF);
	}
	if (mlx->palette == 2)
	{
		if (i == mlx->iter)
			return (0xFFFFFF * i);
		else if (i < mlx->iter * 0.3)
			return (0xffcccc);
		else if (i < mlx->iter * 0.7)
			return (0xff9999 * i);
		else
			return (0xFFFFFF * i);
	}
	return (0);
}

int		palette2(int i, t_mlx *mlx)
{
	if (mlx->palette == 3)
	{
		if (i < mlx->iter * 0.3)
			return (0xffff00 * i);
		else if (i < mlx->iter * 0.7)
			return (0xff9900 * i);
		else
			return (0xff3300 * i);
	}
	if (mlx->palette == 4)
	{
		if (i < mlx->iter * 0.2)
			return (0xff0000);
		else if (i < mlx->iter * 0.4)
			return (0xffff00 * i);
		else if (i < mlx->iter * 0.6)
			return (0xfff00 * i);
		else if (i < mlx->iter * 0.8)
			return (0xf0040ff * i);
		else
			return (rgb(i * 3, i * 6, i * 9));
	}
	return (0);
}

int		palette3(int i, t_mlx *mlx, int x, int y)
{
	if (mlx->palette == 5)
	{
		if (i < mlx->iter * 0.2)
			return (0x660000 * x * y);
		else if (i < mlx->iter * 0.4)
			return (0xff0000 * x);
		else if (i < mlx->iter * 0.6)
			return (0xaa0000 * y);
		else if (i < mlx->iter * 0.8)
			return (0x330000 * x * y);
		else
			return (0x330000);
	}
	if (mlx->palette == 6)
	{
		if (i == mlx->iter)
			return (0);
		return (0x0F0F0F * y);
	}
	return (0);
}

int		palette4(int i, t_mlx *mlx, int x, int y)
{
	if (mlx->palette == 7)
	{
		if (i == mlx->iter)
			return (0);
		return (0xFF * x * y * (mlx->zoom - 150));
	}
	return (0);
}

int		palette(int i, t_mlx *mlx, int x, int y)
{
	if (0 <= mlx->palette && mlx->palette <= 2)
		return (palette1(i, mlx));
	if (3 <= mlx->palette && mlx->palette <= 4)
		return (palette2(i, mlx));
	if (5 <= mlx->palette && mlx->palette <= 6)
		return (palette3(i, mlx, x, y));
	if (7 <= mlx->palette && mlx->palette <= 7)
		return (palette4(i, mlx, x, y));
	return (0);
}

int		burning_ship(int x, int y, t_mlx *mlx)
{
	long double xy_scaled[2];
	long double *xy;
	int			*i;
	long double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	xy_scaled[0] = scale(x, (long double[2]){0, WIN_WIDTH},
		(long double[2]){mlx->re1, mlx->re2});
	xy_scaled[1] = scale(y, (long double[2]){0, WIN_HEIGHT},
		(long double[2]){mlx->lm1, mlx->lm2});
	xy = (long double[2]){0., 0.};
	i = (int[2]){0, mlx->iter};
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 2 * 2 && i[0] < i[1])
	{
		if (xy[0] < 0)
			xy[0] *= -1;
		if (xy[1] < 0)
			xy[1] *= -1;
		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + xy_scaled[0];
		xy[1] = 2 * xy[0] * xy[1] + xy_scaled[1];
		xy[0] = xtmp;
		i[0]++;
	}
	return (palette(i[0], mlx, xy[0], xy[1]));
}

int		multibrot(int x, int y, t_mlx *mlx)
{
	long double xy_scaled[2];
	long double *xy;
	int			*i;
	long double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	xy_scaled[0] = scale(x, (long double[2]){0, WIN_WIDTH},
		(long double[2]){mlx->re1, mlx->re2});
	xy_scaled[1] = scale(y, (long double[2]){0, WIN_HEIGHT},
		(long double[2]){mlx->lm1, mlx->lm2});
	xy = (long double[2]){0., 0.};
	i = (int[2]){0, mlx->iter};
	xtmp = 0;
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 4 && i[0] < i[1])
	{
		xtmp = pow((xy[0] * xy[0] + xy[1] * xy[1]), (mlx->multi / 2.))
			* cos(mlx->multi * atan2(xy[1], xy[0])) + xy_scaled[0];
		xy[1] = pow((xy[0] * xy[0] + xy[1] * xy[1]), (mlx->multi / 2.))
			* sin(mlx->multi * atan2(xy[1], xy[0])) + xy_scaled[1];
		xy[0] = xtmp;
		i[0]++;
	}
	return (palette(i[0], mlx, xy[0], xy[1]));
}

int		tricorn(int x, int y, t_mlx *mlx)
{
	long double xy_scaled[2];
	long double *xy;
	int			*i;
	long double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	xy_scaled[0] = scale(x, (long double[2]){0, WIN_WIDTH},
		(long double[2]){mlx->re1, mlx->re2});
	xy_scaled[1] = scale(y, (long double[2]){0, WIN_HEIGHT},
		(long double[2]){mlx->lm1, mlx->lm2});
	xy = (long double[2]){xy_scaled[0], xy_scaled[1]};
	i = (int[2]){0, mlx->iter};
	xtmp = 0;
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 4 && i[0] < i[1])
	{
		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + xy_scaled[0];
		xy[1] = -2 * xy[0] * xy[1] + xy_scaled[1];
		xy[0] = xtmp;
		i[0]++;
	}
	return (palette(i[0], mlx, xy[0], xy[1]));
}

int		mandelbrot(int x, int y, t_mlx *mlx)
{
	long double xy_scaled[2];
	long double *xy;
	int			*i;
	long double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	xy_scaled[0] = scale(x, (long double[2]){0, WIN_WIDTH},
		(long double[2]){mlx->re1, mlx->re2});
	xy_scaled[1] = scale(y, (long double[2]){0, WIN_HEIGHT},
		(long double[2]){mlx->lm1, mlx->lm2});
	xy = (long double[2]){0., 0.};
	i = (int[2]){0, mlx->iter};
	xtmp = 0;
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 4 && i[0] < i[1])
	{
		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + xy_scaled[0];
		xy[1] = 2 * xy[0] * xy[1] + xy_scaled[1];
		xy[0] = xtmp;
		i[0]++;
	}
	return (palette(i[0], mlx, xy[0], xy[1]));
}

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

int		julia(int x, int y, t_mlx *mlx)
{
	long double x_scaled;
	long double y_scaled;
	long double *xy;
	int			*i;
	long double xtmp;

	x += mlx->offsetx;
	y += mlx->offsety;
	handle_julia_mouse(&x_scaled, &y_scaled, mlx);
	xy = (long double[2]){scale(x, (long double[2]){0, WIN_WIDTH},
		(long double[2]){mlx->re1, mlx->re2}),
			scale(y, (long double[2]){0, WIN_HEIGHT},
				(long double[2]){mlx->lm1, mlx->lm2})};
	i = (int[2]){0, mlx->iter};
	xtmp = 0;
	while (xy[0] * xy[0] + xy[1] * xy[1] <= 4 && i[0] < i[1])
	{
		xtmp = xy[0] * xy[0] - xy[1] * xy[1] + x_scaled;
		xy[1] = 2 * xy[0] * xy[1] + y_scaled;
		xy[0] = xtmp;
		i[0]++;
	}
	return (palette(i[0], mlx, xy[0], xy[1]));
}

void	*draw_fractal(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 0;
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

void	*draw_fractal1(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 1;
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

void	*draw_fractal2(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 2;
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

void	*draw_fractal3(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 3;
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

void	*draw_fractal4(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 4;
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

void	*draw_fractal5(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 5;
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

void	*draw_fractal6(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 6;
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

void	*draw_fractal7(void *param)
{
	t_mlx	*mlx;
	int		color;
	int		xy[2];

	mlx = param;
	xy[1] = 0;
	while (xy[1] < WIN_HEIGHT)
	{
		xy[0] = 7;
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

void	mlxstr(t_mlx *mlx, int x, int y, char *str)
{
	mlx_string_put(mlx->init, mlx->window, x, y, 0xFFFFFF, str);
}

void	handle_gui(t_mlx *mlx)
{
	char *str;

	mlxstr(mlx, 20, 30, "Zoom:");
	mlxstr(mlx, 20, 55, "Iterations:");
	str = ft_itoa(mlx->zoom / (mlx->maxzoom / 100));
	str = ft_strjoinfree(str, ft_strdup("%"));
	mlxstr(mlx, 80, 30, str);
	free(str);
	str = ft_itoa(mlx->iter);
	mlxstr(mlx, 140, 55, str);
	free(str);
}

void	create_threads(t_mlx *mlx)
{
	pthread_t	thread_id[THREADS];
	void		*(*draw[8])(void*);
	int			i;
	int			ret;

	i = 0;
	draw[0] = draw_fractal;
	draw[1] = draw_fractal1;
	draw[2] = draw_fractal2;
	draw[3] = draw_fractal3;
	draw[4] = draw_fractal4;
	draw[5] = draw_fractal5;
	draw[6] = draw_fractal6;
	draw[7] = draw_fractal7;
	while (i < THREADS)
	{
		ret = pthread_create(&thread_id[i], NULL, draw[i], mlx);
		if (ret)
			handle_error(3);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread_id[i++], NULL);
}

void	handle_drawing(t_mlx *mlx)
{
	create_threads(mlx);
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image_ptr, 0, 0);
	if (mlx->drawgui)
		handle_gui(mlx);
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
	mlx->iter = 20;
	if (mlx->fractal == &julia)
		mlx->iter = 60;
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

int		handle_fractal(t_mlx *mlx, char *name)
{
	if (ft_strequ(name, "mandelbrot"))
		mlx->fractal = &mandelbrot;
	else if (ft_strequ(name, "burning_ship"))
		mlx->fractal = &burning_ship;
	else if (ft_strequ(name, "multibrot"))
		mlx->fractal = &multibrot;
	else if (ft_strequ(name, "tricorn"))
		mlx->fractal = &tricorn;
	else if (ft_strequ(name, "julia"))
		mlx->fractal = &julia;
	else
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		handle_error(2);
	if (argc != 2)
		handle_error(1);
	if (handle_fractal(mlx, argv[1]))
		handle_error(1);
	initialize_mlx(mlx, argv[1]);
	handle_graphics(mlx);
	return (0);
}
