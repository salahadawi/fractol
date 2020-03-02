/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:11:13 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/02 13:12:09 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	handle_error(int code)
{
	if (!code)
		ft_printf("Error\n");
	if (code == 1)
		ft_printf("Usage: ./fractol [name of fractal]\n\nAvailable fractals are");
		ft_printf(":\n\nmandelbrot\nburning_ship\njulia\ntricorn\nmultibrot\n");
	if (code == 2)
		ft_printf("Error: Malloc failed\n");
	exit(0);
}
