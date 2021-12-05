/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_another_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:35:26 by casautou          #+#    #+#             */
/*   Updated: 2019/09/24 18:35:29 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_another_path(t_list *begin, t_paths *curr)
{
	if (!(begin->pfnext))
	{
		begin->pfnext = curr->room;
		curr->room->pfnext = NULL;
		return ;
	}
	while (begin->pfnext)
		begin = begin->pfnext;
	begin->pfnext = curr->room;
	curr->room->pfnext = NULL;
}
