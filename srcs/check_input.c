/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:57:27 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:57:35 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
