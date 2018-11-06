/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 03:46:48 by okupin            #+#    #+#             */
/*   Updated: 2018/06/23 03:46:48 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	c_mix(t_color b, t_color a, float k1)
{
	t_color c;

	c.r = (k1 * b.r) + (1 - k1) * a.r;
	c.g = (k1 * b.g) + (1 - k1) * a.g;
	c.b = (k1 * b.b) + (1 - k1) * a.b;

	return (c);
}

t_color	c_scale(t_color b, float a)
{
	t_color c;

	c.r = b.r * a;
	c.g = b.g * a;
	c.b = b.b * a;

	return (c);
}