/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 11:48:57 by magouin           #+#    #+#             */
/*   Updated: 2016/10/26 11:48:59 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	move_left(t_env *e)
{
	if (e->map[(int)(e->cam->y - sin(e->cam->theta + M_PI / 2) * -0.15)][
		(int)(e->cam->x + cos(e->cam->theta + M_PI / 2) * -0.15)] == 0)
	{
		e->cam->x += cos(e->cam->theta + M_PI / 2) * -0.15;
		e->cam->y -= sin(e->cam->theta + M_PI / 2) * -0.15;
	}
}

void	move_bot(t_env *e)
{
	if (e->map[(int)(e->cam->y - sin(e->cam->theta) * -0.15)][
		(int)(e->cam->x + cos(e->cam->theta) * -0.15)] == 0)
	{
		e->cam->x += cos(e->cam->theta) * -0.15;
		e->cam->y -= sin(e->cam->theta) * -0.15;
	}
}

void	move_right(t_env *e)
{
	if (e->map[(int)(e->cam->y - sin(e->cam->theta + M_PI / 2) * 0.15)][
		(int)(e->cam->x + cos(e->cam->theta + M_PI / 2) * 0.15)] == 0)
	{
		e->cam->x += cos(e->cam->theta + M_PI / 2) * 0.15;
		e->cam->y -= sin(e->cam->theta + M_PI / 2) * 0.15;
	}
}

void	move_top(t_env *e)
{
	if (e->map[(int)(e->cam->y - sin(e->cam->theta) * 0.15)][
		(int)(e->cam->x + cos(e->cam->theta) * 0.15)] == 0)
	{
		e->cam->x += cos(e->cam->theta) * 0.15;
		e->cam->y -= sin(e->cam->theta) * 0.15;
	}
}
