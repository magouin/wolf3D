/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 19:00:08 by magouin           #+#    #+#             */
/*   Updated: 2016/03/16 13:53:22 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	zoom(int keycode, t_env *e)
{
	if (keycode == 69)
	{
		if (e->cam->fov < 1.5)
		{
			mlx_clear_window(e->mlx, e->win);
			e->cam->fov += 2 * M_PI / 360 * 2;
			put_picture(e);
		}
	}
	else if (keycode == 78)
	{
		if (e->cam->fov > 0.5)
		{
			e->cam->fov -= 2 * M_PI / 360 * 2;
			put_picture(e);
		}
	}
	else if (keycode == 49)
	{
		e->flag = 12;
	}
}

void	rotate_up_left(int keycode, t_env *e)
{
	if (keycode == 124)
	{
		mlx_clear_window(e->mlx, e->win);
		e->cam->theta += (M_PI / 2) / 90 * 5;
		e->cam->theta >= 2 * M_PI ? e->cam->theta -= 2 * M_PI : 0;
		put_picture(e);
	}
	else if (keycode == 123)
	{
		mlx_clear_window(e->mlx, e->win);
		e->cam->theta -= (M_PI / 2) / 90 * 5;
		e->cam->theta < 0 ? e->cam->theta += 2 * M_PI : 0;
		put_picture(e);
	}
}

void	rotate_down_right(int keycode, t_env *e)
{
	if (keycode == 0)
	{
		mlx_clear_window(e->mlx, e->win);
		move_left(e);
		put_picture(e);
	}
	if (keycode == 13)
	{
		mlx_clear_window(e->mlx, e->win);
		move_top(e);
		put_picture(e);
	}
	if (keycode == 2)
	{
		mlx_clear_window(e->mlx, e->win);
		move_right(e);
		put_picture(e);
	}
	if (keycode == 1)
	{
		mlx_clear_window(e->mlx, e->win);
		move_bot(e);
		put_picture(e);
	}
}

void	move_plus(int keycode, t_env *e)
{
	keycode = 1;
	(void)e;
}

void	move_minus(int keycode, t_env *e)
{
	keycode = 1;
	(void)e;
}
