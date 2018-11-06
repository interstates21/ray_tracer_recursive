
#include "rtv1.h"

t_v3		vt(float x, float y, float z)
{
	t_v3 c;

	c.x = x;
	c.y = y;
	c.z = z;
	return (c);
}

void			v_update(t_v3 *a, float f1, float f2, float f3)
{
	a->x = f1;
	a->y = f2;
	a->z = f3;
}

float			v_mag(t_v3 a)
{
	return (sqrt(SQR(a.x) + SQR(a.y) + SQR(a.z)));
}

t_v3		v_norm(t_v3 a)
{
	t_v3	c;
	float		l;

	l = v_mag(a);
	c.x = a.x / l;
	c.y = a.y / l;
	c.z = a.z / l;
	return (c);
}

t_v3		v_proj(t_v3 a, t_v3 b)
{
	t_v3	proj;
	float		temp;

	temp = v_dot(a, b) / v_dot(b, b);
	proj = v_scale(b, temp);
	return (proj);
}
