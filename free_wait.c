/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:40:28 by casautou          #+#    #+#             */
/*   Updated: 2019/09/24 18:40:29 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_wait(t_stock *stock)
{
	t_wait *temp;

	while (stock->free)
	{
		temp = stock->free;
		stock->free = stock->free->next;
		free(temp);
	}
	stock->free = NULL;
	stock->f = 0;
}

void	free_all(t_stock *stock)
{
	int i;

	i = 0;
	while (i < stock->size)
	{
		if (stock->matrix[i])
			free(stock->matrix[i]);
		i++;
	}
	free_wait(stock);
	if (stock->matrix)
		free(stock->matrix);
	if (stock->tab)
		free(stock->tab);
	if (stock->abp)
		free(stock->abp);
}
