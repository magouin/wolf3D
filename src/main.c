/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 18:58:53 by magouin           #+#    #+#             */
/*   Updated: 2016/10/31 18:07:49 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		handle_key_event(int keycode, t_env *e)
{
	int		x;

	x = 0;
	if (keycode == 53)
	{
		free(e->cam);
		while (x < e->ymax)
		{
			free(e->map[x]);
			x++;
		}
		free(e->map);
		exit(EXIT_SUCCESS);
	}
	zoom(keycode, e);
	rotate_up_left(keycode, e);
	rotate_down_right(keycode, e);
	move_plus(keycode, e);
	move_minus(keycode, e);
	return (0);
}

int		close_hook(t_env *e)
{
	int		x;

	x = 0;
	free(e->cam);
	while (x < e->ymax)
	{
		free(e->map[x]);
		x++;
	}
	free(e->map);
	exit(EXIT_SUCCESS);
}

int		loop_hook(t_env *e)
{
	if (e->flag)
	{
		mlx_clear_window(e->mlx, e->win);
		print_weapon(e, 13 - e->flag);
		mlx_put_image_to_window(e->mlx, e->win, e->image, 0, 0);
		mlx_put_image_to_window(e->mlx, e->win, e->img_map, 100, 100);
		mlx_put_image_to_window(e->mlx, e->win, e->weapon,
			2 * WIN_WIDTH / 6, 2 * WIN_HEIGHT / 3);
		e->flag--;
		usleep(4000);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_env e;

	ac = 0;
	e.flag = 0;
	parsing(av[1], &e);
	e.mlx = mlx_init();
	e.image = mlx_new_image(e.mlx, WIN_WIDTH, WIN_HEIGHT);
	e.str_image = mlx_get_data_addr(e.image,
			&(e.bits_per_pixel), &(e.size_line), &(e.endian));
	e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	put_picture(&e);
	mlx_do_key_autorepeaton(e.mlx);
	mlx_hook(e.win, 2, 0, handle_key_event, &e);
	mlx_hook(e.win, 17, 3, close_hook, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
