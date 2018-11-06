

#include "rtv1.h"

void	new_cam(t_world *e, t_v3 eye, t_v3 l)
{
	v_update(&(e->eye), eye.x, eye.y, eye.z); //translate the eye position
	v_update(&(e->lookat), l.x, l.y, l.z); //translate the point of view
	v_update(&(e->fakeup), 0, 1, 0); //let's assume that up direction is y1;
	//construct a new coordinate frame (x,y,z) in the camera space (not the window space)
	e->forward = v_norm(v_diff(e->lookat, e->eye));  // (eye - point of view) is a new z
	e->right = v_norm(v_cross(e->forward, e->fakeup)); // get a 90degree vector to get a new x 
	e->up = v_cross(e->right, e->forward); // get a new up vector 90degree to both x and z;
	//in case of the mesh-add-transform for the camera 
	t_rotate(e, &(e->forward));
	t_rotate(e, &(e->right));
	t_rotate(e, &(e->up));
	t_translate(e, &(e->eye));
	e->fov = 25.0f * M_PI / 180.0f; // how wide the eye is, in degrees
}


int		new_sphere(t_world *e, float r, int color)
{
	t_sphere		*this;

	if (!(this = (t_sphere*)malloc(sizeof(t_sphere))))
		return (-1);
	this->r = r;
	//in case of mesh-add-transform
	v_update(&this->c, 0, 0, 0);
	t_translate(e, &(this->c));
	if (!e->material_is_set)
		add_lambert_material(e); // default material if notspecified
	e->id = '0'; // not used yet
	e->color = color;
	e->geometry = this; // save geometry to add to the list
	e->function = sphere_intersect; // specify a function to add to the list
	e->material_is_set = 0; // don't use this material for the next object
	if (geometry_push(e, &(e->meshlist)) == -1) // add to the list
		return (-1);
	return (1);
}

int		new_plane(t_world *e, int color)
{
	t_plane		*this;

	if (!(this = (t_plane*)malloc(sizeof(t_plane))))
		return (-1);
	v_update(&this->n, 0, 1, 0);
	v_update(&this->p, 0, 0, 0);
	t_rotate(e, &(this->n));
	t_translate(e, &(this->p));
	if (!e->material_is_set)
		add_lambert_material(e);
	e->id = '1';
	e->color = color;
	e->geometry = this;
	e->function = plane_intersect;
	e->material_is_set = 0;
	if (geometry_push(e, &(e->meshlist)) == -1)
		return (-1);
	return (1);
}

int		new_cylinder(t_world *e, float r, int color)
{
	t_cylinder		*this;

	if (!(this = (t_cylinder*)malloc(sizeof(t_cylinder))))
		return (-1);
	v_update(&this->rot, 0, 1, 0);
	v_update(&this->c, 0, 0, 0);
	t_rotate(e, &(this->rot));
	t_translate(e, &(this->c));
	if (!e->material_is_set)
		add_lambert_material(e);
	this->r = r;
	e->id = '2';
	e->color = color;
	e->geometry = this;
	e->function = cylinder_intersect;
	e->material_is_set = 0;
	if (geometry_push(e, &(e->meshlist)) == -1)
		return (-1);
	return (1);
}

int		new_cone(t_world *e, float angle, int color)
{
	t_cone		*this;

	if (!(this = (t_cone*)malloc(sizeof(t_cone))))
		return (-1);
	v_update(&this->rot, 0, 1, 0);
	v_update(&this->c, 0, 0, 0);
	t_rotate(e, &(this->rot));
	t_translate(e, &(this->c));
	if (!e->material_is_set)
		add_lambert_material(e);
	this->angle = DEGREE(angle);
	e->id = '3';
	e->color = color;
	e->geometry = this;
	e->function = cone_intersect;
	e->material_is_set = 0;
	if (geometry_push(e, &(e->meshlist)) == -1)
		return (-1);
	return (1);
}
