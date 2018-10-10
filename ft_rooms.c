/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:02:54 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/10 17:49:11 by ozalisky         ###   ########.fr       */
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
			if (ft_strcmp(temp->name,inner_temp->name) == 0)
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
	temp=db->rooms;
	while(temp)
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
	temp=db->rooms;
	while(temp)
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
		if (i == 0 && str[i] ^ 'L' && str[i] ^ '#' && str[i] ^ ' ')
		{
			++name;
			while (i < ft_strlen(str) && str[i + 1] ^ ' ')
				++i;
		}
		else if (str[i] == ' ')
			++spaces;
		else if (ft_isdigit(str[i]))
		{
			++coordinates;
			while (i < ft_strlen(str) && ft_isdigit(str[i]) && str[i + 1] ^ ' ')
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
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	temp->step = 0;
	while (db->line[i++] ^ ' ')
	{
		++name_length;
	}
	if (!(temp->name = ft_memalloc(sizeof(char *) * (name_length + 1))))
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	i = 0;
	while (db->line[i] ^ ' ')
	{
		temp->name[i] = db->line[i];
		++i;
	}
	temp->name[i] = '\0';
	if (ft_chrinstr(temp->name,'-'))
	{
		db->error = 1;
	}
	while (!(ft_isdigit(db->line[i])))
		++i;
	temp->x = ft_atoi(db->line + i);
	while (ft_isdigit(db->line[i]))
		++i;
	temp->y = ft_atoi(db->line + i);


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

	if (db->rooms == NULL)
		db->rooms = temp;

	if (db->rooms->start)
		temp->start=db->rooms->start;
	else if (db->start == 2)
		ft_link_start(db, temp->start);

	if (db->rooms->end)
		temp->end = db->rooms->end;
	else if (db->end == 2 && db->start == 2)
		ft_link_end(db, temp->end);
}
