/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:09:35 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/17 19:55:31 by ozalisky         ###   ########.fr       */
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

void	ft_go_start(t_db *db, size_t path, t_r *room)
{
	db->ants--;
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

void	ft_go_not_start(t_db *db, size_t path, t_r *room)
{
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
}

void	ft_go(t_r *room, t_db *db)
{
	if (room->position == 1)
	{
		if (db->ants > 0)
			ft_go_start(db, ft_find_path(room), room);
		else
			ft_go(room->links[ft_find_path(room)], db);
	}
	else if (room->position)
	{
		if (!room->is_vaccant)
		{
			ft_go_not_start(db, ft_find_path(room), room);
			return ;
		}
		else
			ft_go(room->links[ft_find_path(room)], db);
	}
	if (room->end->finished_ants == db->moved_ants)
		return ;
}

void	ft_ants(t_db *db)
{
	while (db->rooms->end->finished_ants != db->moved_ants)
	{
		ft_go(db->rooms->start, db);
		ft_printf("\n");
	}
}
