/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delforlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:15:04 by okupin            #+#    #+#             */
/*   Updated: 2017/11/11 22:15:49 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delforlist(void *cont, size_t size)
{
	if (cont != NULL)
		free(cont);
	size = 0;
}
