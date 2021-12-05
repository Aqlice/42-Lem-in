/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_info_saver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:40:38 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 12:48:50 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*fetch_node(t_list *head, char *room_name,
		int (*assert_correct_node)(char *, char *))
{
	t_list *ptr;

	ptr = head;
	if (ptr == NULL)
		return (NULL);
	while (ptr != NULL)
	{
		if (assert_correct_node(ptr->n, room_name) == 1)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

static t_paths	*create_path(char *room_name, t_list *room_node)
{
	t_paths *new_node;

	new_node = NULL;
	if (!(new_node = malloc(sizeof(t_paths))))
		return (NULL);
	ft_bzero(new_node, sizeof(t_paths));
	if (!(new_node->n = ft_strdup(room_name)))
	{
		free(new_node);
		return (NULL);
	}
	new_node->room = room_node;
	return (new_node);
}

static int		add_path(t_list *node, char *room_name, t_list *link)
{
	t_paths		*ptr;
	t_paths		*new_node;

	ptr = node->path;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		if (!(new_node = create_path(room_name, link)))
			return (-1);
		ptr->next = new_node;
	}
	else if (!(node->path = create_path(room_name, link)))
		return (-1);
	return (0);
}

static int		link_saver(t_parse *box, t_list *head)
{
	t_list	*ptr1;
	t_list	*ptr2;

	if ((ptr1 = fetch_node(head, box->room1, &assert_correct_node))
			&& (ptr2 = fetch_node(head, box->room2, &assert_correct_node)))
	{
		if (add_path(ptr1, box->room2, ptr2) == -1
				|| add_path(ptr2, box->room1, ptr1) == -1)
		{
			errout(box->verbose,
					"Error, failed to allocate memory during linkage.");
			return (-1);
		}
	}
	ft_strdel(&box->room1);
	ft_strdel(&box->room2);
	if (!ptr1 || !ptr2)
	{
		errout(box->verbose,
				"Error, fetcher couldn't return room node address.");
		return (-1);
	}
	return (0);
}

int				link_description(t_parse *box, t_list *head)
{
	int i;
	int ret;

	i = box->link_i;
	while (box->input[i] && (ret = assert_validity(box, i)) > 0)
	{
		if (*box->input[i])
		{
			if (link_saver(box, head) == -1)
			{
				free_list(&head);
				return (-1);
			}
		}
		i++;
	}
	if (ret == -1)
		return (ret);
	return (ret);
}
