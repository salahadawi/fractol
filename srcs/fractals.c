/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:38:00 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:44:34 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
