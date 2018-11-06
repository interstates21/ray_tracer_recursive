/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 22:17:26 by okupin            #+#    #+#             */
/*   Updated: 2018/05/24 22:17:26 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//create new node for push. Add information to the object from the temp e-> updated in the constuctor
static t_meshlist			*geometry_new(t_world *e)
{
	t_meshlist *this;

	this = (t_meshlist*)malloc(sizeof(t_meshlist));
	if (!e->function || !e->geometry || !this)
		return (NULL);
	this->id = e->id;
	this->kd = e->kd;
	this->ka = e->ka;
	this->ks = e->ks;
	this->isinside = 0; // initially we are outside of the object
	this->index_of_refraction = e->ior;
	this->isrefractive = e->isrefractive;
	this->isreflective = e->isreflective;
	this->gamma_s = e->gamma_s;
	this->color  = ui_to_rgb(e->color);
	this->color.r /= 255.0;
	this->color.g /= 255.0;
	this->color.b /= 255.0;
	this->function = e->function;
	this->geometry = e->geometry;
	this->next = NULL;
	return (this);
}

//create new node
static t_lightlist		*light_new(t_v3 light_pos)
{
	t_lightlist *this;

	this = (t_lightlist*)malloc(sizeof(t_lightlist));
	if (!this)
		return (NULL);
	this->pos = light_pos;
	this->next = NULL;
	return (this);
}

//add an element to the end of the list
int						geometry_push(t_world *e, t_meshlist **begin)
{
	t_meshlist *this;
	if (*begin == NULL)
	{
		*begin = geometry_new(e);
		if (!(*begin))
			return (-1);
		return (1);
	}
	this = *begin;
	while (this->next != NULL)
		this = this->next;
	this->next = geometry_new(e);
	if (!(this->next))
		return (-1);

	return (1);
}
//push a new light with an initialized pos
int						new_light(t_world *e, t_v3 light_pos)
{
	t_lightlist *this;

	if (e->lightlist == NULL)
	{
		e->lightlist = light_new(light_pos);
		if (!(e->lightlist))
			return (-1);
		return (1);
	}
	else
	{
		this = e->lightlist;
		while (this->next != NULL)
			this = this->next;
		this->next = light_new(light_pos);
		if (!(this->next))
		return (-1);
	}
	return (1);
}
