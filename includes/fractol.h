/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:41:33 by sadawi            #+#    #+#             */
/*   Updated: 2020/03/03 16:13:01 by sadawi           ###   ########.fr       */
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

# define WIN_HEIGHT	333 * 2
# define WIN_WIDTH	500 * 2
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
	int				iter;
	long double		offsetx;
	long double		offsety;
	long double		re1;
	long double		re2;
	long double		lm1;
	long double		lm2;
	double			zoom;
	double			maxzoom;
	int				(*fractal)(int, int, struct s_mlx*);
	int				palette;
	int				idlezoom;
	int				drawgui;
	double			multi;
	int				lockmouse;
	long double		xyold[2];

}					t_mlx;

typedef	struct		s_thread
{
	int				thread;
	t_mlx			*mlx;

}					t_thread;

void				handle_error(int code);
int					handle_idle(t_mlx *mlx);
void				handle_reset(t_mlx *mlx);
void				handle_multi(t_mlx *mlx, int key);
void				handle_palette(t_mlx *mlx, int key);
int					check_key(int key, void *param);
void				handle_mousewheelup(t_mlx *mlx, int x, int y);
void				handle_mousewheeldown(t_mlx *mlx, int x, int y);
int					mouse_press(int key, int x, int y, void *param);
int					mouse_release(int key, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);
int					rgb(int r, int g, int b);
void				draw_pixel(int x, int y, int color, t_mlx *mlx);
long double			scale(int n, long double old[2], long double new[2]);
int					palette1(int i, t_mlx *mlx);
int					palette2(int i, t_mlx *mlx);
int					palette3(int i, t_mlx *mlx, int x, int y);
int					palette4(int i, t_mlx *mlx, int x, int y);
int					palette(int i, t_mlx *mlx, int x, int y);
int					burning_ship(int x, int y, t_mlx *mlx);
int					multibrot(int x, int y, t_mlx *mlx);
int					tricorn(int x, int y, t_mlx *mlx);
int					mandelbrot(int x, int y, t_mlx *mlx);
void				handle_julia_mouse(long double *x, long double *y,
						t_mlx *mlx);
int					julia(int x, int y, t_mlx *mlx);
void				*draw_fractal(void *param);
void				mlxstr(t_mlx *mlx, int x, int y, char *str);
void				handle_gui(t_mlx *mlx);
void				create_threads(t_mlx *mlx);
void				handle_drawing(t_mlx *mlx);
void				initialize_julia(t_mlx *mlx);
void				initialize_fractal(t_mlx *mlx);
void				initialize_mlx(t_mlx *mlx, char *name);
void				handle_graphics(t_mlx *mlx);
int					handle_fractal(t_mlx *mlx, char *name);

#endif
