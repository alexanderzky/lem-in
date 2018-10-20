/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms_fncts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:34:38 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/20 15:35:17 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_check_rooms(t_db *db)
{
	t_r		*temp;
	t_r		*inner_temp;

	temp = db->rooms;
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
