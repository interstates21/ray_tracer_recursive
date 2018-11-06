/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 12:10:18 by okupin            #+#    #+#             */
/*   Updated: 2018/05/25 12:10:19 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	float		get_specular(t_v3 eye, t_v3 light_pos, t_meshlist obj)
{
	t_v3			h;
	t_v3			eye_vector;
	t_v3			light_vector;
	float			hitangle;

	if (obj.ks <= 0)
		return (0);
	light_vector = v_norm(v_diff(light_pos, obj.hit));
	eye_vector = v_norm(v_diff(eye, obj.hit));
	h = v_norm(v_add(eye_vector, light_vector));
	hitangle = pow(v_dot(h, obj.normal), obj.gamma_s);
	return (obj.ks * hitangle);
}

static float		get_diffuse(t_world *e, t_v3 light_pos, t_meshlist obj)
{
	t_v3			light_vector;
	float			light_dist;
	float			hitangle;
	float			tshadow;

	light_vector = v_diff(light_pos, obj.hit);
	light_dist = v_mag(light_vector);
	light_vector = v_norm(light_vector);
	hitangle = v_dot(light_vector, obj.normal);
	tshadow = intersect_shadow(e, obj.hit, light_vector);
	if (hitangle < 0)
		return (0);
	if (tshadow < (light_dist) && tshadow > ZERO)
		return (0);
	return (obj.kd * hitangle);
}

static float		get_ambient(t_v3 eye, t_meshlist obj)
{
	float			distance;

	distance = v_mag(v_diff(obj.hit, eye));
	distance /= (INFIN);
	return (AMBIENT * obj.ka);
}

t_color				get_color(t_world *e, t_meshlist obj)
{
	float			fcolor[3];
	float			diffuse;
	t_lightlist		*iter;

	e->diffuse = 0;
	e->specular = 0;
	e->ambient = get_ambient(e->eye, obj);
	obj.hit = v_add(obj.hit, BIAS);
	iter = e->lightlist;
	while (iter)
	{
		diffuse = get_diffuse(e, iter->pos, obj);
		if (diffuse)
		{
			e->specular += get_specular(e->eye, iter->pos, obj);
			e->diffuse += diffuse;
		}
		iter = iter->next;
	}
	fcolor[0] = obj.color.r * (e->diffuse + e->ambient) + e->specular;
	fcolor[1] = obj.color.g * (e->diffuse + e->ambient) + e->specular;
	fcolor[2] = obj.color.b * (e->diffuse + e->ambient) + e->specular;
	return (gamma_correction(e, fcolor));
}
