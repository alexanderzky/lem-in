/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:09:35 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/16 19:14:02 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

size_t	ft_find_path(t_r *room)
{
	int		path;
	size_t	i;
	size_t	array_cell;

	path = 2147483647;
	array_cell = 0;
	i = 0;
	while (i < room->links_size)
	{
		if ((room->links[i]->step > 0 && room->links[i]->step < path) ||
		!room->links[i]->position)
		{
			path = room->links[i]->step;
			array_cell = i;
		}
		++i;
	}
	return (array_cell);
}

void	ft_go(t_r *room, t_db *db)
{
	size_t path;

	if (room->position == 1)
	{
		if (db->ants > 0)
		{
			db->ants--;
			path = ft_find_path(room);
			if (room->links[path]->is_vaccant || !room->links[path]->position)
			{
				room->links[path]->ant_name = db->ant_name_counter++;
				room->links[path]->is_vaccant = 0;
				if (!room->links[path]->position)
					room->links[path]->finished_ants++;
				if (!ft_strcmp("0", room->links[path]->name))
					ft_printf("L%d-0 ", room->links[path]->ant_name);
				else
					ft_printf("L%d-%s ", room->links[path]->ant_name,
							room->links[path]->name);
			}
			else
			{
				ft_go(room->links[path], db);
				room->links[path]->ant_name = db->ant_name_counter++;
				room->links[path]->is_vaccant = 0;
				if (!ft_strcmp("0", room->links[path]->name))
					ft_printf("L%d-0 ", room->links[path]->ant_name);
				else
					ft_printf("L%d-%s ", room->links[path]->ant_name,
							room->links[path]->name);
			}
		}
		else
		{
			path = ft_find_path(room);
			ft_go(room->links[path], db);
		}
	}
	else if (room->position)
	{
		if (!room->is_vaccant)
		{
			path = ft_find_path(room);
			if (room->links[path]->is_vaccant || !room->links[path]->position)
			{
				room->links[path]->is_vaccant = 0;
				room->is_vaccant = 1;
				room->links[path]->ant_name = room->ant_name;
				if (!room->links[path]->position)
					room->links[path]->finished_ants++;
				if (!ft_strcmp("0", room->links[path]->name))
					ft_printf("L%d-0 ", room->links[path]->ant_name);
				else
					ft_printf("L%d-%s ", room->links[path]->ant_name,
							room->links[path]->name);
			}
			else
			{
				ft_go(room->links[path], db);
				room->links[path]->ant_name = room->ant_name;
				room->links[path]->is_vaccant = 0;
				room->is_vaccant = 1;
				if (!ft_strcmp("0", room->links[path]->name))
					ft_printf("L%d-0 ", room->links[path]->ant_name);
				else
					ft_printf("L%d-%s ", room->links[path]->ant_name,
							room->links[path]->name);
			}
			return ;
		}
		else
		{
			path = ft_find_path(room);
			ft_go(room->links[path], db);
		}
	}
	if (room->end->finished_ants == db->moved_ants)
		return ;
	ft_printf("\n");
}

void	ft_ants(t_db *db)
{
	while (db->rooms->end->finished_ants != db->moved_ants)
	{
		ft_go(db->rooms->start, db);
	}
}
