

#include "rtv1.h"

void	add_lambert_material(t_world *e)
{
	e->ka = 0.6;
	e->ks = 0;
	e->kd = 1;
	e->isrefractive = 0;
	e->isreflective = 0;
	e->gamma_s = 0;
}

void	mesh_add_material(t_world *e, t_v3 k, t_v3 r, float gamma_s)
{
	e->ka = k.x; // ambient intencity 0-1
	e->kd = k.y; // diffuse intencity 0-1
	e->ks = k.z; // specular intencity 0-1
	e->isrefractive = r.y;
	e->isreflective = r.x;
	e->ior = 1.1; // index of refraction 1.1 for water
	e->material_is_set = 1; // must be unset after applying for an object
	e->gamma_s = gamma_s; //specular exponent
}

void	mesh_add_transform(t_world *e, t_v3 r, t_v3 t)
{
	v_update(&(e->angle), r.x, r.y, r.z);
	v_update(&(e->translate), t.x, t.y, t.z);
}
