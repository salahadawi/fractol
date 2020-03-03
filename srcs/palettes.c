/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:45:06 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:45:22 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
