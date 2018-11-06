/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:46:00 by okupin            #+#    #+#             */
/*   Updated: 2018/05/09 19:46:00 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		get_raydirection(t_world *e, int j, int i)
{
	float	jcam;
	float	icam;
	float	hcam;
	float	wcam;
	// get ray direction from the eye to each pixel on the screen
	jcam = (2.0f * j) / W - 1.0; // transform (current x pixel) in the window space (from 0 to WIDTH) to the camera abstract space (from -1 to 1)
	icam = (-2.0f * i) / H + 1.0; // same for y;
	hcam = tan(e->fov); // the camera canvas top is a tangent (triangle math) of your eye_field_of_view angle from a camera constructor
	wcam = hcam * ASPECTRATIO; // the camera canvas width/height must be the same as in the window space. We can find the cam canvas left side then;
	e->raydir.x = jcam * wcam * e->right.x // the ray direction = (camera transformed x) * (move to the left side) * (new coordinate frame x) + 
	+ icam * hcam * e->up.x + e->forward.x;// + the same for y + (new coordinate frame z * 1 (for each pixel the z direction is always the same))
	e->raydir.y = jcam * wcam * e->right.y
	+ icam * hcam * e->up.y + e->forward.y;
	e->raydir.z = jcam * wcam * e->right.z
	+ icam * hcam * e->up.z + e->forward.z;
	e->raydir = v_norm(e->raydir);
}

t_color	intersect(t_world *e, t_v3 eye, t_v3 dir)
{
	float		tmin;
	float		t;
	t_meshlist	*iter;
	t_meshlist	final_obj;

	tmin = INFIN;
	iter = e->meshlist; // begin list
	while (iter)
	{
		e->geometry = iter->geometry; // argument for an iter->function
		if ((t = iter->function(e, eye, dir))) // get intersection point with an object if there is one
			if (tmin > t) // if the current intersection is the closest so far - remember the cuurent intersection
			{
				// collect shading information if we decided to remember the intersection
				tmin = t;
				final_obj = (*iter);
				final_obj.normal = e->temp_normal;
				final_obj.color = iter->color;
			}
		iter = iter->next;
	}
	e->depth++; // this function called n + 1 times. Needed to stop recursion
	if (tmin >= INFIN || tmin < ZERO) // no intersection has found
		return (rgb(0, 0, 0));
	final_obj.hit = v_add(eye, v_scale(dir, tmin)); // find the hit point to use in coloring
	if (v_dot(dir, final_obj.normal) > 0) // if we are intersecting object from inside - remember this to use in refractions.
	{
		final_obj.normal = v_scale(final_obj.normal, -1); // reverse the normal so that it has a correct angle from inside.
		final_obj.isinside = 1;
	}
	if (e->depth > 4)
		return (get_color(e, final_obj)); // stop recursion at some reasonable point
	if (final_obj.isreflective || final_obj.isrefractive)
	  	return (intersect_recursive(e, final_obj, dir)); // if the object is not diffuse - redirect the light to the next diffuce object and get it's color recursively
	// else if(final_obj.isinside)
	// 	return (rgb(0,0,0));
	return (get_color(e, final_obj));
}

float			intersect_shadow(t_world *e, t_v3 hit, t_v3 lightvec)
{
	float		tmin;
	float		t;
	t_meshlist	*iter;

	if (e->meshlist == NULL)
		return (0);
	tmin = INFIN;
	iter = e->meshlist;
	while (iter)
	{
		e->geometry = iter->geometry;
		if ((t = iter->function(e, hit, lightvec)))
			if (tmin > t)
				tmin = t;
		iter = iter->next;
	}
	return (tmin);
}

static int		beautiful_black_frame(t_world *e, int i, int j)
{
	if (i < 10 || j < 10 || j > (W - 11) || i > (H - 11))
	{
		put_pixel(e, j, i, rgb(0, 0, 0));
		return (1);
	}
	return (0);
}

void			foreach_pixel(t_world *e)
{
	int		i;
	int		j;

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			if (beautiful_black_frame(e, i, j))
			{
				put_pixel(e, j++, i, rgb(0, 0, 0));
				continue;
			}
			e->depth = 0;
			get_raydirection(e, j, i); //direction through the current pixel (j, i, (-z const))
			put_pixel(e, j++, i, intersect(e, e->eye, e->raydir));
		}
		i++;
	}
}
