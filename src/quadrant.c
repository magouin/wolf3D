/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:26 by magouin           #+#    #+#             */
/*   Updated: 2016/10/28 15:10:30 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	aa_pixel_put(t_env *e, int x, int y)
{
	if (x < 0 || x >= e->wid_map || y < 0 || y >= e->hei_map)
		return ;
	e->map_image[x * 4 + 0 + y * 4 * e->wid_map] = 0xff;
	e->map_image[x * 4 + 1 + y * 4 * e->wid_map] = 0xff;
	e->map_image[x * 4 + 2 + y * 4 * e->wid_map] = 0xff;
	e->map_image[x * 4 + 3 + y * 4 * e->wid_map] = 0;
}

void	quadrant1(t_points p1, t_points p2, t_env *e)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p2.py - p1.py) / ((double)p2.px - p1.px) > 1 ? 0 : 1);
	de = (i ? 2 * (p2.py - p1.py) : 2 * (p2.px - p1.px));
	dp = (i ? 2 * (p2.py - p1.py) - (p2.px - p1.px)
			: 2 * (p2.px - p1.px) - (p2.py - p1.py));
	dne = (i ? 2 * ((p2.py - p1.py) - (p2.px - p1.px))
			: 2 * ((p2.px - p1.px) - (p2.py - p1.py)));
	aa_pixel_put(e, p1.px, p1.py);
	while ((p1.px < p2.px && i == 1) || (p1.py < p2.py && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			i ? p1.py++ : p1.px++;
			dp = dp + dne;
		}
		i ? p1.px++ : p1.py++;
		aa_pixel_put(e, p1.px, p1.py);
	}
}

void	quadrant2(t_points p1, t_points p2, t_env *e)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p2.py - p1.py) / ((double)p1.px - p2.px) > 1 ? 0 : 1);
	de = (i ? 2 * (p2.py - p1.py) : 2 * (p1.px - p2.px));
	dp = (i ? 2 * (p2.py - p1.py) - (p1.px - p2.px)
			: 2 * (p1.px - p2.px) - (p2.py - p1.py));
	dne = (i ? 2 * ((p2.py - p1.py) - (p1.px - p2.px))
			: 2 * ((p1.px - p2.px) - (p2.py - p1.py)));
	aa_pixel_put(e, p1.px, p1.py);
	while ((p1.px > p2.px && i == 1) || (p1.py < p2.py && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			dp = dp + dne;
			i ? p1.py++ : p1.px--;
		}
		i ? p1.px-- : p1.py++;
		aa_pixel_put(e, p1.px, p1.py);
	}
}

void	quadrant3(t_points p1, t_points p2, t_env *e)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p1.py - p2.py) / ((double)p2.px - p1.px) > 1 ? 0 : 1);
	de = (i ? 2 * (p1.py - p2.py) : 2 * (p2.px - p1.px));
	dp = (i ? 2 * (p1.py - p2.py) - (p2.px - p1.px)
			: 2 * (p2.px - p1.px) - (p1.py - p2.py));
	dne = (i ? 2 * ((p1.py - p2.py) - (p2.px - p1.px))
			: 2 * ((p2.px - p1.px) - (p1.py - p2.py)));
	aa_pixel_put(e, p1.px, p1.py);
	while ((p1.px < p2.px && i == 1) || (p1.py > p2.py && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			dp = dp + dne;
			i ? p1.py-- : p1.px++;
		}
		i ? p1.px++ : p1.py--;
		aa_pixel_put(e, p1.px, p1.py);
	}
}

void	quadrant4(t_points p1, t_points p2, t_env *e)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p1.py - p2.py) / ((double)p1.px - p2.px) > 1 ? 0 : 1);
	de = (i ? 2 * (p1.py - p2.py) : 2 * (p1.px - p2.px));
	dp = (i ? 2 * (p1.py - p2.py) - (p1.px - p2.px)
			: 2 * (p1.px - p2.px) - (p1.py - p2.py));
	dne = (i ? 2 * ((p1.py - p2.py) - (p1.px - p2.px))
			: 2 * ((p1.px - p2.px) - (p1.py - p2.py)));
	aa_pixel_put(e, p1.px, p1.py);
	while ((p1.px > p2.px && i == 1) || (p1.py > p2.py && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			i ? p1.py-- : p1.px--;
			dp = dp + dne;
		}
		i ? p1.px-- : p1.py--;
		aa_pixel_put(e, p1.px, p1.py);
	}
}
