/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:50:35 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 15:59:31 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
