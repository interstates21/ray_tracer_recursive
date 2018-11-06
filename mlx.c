/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:18 by okupin            #+#    #+#             */
/*   Updated: 2018/03/23 18:32:35 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_img(t_world *e)
{
	if ((e->img.ptr = mlx_new_image(e->mlx, W, H)) == NULL)
		return (-1);
	if ((e->img.data = mlx_get_data_addr(e->img.ptr,
	&e->img.bpp, &e->img.ln, &e->img.en)) == NULL)
		return (-1);
	return (0);
}

int			ft_mlx(t_world *e)
{
	if ((e->mlx = mlx_init()) == NULL)
		return (-1);
	if ((e->win = mlx_new_window(e->mlx, W, H, "cool window")) == NULL)
		return (-1);
	if ((ft_img(e) == -1))
		return (-1);
	return (0);
}

void		put_pixel(t_world *e, int x, int y, t_color color)
{
	color.r *= 254;
	color.g *= 254;
	color.b *= 254;
	if ((x > 0 && x < W) && (y > 0 && y < H))
	{
		e->img.data[(x * 4) + (y * W * 4) + 2] = color.r;
		e->img.data[(x * 4) + (y * W * 4) + 1] = color.g;
		e->img.data[(x * 4) + (y * W * 4)] = color.b;
	}
}
