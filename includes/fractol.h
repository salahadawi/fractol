/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:41:33 by sadawi            #+#    #+#             */
/*   Updated: 2020/02/28 14:18:45 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# include <pthread.h>

# define WIN_HEIGHT	667
# define WIN_WIDTH	1000
# define THREADS 8

typedef	struct		s_mlx
{
	void			*init;
	void			*window;
	void			*image_ptr;
	char			*image;
	int				bpp;
	int				size_line;
	int				endian;
	int				mouse1;
	int				mouse2;
	int				mousex;
	int				mousey;
	int				redraw;
	int				iter;
	int				thread;
	long double		offsetx;
	long double		offsety;
	long double		re1;
	long double		re2;
	long double		lm1;
	long double		lm2;
	double			zoom;
	int				(*fractal)(int, int, struct s_mlx*);
	int				color;
	int				idlezoom;
	int				drawgui;
	double			multi;

}					t_mlx;

void	handle_error(int code);
void	handle_drawing(t_mlx *mlx);

#endif
