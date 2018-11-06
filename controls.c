/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:47:54 by okupin            #+#    #+#             */
/*   Updated: 2018/05/09 19:47:55 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		cleaner(t_world *e)
{
	t_meshlist	*mtmp;
	t_lightlist	*ltmp;

	while (e->meshlist)
	{
		mtmp = e->meshlist;
		e->meshlist = e->meshlist->next;
		free(mtmp->geometry);
		free(mtmp);
	}
	while (e->lightlist)
	{
		ltmp = e->lightlist;
		e->lightlist = e->lightlist->next;
		free(ltmp);
	}
	mlx_destroy_image(e->mlx, e->img.ptr);
	mlx_destroy_window(e->mlx, e->win);
}

int				ft_exit(t_world *e)
{
	cleaner(e);
	exit(1);
	return (0);
}

int				key_listener(int keycode, t_world *e)
{
	if (keycode == 53)
	{
		cleaner(e);
		exit(1);
	}
	return (0);
}

void			window_resize2(int x, int y, t_world *e)
{
	if ((x < 15 || x > (W2 - 20)) && e->w - 50 > 0)
	{
		mlx_destroy_window(e->mlx, e->win);
		e->w -= 50;
		e->win = mlx_new_window(e->mlx, W2, H2, "cool window");
		mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->w / 2, 0);
		reload_hooks(e);
	}
	else if ((y < 15 || y > (H2 - 20)) && e->h - 50 > 0)
	{
		mlx_destroy_window(e->mlx, e->win);
		e->h -= 50;
		e->win = mlx_new_window(e->mlx, W2, H2, "cool window");
		mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->w / 2, 0);
		reload_hooks(e);
	}
}

int				window_resize(int keycode, int x, int y, t_world *e)
{
	if (keycode == 1)
	{
		if ((x < 15 || x > (W2 - 20)) && e->w < 600)
		{
			mlx_destroy_window(e->mlx, e->win);
			e->w += 50;
			e->win = mlx_new_window(e->mlx, W2, H2, "cool window");
			mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->w / 2, 0);
			reload_hooks(e);
		}
		else if ((y < 15 || y > (H2 - 20)) && e->h < 600)
		{
			mlx_destroy_window(e->mlx, e->win);
			e->h += 50;
			e->win = mlx_new_window(e->mlx, W2, H2, "cool window");
			mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->w / 2, 0);
			reload_hooks(e);
		}
	}
	else if (keycode == 2)
		window_resize2(x, y, e);
	return (0);
}
