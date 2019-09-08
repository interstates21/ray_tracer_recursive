/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:29:33 by okupin            #+#    #+#             */
/*   Updated: 2018/05/07 17:29:35 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft/libft.h"
# include "geometry.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "MinilibX/sierra/mlx.h"

# define MAX(a,b) ((a < b) ? b : a)
# define SQR(x) (x * x)
# define W 1024
# define V0 vt(0, 0, 0)
# define V1 vt(1, 1, 1)
# define VX(x) (vt(x, 0, 0))
# define VY(x) (vt(0, x, 0))
# define VZ(x) (vt(0, 0, x))
# define BIAS (v_scale(obj.normal, 0.001))
# define ZERO 0.00001
# define AIR_INX_REF 1.0
# define H 648
# define W2 1024 + e->w
# define H2 648 + e->h
# define HALFWIDTH W / 2
# define HALFHEIGHT H / 2
# define ASPECTRATIO (float)W / (float)H
# define KLEFT 123
# define KRIGHT 124
# define KUP 126
# define KDOWN 125
# define INFIN 1e8
# define NEAR 0.0001
# define DEGREE(a)			(a * (M_PI / 180))
# define WHITE 0xffffff
# define BLACK 0x000000
# define RED 0xff0000
# define BLUE 0x4444ff
# define LIGHTBLUE 0x8888ff
# define DARKBLUE 0x111166
# define GREY0 0x222222
# define GREY1 0x444444
# define GREY2 0x666666
# define GREY3 0x888888
# define GREY4 0xaaaaaa
# define YELLOW 0xffff00
# define AMBIENT 0.5
# define RANDOMPOS ((random() % 60) - 30)
# define RANDOMSIZE (random() % 10)
# define RANDOMCOL (random() % (255 * 255 * 255))

typedef struct	s_img
{
	void		*ptr;
	int			xpm_w;
	int			xpm_h;
	int			en;
	int			ln;
	int			bpp;
	char		*data;
}				t_img;

typedef struct	s_world
{
	char		scene;
	char		id;
	void		*mlx;
	void		*win;
	t_img		img;
	float		fov;
	t_v3		forward;
	t_v3		up;
	t_v3		right;
	t_v3		lookat;
	t_v3		fakeup;
	t_v3		eye;
	t_v3		raydir;
	t_v3		angle;
	t_v3		translate;
	t_v3		temp_normal;
	t_v3		normal;
	t_v3		hit;
	void		*geometry;
	float		(*function)(struct s_world *e, t_v3 eye, t_v3 dir);
	t_meshlist	*meshlist;
	t_lightlist	*lightlist;
	float		color;
	float		diffuse;
	float		specular;
	float		kd;
	float		ka;
	float		ks;
	float		gamma_s;
	float		ambient;
	float		exposure;
	int			isrefractive;
	int			isreflective;
	float		ior;
	int			material_is_set;
	int			isglass;
	int			w;
	int			h;
	int			depth;
}				t_world;

void			t_translate(t_world *e, t_v3 *p);
void			t_rotate(t_world *e, t_v3 *p);
t_v3			v_diff(t_v3 a, t_v3 b);
t_v3			v_add(t_v3 a, t_v3 b);
t_v3			v_cross(t_v3 a, t_v3 b);
t_v3			v_proj(t_v3 a, t_v3 b);
t_v3			vt(float x, float y, float z);
void			v_update(t_v3 *a, float f1, float f2, float f3);
t_v3			v_norm(t_v3 a);
t_v3			v_scale(t_v3 a, float scalar);
float			v_dot(t_v3 a, t_v3 b);
float			v_mag(t_v3 a);

t_color			c_scale(t_color b, float a);
t_color			c_mix(t_color b, t_color a, float k1);
void			draw_each_frame(t_world *e);
int				ft_exit(t_world *e);
int				ft_mlx(t_world *e);
void			put_pixel(t_world *e, int x, int y, t_color color);
int				key_listener(int keycode, t_world *e);
void			foreach_pixel(t_world *e);

float			sphere_intersect(t_world *e, t_v3 eye, t_v3 dir);
float			plane_intersect(t_world *e, t_v3 eye, t_v3 dir);
float			cylinder_intersect(t_world *e, t_v3 eye, t_v3 dir);
float			cone_intersect(t_world *e, t_v3 eye, t_v3 dir);

void			cylinder_get_normal(t_world *e, t_cylinder *this, float t);
void			cone_get_normal(t_world *e, t_cone *this, float t);

void			new_cam(t_world *e, t_v3 eye, t_v3 l);
int				new_sphere(t_world *e, float r, int color);
int				new_plane(t_world *e, int color);
int				new_cylinder(t_world *e, float r, int color);
int				new_cone(t_world *e, float angle, int color);
int				new_light(t_world *e, t_v3 light_pos);

int				geometry_push(t_world *e, t_meshlist **begin);

void			scene_1(t_world *e);
void			scene_2(t_world *e);
void			scene_3(t_world *e);
void			scene_4(t_world *e);
void			scene_5(t_world *e);

void			mesh_add_material(t_world *e, t_v3 k, t_v3 r, float gamma_s);
void			mesh_add_transform(t_world *e, t_v3 r, t_v3 t);
void			add_lambert_material(t_world *e);
t_color			rgb(int r, int g, int b);
t_color			get_color(t_world *e, t_meshlist obj);

t_color			rgb(int r, int g, int b);
t_color			ui_to_rgb(unsigned int i);
t_color			gamma_correction(t_world *e, float fcolor[3]);
void			reload_hooks(t_world *e);
int				window_resize(int keycode, int x, int y, t_world *e);
void			v_print(char *str, t_v3 a);

t_color			intersect_recursive(t_world *e, t_meshlist obj, t_v3 dir);
t_color			intersect(t_world *e, t_v3 eye, t_v3 dir);
float			intersect_shadow(t_world *e, t_v3 hit, t_v3 lightvec);

#endif
