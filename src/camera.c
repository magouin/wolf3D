/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 14:20:45 by magouin           #+#    #+#             */
/*   Updated: 2016/10/28 17:53:40 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../img/barrel.XPM"
#include "../img/bluestone.XPM"
#include "../img/colorstone.XPM"
#include "../img/eagle.XPM"
#include "../img/greenlight.XPM"
#include "../img/greystone.XPM"
#include "../img/mossy.XPM"
#include "../img/pillar.XPM"
#include "../img/purplestone.XPM"
#include "../img/redbrick.XPM"
#include "../img/wood.XPM"
#include "../img/mblue1.XPM"
#include "../img/mblue2.XPM"
#include "../img/mblue3.XPM"
#include "../img/mblue4.XPM"
#include "../img/mblue5.XPM"
#include "../img/mblue6.XPM"
#include "../img/mblue7.XPM"
#include "../img/mblue8.XPM"
#include "../img/mblue9.XPM"
#include "../img/mblue10.XPM"
#include "../img/mblue11.XPM"
#include "../img/mblue12.XPM"
#include "../img/mblue13.XPM"

void			get_color(int x, int y, char **xmp, int *co)
{
	int		color;
	char	c;
	int		count;
	int		mask;

	count = 1;
	mask = 256 * 256 * 16;
	y = ft_atoi(xmp[0] + 6) + y + 1;
	c = xmp[y][x];
	color = 0;
	while (c != xmp[count][0])
		count++;
	x = 5;
	while (++x < 12)
	{
		if (xmp[count][x] <= '9' && xmp[count][x] >= '0')
			color = color + (xmp[count][x] - '0') * mask;
		else if ((xmp[count][x] <= 'f' && xmp[count][x] >= 'a')
			|| (xmp[count][x] <= 'F' && xmp[count][x] >= 'A'))
			color = color + ((xmp[count][x] % 32) + 9) * mask;
		mask = mask >> 4;
	}
	co[2] = (color & 0xff0000) >> 16;
	co[1] = (color & 0xff00) >> 8;
	co[0] = color % 256;
}

void			init_map(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->wid_map)
	{
		y = -1;
		while (++y < e->hei_map)
		{
			if (e->map[(int)(((double)y / e->hei_map) * e->ymax)]
				[(int)(((double)x / e->wid_map) * e->xmax)] == 0)
			{
				e->map_image[x * 4 + 0 + y * e->wid_map * 4] = 0xa0;
				e->map_image[x * 4 + 1 + y * e->wid_map * 4] = 0xa0;
				e->map_image[x * 4 + 2 + y * e->wid_map * 4] = 0xa0;
				e->map_image[x * 4 + 3 + y * e->wid_map * 4] = 0xa0;
			}
			else
			{
				e->map_image[x * 4 + 0 + y * e->wid_map * 4] = 0;
				e->map_image[x * 4 + 1 + y * e->wid_map * 4] = 0;
				e->map_image[x * 4 + 2 + y * e->wid_map * 4] = 0;
			}
		}
	}
}

void			plein_de_if(t_env *e, int *y, int *x, double h)
{
	int				color[3];

	x[1] = ((*y - (WIN_HEIGHT - h) / 2) / h * 64);
	if ((*y > (WIN_HEIGHT - h) / 2)
		&& (*y < (WIN_HEIGHT - (WIN_HEIGHT - h) / 2)))
	{
		get_color(x[0], x[1], g_tab[x[3]], color);
		e->str_image[(x[2] - 1) * 4 + 0 + *y * e->size_line] = color[0];
		e->str_image[(x[2] - 1) * 4 + 1 + *y * e->size_line] = color[1];
		e->str_image[(x[2] - 1) * 4 + 2 + *y * e->size_line] = color[2];
	}
	else if (*y < (WIN_HEIGHT - h) / 2)
	{
		e->str_image[(x[2] - 1) * 4 + 0 + *y * e->size_line] = 0x10;
		e->str_image[(x[2] - 1) * 4 + 1 + *y * e->size_line] = 0x10;
		e->str_image[(x[2] - 1) * 4 + 2 + *y * e->size_line] = 0x10;
	}
	else
	{
		e->str_image[(x[2] - 1) * 4 + 0 + *y * e->size_line] = 0x80;
		e->str_image[(x[2] - 1) * 4 + 1 + *y * e->size_line] = 0x80;
		e->str_image[(x[2] - 1) * 4 + 2 + *y * e->size_line] = 0x80;
	}
	(*y)++;
}

void			print_weapon(t_env *e, int nb)
{
	int x;
	int y;
	int color[3];

	y = 0;
	while (y < WIN_HEIGHT / 3)
	{
		x = 0;
		while (x < WIN_WIDTH / 3)
		{
			get_colors((double)x / (WIN_WIDTH / 3) * 192,
				(double)y / (WIN_HEIGHT / 3) * 192, g_weapons[nb], color);
			if (color[0] == 0xff && color[1] == 0xff && color[2] == 0xff)
				e->str_weapon[x * 4 + 3 + y * (WIN_WIDTH / 3) * 4] = 0xff;
			else
			{
				e->str_weapon[x * 4 + 0 + y * (WIN_WIDTH / 3) * 4] = color[0];
				e->str_weapon[x * 4 + 1 + y * (WIN_WIDTH / 3) * 4] = color[1];
				e->str_weapon[x * 4 + 2 + y * (WIN_WIDTH / 3) * 4] = color[2];
				e->str_weapon[x * 4 + 3 + y * (WIN_WIDTH / 3) * 4] = 0;
			}
			x++;
		}
		y++;
	}
}

void			put_picture(t_env *e)
{
	int				y;
	double			angle;
	int				x[4];
	double			h;

	x[2] = 0;
	init_map(e);
	print_weapon(e, 0);
	while (++(x[2]) < WIN_WIDTH + 1)
	{
		y = 0;
		angle = e->cam->theta - (e->cam->fov / 2)
		+ ((double)x[2] / WIN_WIDTH) * (e->cam->fov);
		angle < 0 ? angle += 2 * M_PI : 0;
		angle >= 2 * M_PI ? angle -= 2 * M_PI : 0;
		x[3] = print_column(e, &h, angle, x[2]);
		h /= cos(angle - e->cam->theta) / 2;
		x[0] = (int)(e->x * 64);
		while (y < WIN_HEIGHT)
			plein_de_if(e, &y, x, h);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->image, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img_map, 100, 100);
	mlx_put_image_to_window(e->mlx, e->win, e->weapon,
		2 * WIN_WIDTH / 6, 2 * WIN_HEIGHT / 3);
}
