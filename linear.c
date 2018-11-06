
#include "rtv1.h"

static void		t_rotate_x(t_v3 *p, float angle)
{
	float temp;

	angle = angle * M_PI / 180.0;
	temp = p->y;
	p->y = p->y * cos(angle) - p->z * sin(angle);
	p->z = temp * sin(angle) + p->z * cos(angle);
}

static void		t_rotate_y(t_v3 *p, float angle)
{
	float temp;

	angle = angle * M_PI / 180.0;
	temp = p->z;
	p->z = p->z * cos(angle) + p->x * sin(angle);
	p->x = p->x * cos(angle) - temp * sin(angle);
}

static void		t_rotate_z(t_v3 *p, float angle)
{
	float temp;

	angle = angle * M_PI / 180.0;
	temp = p->x;
	p->x = p->x * cos(angle) - p->y * sin(angle);
	p->y = temp * sin(angle) + p->y * cos(angle);
}

void			t_translate(t_world *e, t_v3 *p)
{
	p->x += e->translate.x;
	p->y += e->translate.y;
	p->z += e->translate.z;
}

void			t_rotate(t_world *e, t_v3 *p)
{
	t_rotate_x(p, e->angle.x);
	t_rotate_y(p, e->angle.y);
	t_rotate_z(p, e->angle.z);
}
