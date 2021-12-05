/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_flow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:08:43 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 16:08:48 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_get_flow(t_stock *stock, t_list *begin)
{
	stock->io = 0;
	begin->mark = stock->ref;
	begin->prev = NULL;
}
