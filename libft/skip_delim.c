/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_delim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 02:54:11 by okupin            #+#    #+#             */
/*   Updated: 2017/11/13 02:54:53 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		skip_delim(int start, char *str, char delim)
{
	while (str[start] == delim)
		start++;
	return (start);
}
