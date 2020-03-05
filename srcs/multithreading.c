/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:58:21 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/05 13:00:05 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	create_threads(t_mlx *mlx)
{
	pthread_t	thread_id[THREADS];
	t_thread	thread_arr[THREADS];
	int			i;
	int			ret;

	i = 0;
	while (i < THREADS)
	{
		thread_arr[i].mlx = mlx;
		thread_arr[i].thread = i;
		ret = pthread_create(&thread_id[i], NULL, draw_fractal, &thread_arr[i]);
		if (ret)
			handle_error(3);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread_id[i++], NULL);
}
