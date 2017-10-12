/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 19:01:11 by magouin           #+#    #+#             */
/*   Updated: 2016/10/28 15:08:45 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int		ft_open(char *fichier, t_env *e)
{
	int		fd;
	char	*str;
	int		i;
	int		test;

	fd = open(fichier, O_RDONLY);
	str = NULL;
	while ((i = get_next_line(fd, &str)))
	{
		(i == -1) ? ft_putstr_fd(2, "Invalide file.\n", NULL) : 0;
		e->xmax = 0;
		while (str[e->xmax] != '\0')
			(e->xmax)++;
		if (e->ymax == 0)
			test = e->xmax;
		else
			test != e->xmax ? ft_putstr_fd(2, "Map Error\n", NULL) : 0;
		(e->ymax)++;
	}
	close(fd);
	free(str);
	e->wid_map = e->xmax * 6;
	e->hei_map = e->ymax * 6;
	e->img_map = mlx_new_image(e->mlx, e->xmax * 6, e->ymax * 6);
	return (fd);
}

void			foret(t_env *e, char *str, int count_y, int count_x)
{
	if (str[count_x] == '0')
	{
		if (e->cam == NULL)
		{
			e->cam = malloc(sizeof(t_cam));
			!(e->cam) ? ft_putstr_fd(2, "Malloc failed\n", NULL) : 0;
			e->cam->fov = M_PI / 3;
			e->cam->z = 0.5;
			e->cam->ray = e->cam->fov / WIN_WIDTH;
			e->cam->x = count_x + 0.5;
			e->cam->y = count_y + 0.5;
			e->cam->theta = 0;
		}
		e->map[count_y][count_x] = 0;
	}
	else if (str[count_x] <= '9' && str[count_x] >= '1')
		e->map[count_y][count_x] = str[count_x] - '0';
	else if (str[count_x] <= 'b' && str[count_x] >= 'a')
		e->map[count_y][count_x] = str[count_x] - 'a' + 10;
	else
		ft_putstr_fd(2, "Caractere accepted : 0123456789ab\n", NULL);
	if ((count_y == 0 || count_y == e->ymax - 1 || count_x == e->
xmax - 1 || count_x == 0) && e->map[count_y][count_x] == 0)
		ft_putstr_fd(2, "Parsing Map ERROR\n", NULL);
}

void			map_creation(t_env *e, char *fichier)
{
	int		count_x;
	int		count_y;
	char	*str;
	int		fd;

	str = NULL;
	count_y = 0;
	e->cam = NULL;
	fd = open(fichier, O_RDONLY);
	while (count_y < e->ymax)
	{
		get_next_line(fd, &str);
		count_x = 0;
		while (count_x < e->xmax)
		{
			foret(e, str, count_y, count_x);
			count_x++;
		}
		count_y++;
	}
	free(str);
	e->cam == NULL ? ft_putstr_fd(2, "No bock to put camera!\n", NULL) : 0;
}

void			parsing(char *fichier, t_env *e)
{
	int		fd;
	int		count;

	e->xmax = 0;
	e->ymax = 0;
	fd = ft_open(fichier, e);
	e->map_image = mlx_get_data_addr(e->img_map, &(count), &(count), &(count));
	e->weapon = mlx_new_image(e->mlx, WIN_WIDTH / 3, WIN_HEIGHT / 3);
	e->str_weapon = mlx_get_data_addr(e->weapon, &count, &count, &count);
	count = 0;
	e->map = malloc(sizeof(int *) * (e->ymax + 1));
	if (!e->map)
		ft_putstr_fd(2, "Malloc failed\n", NULL);
	e->map[e->ymax] = NULL;
	while (count < e->ymax)
	{
		e->map[count] = malloc(sizeof(int) * e->xmax);
		if (!e->map[count])
			ft_putstr_fd(2, "Malloc failed\n", NULL);
		count++;
	}
	map_creation(e, fichier);
}
