/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:09:35 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/08 20:17:36 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int ft_find_path(t_r *room)
{
	int path;
	int i;

	path = 2147483647;
	i = 0;
	while (i < room->links_size)
	{
		if (room->links[i]->step > 0 && room->links[i]->step < path)
			path = room->links[i]->step;
		++i;
	}

	return (path);
}

void ft_go(t_r *room, t_db *db)
{
	int path;

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
				if(!room->links[path]->position)
					room->links[path]->finished_ants++;
				ft_printf("L%d-%s ", room->links[path]->ant_name,room->links[path]->name);
			}
			else
			{
				ft_go(room->links[path],db);
				room->links[path]->ant_name = db->ant_name_counter++;
				room->links[path]->is_vaccant = 0;
				ft_printf("L%d-%s ", room->links[path]->ant_name,room->links[path]->name);
			}
		}
	}
	else if (room->position /*&& !room->is_vaccant*/)
	{
		path = ft_find_path(room);
		if (room->links[path]->is_vaccant || !room->links[path]->position)
		{
			room->links[path]->is_vaccant = 0;
			room->is_vaccant = 1;
			room->links[path]->ant_name = room->ant_name;
			if(!room->links[path]->position)
				room->links[path]->finished_ants++;
			ft_printf("L%d-%s ", room->links[path]->ant_name,room->links[path]->name);
		}
		else
		{
			ft_go(room->links[path],db);
			room->links[path]->ant_name = room->ant_name;
			room->links[path]->is_vaccant = 0;
			room->is_vaccant = 1;
			ft_printf("L%d-%s ", room->links[path]->ant_name,room->links[path]->name);
		}
		return;
	}
	if ((!db->ants && room->position) || (room->is_vaccant && room->position == -1))
	{
		ft_go(db->rooms->start, db);
	}
	if (room->end->finished_ants == db->moved_ants)
		return;
	ft_printf("\n");
	ft_go(db->rooms->start, db);

//	else if (!room->position)
//	{
//		if (db->ants > 0)
//		{
//			room->ant_name--;
//			path = ft_find_path(room);
//			room->links[path]->is_vaccant = 0;
//			room->links[path]->ant_name = room->ant_name;
//		}
//	}
}

void ft_ants(t_db *db)
{
	ft_go(db->rooms->start, db);
}