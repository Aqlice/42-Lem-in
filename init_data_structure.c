/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:39:06 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 15:05:11 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			printlst(t_list *head)
{
	int		i;
	t_list	*ptr;
	t_paths	*patr;

	i = 0;
	ptr = head;
	while (ptr)
	{
		ft_printf("Room |%d| is called |%s|\n", i, ptr->n);
		if (ptr->start == 1)
			ft_printf("Room |%d| is the START ROOM and has %d ants|\n", i, ptr->ant_nb);
		else if (ptr->end == 1)
			ft_printf("Room |%d| is the END ROOM\n", i);
		if (!ptr->path)
			ft_printf("Room |%d| has NO PATHS\n", i);
		else
		{
			patr = ptr->path;
			while (patr)
			{
				ft_printf("Room |%d|---->|%s|\n", i, patr->n);
				patr = patr->next;
			}
		}
		ptr = ptr->next;
		i++;
	}
}

static t_list	*create(char *name, int startendfg, int ants)
{
	t_list *new_node;

	new_node = NULL;
	if (!(new_node = malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero(new_node, sizeof(t_list));
	if (!(new_node->n = ft_strdup(name)))
	{
		free(new_node);
		return (NULL);
	}
	if (startendfg == 1)
	{
		new_node->start = 1;
		new_node->ant_nb = ants;
	}
	else if (startendfg == 2)
		new_node->end = 1;
	return (new_node);
}

static int		add_node(t_list ***head, char *name, int startendfg, int ants)
{
	t_list *ptr;
	t_list *new_node;

	ptr = **head;
	if (!**head)
	{
		if (!(new_node = create(name, startendfg, ants)))
			return (-1);
		**head = new_node;
		return (0);
	}
	while (ptr->next)
		ptr = ptr->next;
	if (!(new_node = create(name, startendfg, ants)))
		return (-1);
	ptr->next = new_node;
	new_node->prev = ptr;
	return (0);
}

static int		add_collisions(t_parse *box, t_hash *hash, t_list **head,
		int *c)
{
	t_hash *ptr;

	ptr = hash;
	while (ptr && ptr->room != NULL)
	{
		if (add_node(&head, ptr->room, ptr->startend, box->ant_nb) == -1)
		{
			errout(box->verbose,
					"ERROR: Failed to initialize data_structure.");
			free_list(head);
			return (0);
		}
		*c -= 1;
		ptr = ptr->next_col;
	}
	return (1);
}

t_list			*init_data_structure(t_parse *box)
{
	int		i;
	int		c;
	t_list	*head;

	i = 0;
	c = box->room_nb;
	head = NULL;
	while (c > 0)
	{
		if (box->room_ids[i].room)
			if (!add_collisions(box, &box->room_ids[i], &head, &c))
				return (NULL);
		i++;
	}
	return (head);
}
