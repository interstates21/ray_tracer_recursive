/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 20:41:45 by okupin            #+#    #+#             */
/*   Updated: 2018/06/06 20:41:45 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		set_cam(t_world *e)
{
		e->exposure = -1;
		new_cam(e, vt(10, 30, 100), V0);
}

void		set_planes(t_world *e)
{
	mesh_add_transform(e, V0, VY(-5));
	new_plane(e, WHITE);

	// mesh_add_transform(e, V0, vt(10, 30, -20));
	// new_sphere(e, 5, RED);
	mesh_add_transform(e, V0, vt(10, 35, -20));
	new_sphere(e, 5, BLUE);
	mesh_add_transform(e, vt(90,0,0), vt(10, 10, -110));
	new_plane(e, LIGHTBLUE);
}

void		scene_1(t_world *e)
{
	set_cam(e);
	new_plane(e, RED);
	new_light(e, vt(-20, 10, 24));

}


void		scene_2(t_world *e)
{
	e->exposure = -1.0;
	new_cam(e, vt(0, 0, 100), V0);

	mesh_add_transform(e, VX(90), VZ(-25));
	new_plane(e, RED);

	mesh_add_transform(e, VX(180), VY(30));
	new_plane(e, RED);

	mesh_add_transform(e, V0, VY(-20));
	new_plane(e, RED);

	mesh_add_transform(e, V0, vt(-8, 0, 10));
	new_cylinder(e, 3, RED);

	mesh_add_transform(e, V0, vt(8, 0, 10));
	new_cylinder(e, 3, RED);

	mesh_add_transform(e, VZ(90), vt(0, 5, 10));
	new_cone(e, 45, GREY1);

	mesh_add_transform(e, V0, vt(0, 5, 10));
	new_sphere(e, 2, GREY0);

	new_light(e, vt(0, 11, 12));
}

void		scene_3(t_world *e)
{
	e->exposure = -1.0;
	new_cam(e, VZ(150), VY(35));

	mesh_add_transform(e, VX(90), VZ(-50));
	new_plane(e, RED);

	mesh_add_transform(e, V0, VY(25));
	new_sphere(e, 10, RED);

	new_light(e, vt(-20, 10, 24));
	new_light(e, vt(20, 10, 24));
	new_light(e, vt(-10, 10, 18));
	new_light(e, vt(10, 10, 18));
	new_light(e, vt(0, 5, 20));
}

void		scene_4(t_world *e)
{
	int i;

	i = 0;
	e->exposure = -1.0;

	new_cam(e, vt(0, 0, 100), V0);

	mesh_add_transform(e, VX(90), VZ(-40));
	new_plane(e, LIGHTBLUE);
	while (i < 100)
	{
		if (i % 2)
			mesh_add_material(e, vt(1, 0.7, 40), V1, 3);

		mesh_add_transform(e, V0,
		vt(RANDOMPOS, RANDOMPOS + 10, RANDOMPOS));
		new_sphere(e, RANDOMSIZE / 2, RANDOMCOL);

		i++;
	}
	new_light(e, vt(0, 20, 40));
}

void		scene_5(t_world *e)
{
	int i;

	i = -30;
	e->exposure = -0.1;
	new_cam(e, vt(0, 0, 100), V0);

	// mesh_add_transform(e, VX(90), VZ(-40));
	// new_plane(e, LIGHTBLUE);

	// mesh_add_transform(e, V0, VY(-30));
	// new_plane(e, LIGHTBLUE);

	// mesh_add_transform(e, VX(180), VY(40));
	// new_plane(e, LIGHTBLUE);

	// mesh_add_transform(e, VZ(90), VX(-40));
	// new_plane(e, LIGHTBLUE);

	// mesh_add_transform(e, VZ(90), VX(40));
	// new_plane(e, LIGHTBLUE);
	while (i < 30)
	{
		//mesh_add_transform(e, VZ(i * 1.5), VZ(i));
		new_cylinder(e, 5, LIGHTBLUE);
		i += 13;
	}
	new_light(e, vt(16, 20, 10));
	new_light(e, vt(-16, 5, 10));
}
