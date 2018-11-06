/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:32:10 by okupin            #+#    #+#             */
/*   Updated: 2018/06/08 18:32:10 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		sphere_intersect(t_world *e, t_v3 eye, t_v3 dir)
{
	t_sphere	*this;
	float		dabc[4];
	float		t1;
	float		t2;
	t_v3		centerdist;

	this = e->geometry;
	centerdist = v_diff(eye, this->c);
	dabc[1] = v_dot(dir, dir);
	dabc[2] = 2 * v_dot(dir, centerdist);
	dabc[3] = v_dot(centerdist, centerdist) - SQR(this->r);
	dabc[0] = SQR(dabc[2]) - 4 * dabc[1] * dabc[3];
	if (dabc[0] < 0)
		return (INFIN);
	t1 = (-dabc[2] - sqrt(dabc[0])) / (2 * dabc[1]);
	if (t1 > 0 && t1 < INFIN)
	{
		e->temp_normal = v_norm(v_diff(v_add(eye,
		v_scale(dir, t1)), this->c));
		return (t1);
	}
	else if (t1 < 0)
	{
		t2 = (-dabc[2] + sqrt(dabc[0])) / (2 * dabc[1]);
		if (t2 > 0 && t2 < INFIN)
		{
			e->temp_normal = v_norm(v_diff(v_add(eye,
			v_scale(dir, t2)), this->c));
			return (t2);
		}
	}
	return (INFIN);
}

float		plane_intersect(t_world *e, t_v3 eye, t_v3 dir)
{
	t_plane		*this;
	float		temp;
	float		t;

	this = e->geometry;
	this->n = v_norm(this->n);
	temp = v_dot(dir, this->n);
	if (temp == 0.0f)
		return (INFIN);
	t = v_dot(v_diff(this->p, eye), this->n) / temp;
	if (t > 0 && t < INFIN)
	{
		e->temp_normal = this->n;
		return (t);
	}
	return (INFIN);
}

float		cylinder_intersect(t_world *e, t_v3 eye, t_v3 dir)
{
	t_cylinder	*this;
	float		dabc[4];
	float		t;
	float		d;
	float		d2;
	t_v3	temp;

	this = e->geometry;
	temp = v_diff(eye, this->c);
	d = v_dot(dir, this->rot);
	d2 = v_dot(temp, this->rot);
	dabc[1] = v_dot(dir, dir) - d * d;
	dabc[2] = 2 * (v_dot(dir, temp) -
	(d * d2));
	dabc[3] = v_dot(temp, temp) - (d2 * d2) - (SQR(this->r));
	dabc[0] = (SQR(dabc[2])) - 4 * dabc[1] * dabc[3];
	if (dabc[0] < 0)
		return (INFIN);
	t = (-dabc[2] - sqrt(dabc[0])) / (2 * dabc[1]);
	if (t > 0 && t < INFIN)
	{
		cylinder_get_normal(e, this, t);
		return (t);
	}
	return (INFIN);
}

// float		triangle_intersect(t_world *e)
// {
// 	t_triangle	*this;
// 	float		t1;

// 	this = e->geometry;
// }

float		cone_intersect(t_world *e, t_v3 eye, t_v3 dir)
{
	t_cone		*this;
	float		dabc[4];
	float		t;
	float		k;
	t_v3	temp;

	this = e->geometry;
	temp = v_diff(eye, this->c);
	k = tan(this->angle);
	dabc[1] = v_dot(dir, dir)
	- (1 + k * k) * (SQR(v_dot(dir, this->rot)));
	dabc[2] = 2 * (v_dot(dir, temp) - (1 + (SQR(k)))
	* v_dot(dir, this->rot) * v_dot(temp, this->rot));
	dabc[3] = v_dot(temp, temp)
	- (1 + (SQR(k))) * (SQR(v_dot(temp, this->rot)));
	dabc[0] = (SQR(dabc[2])) - (4 * dabc[1] * dabc[3]);
	if (dabc[0] <= 0)
		return (INFIN);
	t = (-dabc[2] - sqrt(dabc[0])) / (2 * dabc[1]);
	if (t > 0 && t < INFIN)
	{
		cone_get_normal(e, this, t);
		return (t);
	}
	return (INFIN);
}
