/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:03:00 by okupin            #+#    #+#             */
/*   Updated: 2018/05/21 18:03:14 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3	v_diff(t_v3 a, t_v3 b)
{
	t_v3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_v3	v_add(t_v3 a, t_v3 b)
{
	t_v3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_v3	v_cross(t_v3 a, t_v3 b)
{
	t_v3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_v3	v_scale(t_v3 a, float scalar)
{
	t_v3 c;

	c.x = a.x * scalar;
	c.y = a.y * scalar;
	c.z = a.z * scalar;
	return (c);
}

float		v_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void		v_print(char *str, t_v3 a)
{
	printf("---%s--- x: %f y: %f z: %f\n", str, a.x, a.y, a.z);
}