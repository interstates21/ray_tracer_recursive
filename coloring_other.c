/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:33:27 by okupin            #+#    #+#             */
/*   Updated: 2018/06/08 18:33:28 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		ui_to_rgb(unsigned int i)
{
	t_color this;

	this.b = i & 255;
	this.g = (i >> 8) & 255;
	this.r = (i >> 16) & 255;
	return (this);
}

t_color		rgb(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color		gamma_correction(t_world *e, float fcolor[3])
{
	t_color color;

	fcolor[0] = 1.0f - exp(fcolor[0] * e->exposure);
	fcolor[1] = 1.0f - exp(fcolor[1] * e->exposure);
	fcolor[2] = 1.0f - exp(fcolor[2] * e->exposure);
	fcolor[0] = (fcolor[0] > 1.0f) ? 1.0f : fcolor[0];
	fcolor[1] = (fcolor[1] > 1.0f) ? 1.0f : fcolor[1];
	fcolor[2] = (fcolor[2] > 1.0f) ? 1.0f : fcolor[2];
	fcolor[0] = (fcolor[0] < 0.0f) ? 0.0f : fcolor[0];
	fcolor[1] = (fcolor[1] < 0.0f) ? 0.0f : fcolor[1];
	fcolor[2] = (fcolor[2] < 0.0f) ? 0.0f : fcolor[2];
	color.r = (fcolor[0]);
	color.g = (fcolor[1]);
	color.b = (fcolor[2]);
	return (color);
}

void		cylinder_get_normal(t_world *e, t_cylinder *this, float t)
{
	t_v3	proj;
	t_v3	hitpoint;

	hitpoint = v_add(e->eye, v_scale(e->raydir, t));
	e->temp_normal = v_diff(hitpoint, this->c);
	proj = v_proj(e->temp_normal, this->rot);
	e->temp_normal = v_norm(v_scale(v_diff(e->temp_normal, proj), -1));
}

void		cone_get_normal(t_world *e, t_cone *this, float t)
{
	t_v3	proj;
	t_v3	hitpoint;
	float		k;

	hitpoint = v_add(e->eye, v_scale(e->raydir, t));
	e->temp_normal = v_diff(hitpoint, this->c);
	proj = v_proj(e->temp_normal, this->rot);
	k = 1 + tan(this->angle) * tan(this->angle);
	proj = v_scale(proj, k);
	e->temp_normal = v_norm(v_scale(v_diff(e->temp_normal, proj), -1));
}
