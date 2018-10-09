/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:01:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/06 17:17:29 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	ft_check_links(t_db *db)
{
	if (db->end ^ 2 || db->start ^ 2)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	if (db->rooms->start->links_size == 0 || db->rooms->end->links_size == 0)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
}

int		ft_islink(char *str)
{
	int i;
	int minus;
	int names;
	int wrong;

	wrong = 0;
	names = 0;
	minus = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] ^ 'L' && str[i] ^ '#' && str[i] ^ ' ' && str[i] ^ '-')
		{
			++names;
			while (i < ft_strlen(str) && str[i + 1] ^ '-')
				++i;
		}
		else if (str[i] == '-')
			++minus;
		else
			++wrong;
		++i;
	}
	if (names == 2 && minus == 1 && wrong == 0)
		return (1);
	return (0);
}

void	ft_count_room_mentions(t_db *db)
{
	int i;
	int j;
	int length;
	char *source_name;
	char *target_name;
	t_r *source;
	t_r *target;

//	t_l *tmp_link;
//	t_r *next_link;
//	t_l *prev_link;

	length = 0;
	i = 0;
	j = 0;


	//find source room name
	while (db->line[i++] ^ '-')
	{
		++length;
	}
	source_name = ft_memalloc(sizeof(char*) * (length + 1));
	i = 0;
	while (j < length)
	{
		source_name[j++] = db->line[i++];
	}
	source_name[j] = '\0';
	length = 0;
	while (++i < ft_strlen(db->line))
	{
		++length;
	}


	//find target room name
	i = i - length;
	target_name = ft_memalloc(sizeof(char*) * (length + 1));
	j = 0;
	while (j < length)
	{
		target_name[j++] = db->line[i++];
	}
	target_name[j] = '\0';

	//find source room
	source = db->rooms;
	while (source && ft_strcmp(source_name, source->name))
	{
		source = source->next_room;
	}
	//change links size to know how much memory to malloc
	if (!ft_strcmp(source_name, source->name))
	{
		++source->links_size;
	}
	//find target room
	target = db->rooms;
	while (target != NULL && ft_strcmp(target_name, target->name))
	{
		target = target->next_room;
	}
	//change links size to know how much memory to malloc
	if (!ft_strcmp(target_name, target->name))
	{
		++target->links_size;
	}
}

void	ft_link_rooms(t_db *db)
{
	int i;
	int j;
	int length;
	char *source_name;
	char *target_name;
	t_r *source;
	t_r *target;

	length = 0;
	i = 0;
	j = 0;

	while (db->line[i++] ^ '-')
	{
		++length;
	}
	source_name = malloc(sizeof(char*) * (length + 1));
	i = 0;
	while (j < length)
	{
		source_name[j++] = db->line[i++];
	}
	source_name[j] = '\0';
	length = 0;
	while (++i < ft_strlen(db->line))
	{
		++length;
	}

	//find target room name
	i = i - length;
	target_name = malloc(sizeof(char*) * (length + 1));
	j = 0;
	while (j < length)
	{
		target_name[j++] = db->line[i++];
	}
	target_name[j] = '\0';

	//find source room
	source = db->rooms->start;
	while (source && ft_strcmp(source_name, source->name))
	{
		source = source->next_room;
	}
	//find target room
	target = db->rooms->start;
	while (target != NULL && ft_strcmp(target_name, target->name))
	{
		target = target->next_room;
	}

	if (target && source)
	{
		if (!source->links)
		{
			source->links = malloc(sizeof(struct s_room) *
													(source->links_size));
			ft_bzero(source->links, sizeof(struct s_room));
		}

		source->links[source->link_slot++] = target;
	}

	if (target && source)
	{
		if (!target->links)
		{
			target->links = malloc(sizeof(struct s_room) *
					(target->links_size));
			ft_bzero(target->links, sizeof(struct s_room));
		}

		target->links[target->link_slot++] = source;
	}


}