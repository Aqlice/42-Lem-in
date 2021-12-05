/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:25:48 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/18 13:42:57 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_paths(t_paths **head)
{
	t_paths *ptr;

	if (*head)
	{
		while (*head)
		{
			ptr = *head;
			*head = (*head)->next;
			if (ptr != NULL)
			{
				ft_strdel(&ptr->n);
				free(ptr);
			}
		}
		*head = NULL;
	}
}

void			free_list(t_list **head)
{
	t_list *ptr;

	if (*head)
	{
		while (*head)
		{
			ptr = *head;
			*head = (*head)->next;
			if (ptr != NULL)
			{
				if (ptr->path != NULL)
					free_paths(&ptr->path);
				ft_strdel(&ptr->n);
				free(ptr);
			}
		}
		*head = NULL;
	}
}

void			free_hashtable(t_parse **box)
{
	int		i;
	t_hash	*ptr;
	t_hash	*ptr2;
	t_hash	*hash;

	i = 0;
	while (i < (*box)->room_nb)
	{
		if ((*box)->room_ids[i].room != NULL)
		{
			hash = &(*box)->room_ids[i];
			ptr = hash->next_col;
			while (ptr)
			{
				ptr2 = ptr->next_col;
				ft_strdel(&ptr->room);
				free(ptr);
				ptr = ptr2;
			}
			ft_strdel(&hash->room);
		}
		i++;
	}
	free((*box)->room_ids);
}

void			free_parser(t_parse **box)
{
	if ((*box)->input != NULL)
		ft_tabdel(ft_tab_size((*box)->input), &(*box)->input);
	if ((*box)->output != NULL)
		ft_tabdel(ft_tab_size((*box)->output), &(*box)->output);
	if ((*box)->room1 != NULL)
		ft_strdel(&(*box)->room1);
	if ((*box)->room2 != NULL)
		ft_strdel(&(*box)->room2);
	if ((*box)->room_ids != NULL)
		free_hashtable(box);
}
