/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 19:02:55 by magouin           #+#    #+#             */
/*   Updated: 2016/10/28 19:03:40 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void			print_column2(t_env *e, double *x2, double *y2, double angle)
{
	double		xa;

	xa = tan(-1 * angle);
	if (angle < M_PI / 2 || angle > 3 * M_PI / 2)
	{
		x2[0] = e->cam->x + (1 - (e->cam->x - (int)e->cam->x) - 1);
		y2[0] = e->cam->y + (x2[0] + 1 - e->cam->x) * tan(-1 * angle);
		while (++x2[0] < e->xmax && x2[0] >= 1 && y2[0] < e->ymax && y2[0] >= 0
			&& (e->map[(int)y2[0]][(int)x2[0]] == 0
				&& e->map[(int)y2[0]][(int)x2[0] - 1] == 0))
			y2[0] += xa;
	}
	else
	{
		xa = tan(angle);
		x2[0] = e->cam->x - (e->cam->x - (int)e->cam->x) + 1;
		y2[0] = e->cam->y - (e->cam->x - (int)e->cam->x) * tan(-1 * angle);
		while (--x2[0] < e->xmax && x2[0] >= 1 && y2[0] >= 0
			&& (y2[0] < e->ymax && e->map[(int)y2[0]][(int)x2[0]] == 0
				&& e->map[(int)y2[0]][(int)x2[0] - 1] == 0))
			y2[0] += xa;
	}
}

void			print_column3(t_env *e, double *x2, double *y2, double angle)
{
	double		xa;

	xa = 1 / tan(angle);
	if (angle < M_PI)
	{
		y2[1] = e->cam->y - (e->cam->y - (int)e->cam->y) + 1;
		x2[1] = e->cam->x + (e->cam->y - (int)e->cam->y) / tan(angle);
		while (--y2[1] < e->ymax && x2[1] < e->xmax && x2[1] >= 0 && y2[1] >= 1
			&& (e->map[(int)y2[1]][(int)x2[1]] == 0
				&& e->map[(int)y2[1] - 1][(int)x2[1]] == 0))
			x2[1] += xa;
	}
	else
	{
		y2[1] = e->cam->y + (1 - (e->cam->y - (int)e->cam->y) - 1);
		x2[1] = e->cam->x + (y2[1] - e->cam->y + 1) * tan(angle - M_PI / 2);
		while (++y2[1] < e->ymax && x2[1] < e->xmax && x2[1] >= 0 && y2[1] >= 1
			&& (e->map[(int)y2[1]][(int)x2[1]] == 0
				&& e->map[(int)y2[1] - 1][(int)x2[1]] == 0))
			x2[1] -= xa;
	}
}

double			block(t_env *e, double *x2, double *y2, int *block_number)
{
	if (*x2 < e->xmax && *x2 >= 1 && y2[0] < e->ymax && *y2 >= 0)
	{
		e->map[(int)*y2][(int)*x2 - 1] ?
			*block_number = e->map[(int)*y2][(int)*x2 - 1] : 0;
		e->map[(int)*y2][(int)*x2] ?
			*block_number = e->map[(int)*y2][(int)*x2] : 0;
	}
	return (sqrt((*x2 - e->cam->x) * (*x2 - e->cam->x) +
		(*y2 - e->cam->y) * (*y2 - e->cam->y)));
}

double			block2(t_env *e, double *x2, double *y2, int *block_number)
{
	if (*x2 < e->xmax && *x2 >= 0 && *y2 < e->ymax && *y2 >= 1)
	{
		e->map[(int)*y2][(int)*x2] ?
			*block_number = e->map[(int)*y2][(int)*x2] : 0;
		e->map[(int)*y2 - 1][(int)*x2] ?
			*block_number = e->map[(int)*y2 - 1][(int)*x2] : 0;
	}
	return (sqrt((*x2 - e->cam->x) * (*x2 - e->cam->x) +
		(*y2 - e->cam->y) * (*y2 - e->cam->y)));
}

int				print_column(t_env *e, double *h, double angle, int x)
{
	double		x2[2];
	double		y2[2];
	double		dist[2];
	int			block_number[2];
	t_points	p[2];

	print_column2(e, x2, y2, angle);
	dist[0] = block(e, &(x2[0]), &(y2[0]), &(block_number[0]));
	print_column3(e, x2, y2, angle);
	dist[1] = block2(e, &(x2[1]), &(y2[1]), &(block_number[1]));
	*h = dist[0] < dist[1] ? (WIN_WIDTH / 2 * tan(e->cam->fov / 2) /
		dist[0]) : (WIN_WIDTH / 2 * tan(e->cam->fov / 2) / dist[1]);
	e->x = dist[0] < dist[1] ? y2[0] - (int)y2[0] : (x2[1] - (int)x2[1]);
	p[0].px = dist[0] < dist[1] ? x2[0] * 6 : x2[1] * 6;
	p[0].py = dist[0] < dist[1] ? y2[0] * 6 : y2[1] * 6;
	p[1].px = e->cam->x * (e->wid_map / e->xmax);
	p[1].py = e->cam->y * (e->hei_map / e->ymax);
	draw_line(p[0], p[1], e);
	x % 50 == 0 ? draw_line(p[0], p[1], e) : 0;
	return (dist[0] < dist[1] ? block_number[0] : block_number[1]);
}
