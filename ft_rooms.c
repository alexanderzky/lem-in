/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:02:54 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/12 21:05:00 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_isroom(char *str)
{
	int i;
	int spaces;
	int name;
	int coordinates;
	int wrong;

	wrong = 0;
	coordinates = 0;
	name = 0;
	spaces = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (i == 0 && str[i] != 'L' && str[i] != '#' && str[i] != ' ')
		{
			++name;
			while (i < ft_strlen(str) && str[i + 1] != ' ')
				++i;
		}
		else if (str[i] == ' ')
			++spaces;
		else if (ft_isdigit(str[i]))
		{
			++coordinates;
			while (i < ft_strlen(str) && ft_isdigit(str[i]) && str[i + 1] != ' ')
			{
				++i;
			}
			if (ft_isalpha(str[i]))
			{
				++wrong;
			}
		}
		else if (ft_isalpha(str[i]))
		{
			++wrong;
		}
		++i;
	}
	if (name == 1 && spaces == 2 && coordinates == 2 && wrong == 0)
		return (1);
	return (0);
}

void	ft_saveroom(t_db *db)
{
	int i;
	t_r	*prev;
	t_r	*temp;
	int name_length;

	name_length = 0;
	temp = db->rooms;
	i = 0;
	prev = NULL;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next_room;
	}

	if (!(temp = (t_r*)malloc(sizeof(t_r))))
		db->error = 1;
	while (db->line[i++] != ' ')
	{
		++name_length;
	}
	temp->name = ft_memalloc(sizeof(char *) * (name_length + 1));
	i = 0;
	while (db->line[i] != ' ')
	{
		temp->name[i] = db->line[i];
		++i;
	}
	temp->name[i] = '\0';
	while (!(ft_isdigit(db->line[i])))
		++i;
	temp->x = ft_atoi(db->line + i);
	while (ft_isdigit(db->line[i]))
		++i;
	temp->y = ft_atoi(db->line + i);
	if (db->start)
	{
		temp->position = 1;
		db->start = 0;
	}
	else if (db->end)
	{
		temp->position = -1;
		db->end = 0;
	}
	else
		temp->position = 0;
	if (prev != NULL)
	{
		temp->prev_room = prev;
		prev->next_room = temp;
	}
	if (temp->position == 1)
	{
		temp->start = temp;
		temp->prev_room = prev;
	}
	else if (temp->position ^ 1)
	{
		temp->start = temp->prev_room->start;
	}
	temp->next_room = NULL;
	temp->links = NULL;
	if (db->rooms == NULL)
	{
		db->rooms = temp->start;
	}
}
