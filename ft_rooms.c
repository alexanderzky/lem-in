/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:02:54 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/17 20:57:02 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_check_rooms(t_db *db)
{
	t_r		*temp;
	t_r		*inner_temp;

	temp = db->rooms->start;
	while (temp->next_room)
	{
		inner_temp = temp->next_room;
		while (inner_temp)
		{
			if (temp->x == inner_temp->x && temp->y == inner_temp->y)
			{
				ft_printf("ERROR\n");
				exit(0);
			}
			if (ft_strcmp(temp->name, inner_temp->name) == 0)
			{
				ft_printf("ERROR\n");
				exit(0);
			}
			inner_temp = inner_temp->next_room;
		}
		temp = temp->next_room;
	}
}

void	ft_link_start(t_db *db, t_r *start)
{
	t_r *temp;
	t_r *t_start;

	t_start = start ? start : db->rooms->start;
	temp = db->rooms;
	while (temp)
	{
		if (!temp->start)
		{
			temp->start = t_start;
		}
		temp = temp->next_room;
	}
}

void	ft_link_end(t_db *db, t_r *end)
{
	t_r *temp;
	t_r *t_end;

	t_end = end ? end : db->rooms->end;
	temp = db->rooms;
	while (temp)
	{
		if (!temp->end)
		{
			temp->end = t_end;
		}
		temp = temp->next_room;
	}
}

int		ft_chrinstr(const char *s, int c)
{
	char *c_s;
	char c_c;

	c_s = (char *)s;
	c_c = (char)c;
	while (*c_s)
	{
		if (*c_s == c_c)
		{
			return (1);
		}
		c_s++;
	}
	if (*c_s == c_c)
	{
		return (1);
	}
	return (0);
}

void	ft_room_cycle(t_db *db, char *str)
{
	if (db->is_room_i == 0 && str[db->is_room_i] ^ 'L' && str[db->is_room_i] ^
	'#' && str[db->is_room_i] ^ ' ')
	{
		++db->is_room_name;
		while (db->is_room_i < ft_strlen(str) && str[db->is_room_i + 1] ^ ' ')
			++db->is_room_i;
	}
	else if (str[db->is_room_i] == ' ')
		++db->is_room_spaces;
	else if (ft_isdigit(str[db->is_room_i]))
	{
		++db->is_room_coordinates;
		while (db->is_room_i < ft_strlen(str) && ft_isdigit(str[db->is_room_i])
		&& str[db->is_room_i + 1] ^ ' ')
			++db->is_room_i;
		if (ft_isalpha(str[db->is_room_i]))
			++db->is_room_wrong;
	}
	else if (ft_isalpha(str[db->is_room_i]))
	{
		++db->is_room_wrong;
	}
	++db->is_room_i;
}

int		ft_isroom(t_db *db, char *str)
{
	db->is_room_wrong = 0;
	db->is_room_coordinates = 0;
	db->is_room_name = 0;
	db->is_room_spaces = 0;
	db->is_room_i = 0;
	while (db->is_room_i < ft_strlen(str))
	{
		ft_room_cycle(db, str);
	}
	if (db->is_room_name == 1 && db->is_room_spaces == 2 &&
	db->is_room_coordinates == 2 && db->is_room_wrong == 0)
		return (1);
	return (0);
}

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
	else if (db->end == 2 && db->start == 2)
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
