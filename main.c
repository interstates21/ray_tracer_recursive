/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:28:44 by okupin            #+#    #+#             */
/*   Updated: 2018/05/07 17:28:45 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			reload_hooks(t_world *e)
{
	//for window resize
	mlx_hook(e->win, 17, 0, ft_exit, e);
	mlx_hook(e->win, 2, 1L << 0, key_listener, e);
	mlx_mouse_hook(e->win, window_resize, e);
	mlx_loop(e->mlx);
}

void			draw_each_frame(t_world *e)
{
	ft_bzero(e->img.data, (W * H * 4));
	mlx_clear_window(e->mlx, e->win);
	if (e->meshlist)
		foreach_pixel(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, 0, 0);
}

static int		choose_scene(t_world *e)
{
	if (e->scene == '1')
		scene_1(e);
	else if (e->scene == '2')
		scene_2(e);
	else if (e->scene == '3')
		scene_3(e);
	else if (e->scene == '4')
		scene_4(e);
	else
		scene_5(e);
	return (1);
}

static int		start(char *scene)
{
	t_world *e;

	if ((e = (t_world*)malloc(sizeof(t_world))) == NULL)
		return (-1);
	//set variables for the window resize in the future
	e->w = 1;
	e->h = 1;
	if (ft_mlx(e) == -1)
		return (-1);
	//pre-scene inits
	e->scene = scene[0];
	e->lightlist = NULL;
	e->meshlist = NULL;
	e->material_is_set = 0;
	choose_scene(e);
	//display the first frame
	draw_each_frame(e);
	//exit with the red cross
	mlx_hook(e->win, 17, 0, ft_exit, e);
	mlx_hook(e->win, 2, 1L << 0, key_listener, e);
	mlx_mouse_hook(e->win, window_resize, e);
	mlx_loop(e->mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc != 2 || (!ft_strequ("1", argv[1])
	&& !ft_strequ("2", argv[1]) && !ft_strequ("3", argv[1])
	&& !ft_strequ("4", argv[1]) && !ft_strequ("5", argv[1])))
	{
		ft_putstr("USAGE: ./rtv1 [1 | 2 | 3 | 4 | 5]\n");
		return (0);
	}
	if (start(argv[1]) == -1)
		ft_putstr("ERROR.\n");
	return (0);
}
