/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assertions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 13:17:17 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 13:50:58 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		assert_room_existence(t_parse *box, char *room_name)
{
	int		i;
	t_hash	*ptr;

	i = hash(box, room_name, ft_strichr(room_name, ' '));
	ptr = &box->room_ids[i];
	while (ptr && ptr->room)
	{
		if (!ft_strcmp(ptr->room, room_name))
			return (1);
		ptr = ptr->next_col;
	}
	return (0);
}

int		assert_validity(t_parse *box, int i)
{
	if (!*box->input[i])
		return (1);
	else if (!(box->room1 = ft_strsub(box->input[i], 0,
					ft_strichr(box->input[i], '-')))
			|| !(box->room2 = ft_strdup(ft_strchr(box->input[i], '-') + 1)))
	{
		ft_strdel(&box->room1);
		ft_strdel(&box->room2);
		errout(box->verbose, "ERROR: Failed to separate rooms in linkage.");
		return (-1);
	}
	else if (ft_strcmp(box->room1, box->room2) != 0
			&& assert_room_existence(box, box->room1)
			&& assert_room_existence(box, box->room2))
		return (1);
	ft_strdel(&box->room1);
	ft_strdel(&box->room2);
	return (0);
}

int		assert_correct_node(char *node_name, char *target)
{
	char *ptr;

	if (!ft_strstr(node_name, target))
		return (0);
	else if (!ft_strcmp(node_name, target))
		return (1);
	else if ((!ft_strcmp(target, "start") || !ft_strcmp(target, "end"))
			&& ft_strstr(node_name, target)
			&& ft_strchr(node_name, '-'))
		return (1);
	else if (ft_strstr(node_name, target) && ft_strcmp(node_name, target) != 0
			&& (ptr = ft_strchr(node_name, '-'))
			&& !ft_strcmp(ptr + 1, target))
		return (1);
	return (0);
}

int		assert_no_duplicate(t_parse *box, char *line, int i)
{
	int		j;

	j = i - 2;
	while (j > 1)
	{
		if (!ft_strncmp(box->input[j], line, ft_strichr(line, ' '))
				&& !ft_strncmp(box->input[j],
					line, ft_strichr(box->input[j], ' ')))
			return (0);
		j--;
	}
	while (box->input[i] && !ft_strchr(box->input[i], '-'))
	{
		if (!ft_strncmp(box->input[i], line, ft_strichr(line, ' '))
				&& !ft_strncmp(box->input[i],
					line, ft_strichr(box->input[i], ' ')))
			return (0);
		i++;
	}
	return (1);
}
