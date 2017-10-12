/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:19 by magouin           #+#    #+#             */
/*   Updated: 2016/10/28 15:10:21 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	get_colors(int x, int y, char **xmp, int *co)
{
	int		color;
	char	c;
	int		count;
	int		mask;

	count = 1;
	mask = 256 * 256 * 16;
	y = ft_atoi(xmp[0] + 8) + y + 1;
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

void	draw_line(t_points p1, t_points p2, t_env *e)
{
	int x;
	int y;

	y = MIN(p1.py, p2.py);
	x = MIN(p1.px, p2.px);
	if (p1.px == p2.px)
	{
		while (y <= (int)MAX(p1.py, p2.py))
		{
			aa_pixel_put(e, x, y);
			y++;
		}
		return ;
	}
	if (p1.px < p2.px && p1.py <= p2.py)
		quadrant1(p1, p2, e);
	else if (p1.py <= p2.py && p2.px < p1.px)
		quadrant2(p1, p2, e);
	else if (p1.px < p2.px && p2.py <= p1.py)
		quadrant3(p1, p2, e);
	else if (p2.py <= p1.py && p2.px < p1.px)
		quadrant4(p1, p2, e);
}
