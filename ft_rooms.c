/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:02:54 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/23 20:03:24 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_init_temp(t_r *temp)
{
	temp->next_room = NULL;
	temp->prev_room = NULL;
	temp->links = NULL;
	temp->start = NULL;
	temp->end = NULL;
	temp->step = 2147483647;
	temp->links_size = 0;
	temp->link_slot = 0;
	temp->connected = 0;
	temp->is_vaccant = 1;
	temp->ant_name = 0;
	temp->finished_ants = 0;
	temp->position = -1;
}

void	ft_ch_position(t_db *db, t_r *temp, t_r *prev)
{
	if (db->start == 1)
	{
		temp->position = 1;
		db->start = 2;
		temp->start = temp;
	}
	if (db->end == 1)
	{
		temp->position = 0;
		temp->end = temp;
		db->end = 2;
		temp->step = 0;
	}
	if (prev)
	{
		temp->prev_room = prev;
		prev->next_room = temp;
	}
}

void	ft_mark_rooms(t_db *db, t_r *temp)
{
	if (db->rooms == NULL)
		db->rooms = temp;
	if (db->rooms->start)
		temp->start = db->rooms->start;
	else if (db->start == 2)
		ft_link_start(db, temp->start);
	if (db->rooms->end)
		temp->end = db->rooms->end;
	else if (db->end == 2)
		ft_link_end(db, temp->end);
}

void	ft_find_crdnts(t_db *db, t_r *temp, int name_length)
{
	temp->name = ft_memalloc(sizeof(char *) * (name_length + 1));
	db->links_i = -1;
	while (db->line[++db->links_i] ^ ' ')
		temp->name[db->links_i] = db->line[db->links_i];
	temp->name[db->links_i] = '\0';
	if (ft_chrinstr(temp->name, '-'))
		db->error = 1;
	while (!(ft_isdigit(db->line[db->links_i])))
		++db->links_i;
	temp->x = ft_atoi(db->line + db->links_i);
	while (ft_isdigit(db->line[db->links_i]))
		++db->links_i;
	temp->y = ft_atoi(db->line + db->links_i);
}

void	ft_saveroom(t_db *db)
{
	t_r	*prev;
	t_r	*temp;
	int name_length;

	name_length = 0;
	temp = db->rooms;
	db->links_i = 0;
	prev = NULL;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next_room;
	}
	temp = (t_r*)malloc(sizeof(t_r));
	while (db->line[db->links_i++] ^ ' ')
		++name_length;
	ft_find_crdnts(db, temp, name_length);
	ft_init_temp(temp);
	ft_ch_position(db, temp, prev);
	ft_mark_rooms(db, temp);
}
