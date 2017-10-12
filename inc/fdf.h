/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 19:02:14 by magouin           #+#    #+#             */
/*   Updated: 2016/10/18 11:42:38 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <get_next_line.h>
# include <libft.h>
# define WIN_WIDTH 1200
# define WIN_HEIGHT 900
# define PI 3.141592653589793
# define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))
# define MAX(x1, x2) ((x1) > (x2) ? (x1) : (x2))

typedef struct		s_points
{
	double			x;
	double			y;
	double			z;
	int				py;
	int				px;
	int				color;
}					t_points;

typedef struct		s_cam
{
	double			theta;
	double			x;
	double			y;
	double			z;
	double			ray;
	double			fov;
}					t_cam;

typedef struct		s_img
{
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
}					t_img;

typedef struct		s_env
{
	void			*win;
	int				xmax;
	int				flag;
	int				ymax;
	int				wid_map;
	int				hei_map;
	double			x;
	int				y;
	void			*mlx;
	void			*image;
	void			*img_map;
	void			*weapon;
	char			*str_weapon;
	int				**map;
	int				endian;
	char			*str_image;
	char			*map_image;
	int				size_line;
	int				bits_per_pixel;
	t_cam			*cam;
}					t_env;

void				print_shot(t_env *e);
void				print_weapon(t_env *e, int nb);
int					print_column(t_env *e, double *h, double angle, int x);
void				draw_line(t_points p1, t_points p2, t_env *e);
void				aa_pixel_put(t_env *e, int x, int y);
void				quadrant1(t_points p1, t_points p2, t_env *e);
void				quadrant2(t_points p1, t_points p2, t_env *e);
void				quadrant3(t_points p1, t_points p2, t_env *e);
void				quadrant4(t_points p1, t_points p2, t_env *e);
void				move_top(t_env *e);
void				move_bot(t_env *e);
void				get_colors(int x, int y, char **xmp, int *co);
void				move_right(t_env *e);
void				move_left(t_env *e);
void				put_picture(t_env *e);
void				parsing(char *fichier, t_env *e);
int					expose_hook(t_env *e);
void				init_env(t_env *e, int i);
void				mandelbrot4(t_env *e, int dim[2], double z[2], int i);
void				mandelbrot2(t_env *e, double *rp);
void				couleur(t_env *e);
void				mandelbrot(t_env *e);
void				modulo(t_env *e);
void				julia(t_env *e);
void				zoom(int keycode, t_env *e);
void				rotate_up_left(int keycode, t_env *e);
void				rotate_down_right(int keycode, t_env *e);
void				move_plus(int keycode, t_env *e);
void				move_minus(int keycode, t_env *e);
#endif
