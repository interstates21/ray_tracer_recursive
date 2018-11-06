/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 19:40:15 by okupin            #+#    #+#             */
/*   Updated: 2018/05/24 19:40:16 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

struct s_world;

typedef struct	s_color
{
	float r;
	float g;
	float b;
}				t_color;

typedef struct			s_vector3
{
	float				x;
	float				y;
	float				z;
	int					color;
}						t_v3;

typedef struct			s_object
{
	struct s_object		*next;
	void				*geometry;
	t_v3				normal;
	t_v3				hit;
	int					isinside;
	t_color				color;
	float				ka;
	float				kd;
	float				ks;
	float				index_of_refraction;
	int					isrefractive;
	int					isreflective;
	float				gamma_s;
	char				id;
	float				(*function)(struct s_world *e, t_v3 eye, t_v3 dir);
}						t_meshlist;

typedef struct			s_lightlist
{
	struct s_lightlist	*next;
	t_v3			pos;
	int					color;
}						t_lightlist;

typedef struct			s_sphere
{
	t_v3			c;
	float				r;
}						t_sphere;

typedef struct			s_plane
{
	t_v3			p;
	t_v3			n;
}						t_plane;

typedef struct			s_cylinder
{
	t_v3			c;
	t_v3			rot;
	float				r;
}						t_cylinder;

typedef struct			s_cone
{
	t_v3			c;
	t_v3			rot;
	float				angle;
}						t_cone;

#endif
