/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:45:53 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:46:01 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
	mlxstr(mlx, 20, 80, "Mouse1 - Drag to move");
	mlxstr(mlx, 20, 105, "Mouse2 - Hold to zoom");
	mlxstr(mlx, 20, 130, "Mouse wheel - Zoom in/out");
	mlxstr(mlx, 20, 155, "0 - Reset view");
	mlxstr(mlx, 20, 180, "4 / 6 - Change color");
	if (mlx->fractal == &multibrot)
		mlxstr(mlx, 20, 205, "7 / 9 - Change exponent");
	mlxstr(mlx, WIN_WIDTH - 240, 10, "Press 5 to toggle GUI");
}
