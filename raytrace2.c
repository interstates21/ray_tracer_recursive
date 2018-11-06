/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:16:17 by okupin            #+#    #+#             */
/*   Updated: 2018/06/11 23:16:17 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	refract(t_world *e, t_meshlist obj, t_v3 dir, float n1, float n2)
{
	float	n;
	float	cosi;
	float	sint2;
	float	cost;
	t_v3	new_dir;

	n = n1 / n2;
	cosi = -(v_dot(obj.normal, dir));
	sint2 = n * n * (1.0 - cosi * cosi);
	if (sint2 > 1.0)
		return(rgb(0,0,0));
	cost = sqrt(1.0 - sint2);
	new_dir =v_norm(v_add(v_scale(dir, n), v_scale(obj.normal, (n * cosi - cost))));
	return (intersect(e, v_diff(obj.hit, BIAS), new_dir));
}

t_color	reflect(t_world *e, t_meshlist obj, t_v3 dir)
{
	float	cosi;
	t_v3	new_dir;

	cosi = -(v_dot(obj.normal, dir));
	new_dir = v_norm(v_add(dir, v_scale(obj.normal, cosi * 2)));
	return (intersect(e, v_add(obj.hit, BIAS), new_dir));
}

float fresnel(t_v3 dir, t_meshlist obj) 
{ 
	float kr;
		float etai = 1, etat = 1.1; 
	float cosi = v_dot(dir, (obj.normal)); 
	if (obj.isinside)
		ft_swap(&etai, &etat);
  float sint = etai / etat * sqrtf(MAX(0.f, 1.0f - cosi * cosi)); 
    if (sint >= 1) {
        kr = 1;
    } 
    else { 
      float cost = sqrtf(MAX(0, 1 - sint * sint)); 
       cosi = fabs(cosi); 
      float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
      float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
    return (kr);
} 

t_color intersect_recursive(t_world *e, t_meshlist obj, t_v3 dir)
{
	t_color	refl_color;
	t_color refr_color;
	t_color color;
	float	fr;

	refl_color = reflect(e, obj, dir);
	if (obj.isrefractive == 0)
		return (refl_color);

		refr_color = refract(e, obj, dir, AIR_INX_REF, obj.index_of_refraction);
		fr = fresnel(dir, obj);
		// color.r = refl_color.r * fr + refr_color.r * (1.0f - fr);
		// color.g = refl_color.g * fr + refr_color.g * (1.0f - fr);
		// color.b = refl_color.b * fr + refr_color.b * (1.0f - fr);
		color = c_mix(refl_color, get_color(e, obj), 1);

	return (color);
}
