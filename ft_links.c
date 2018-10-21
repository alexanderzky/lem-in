/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:01:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/21 16:29:57 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	return (names == 2 && minus == 1 && wrong == 0) ? 1 : 0;
}

void	ft_incrs_mentions(t_db *db, t_r *source, t_r *target)
{
	source = db->rooms;
	while (source && ft_strcmp(db->source_name, source->name))
		source = source->next_room;
	if (source && !ft_strcmp(db->source_name, source->name))
		++source->links_size;
	target = db->rooms;
	while (target != NULL && ft_strcmp(db->target_name, target->name))
		target = target->next_room;
	if (target && !ft_strcmp(db->target_name, target->name))
		++target->links_size;
	free(db->source_name);
	free(db->target_name);
}

void	ft_count_room_mentions(t_db *db)
{
	int		j;
	int		length;

	length = 0;
	db->links_i = 0;
	j = 0;
	while (db->line[db->links_i++] ^ '-')
		++length;
	db->source_name = ft_memalloc(sizeof(char*) * (length + 1));
	db->links_i = 0;
	while (j < length)
		db->source_name[j++] = db->line[db->links_i++];
	db->source_name[j] = '\0';
	length = 0;
	while (++db->links_i < ft_strlen(db->line))
		++length;
	db->links_i = db->links_i - length;
	db->target_name = ft_memalloc(sizeof(char*) * (length + 1));
	j = 0;
	while (j < length)
		db->target_name[j++] = db->line[db->links_i++];
	db->target_name[j] = '\0';
	ft_incrs_mentions(db, NULL, NULL);
}

void	ft_link_it(t_db *db, t_r *source, t_r *target)
{
	while (source && ft_strcmp(db->source_name, source->name))
		source = source->next_room;
	while (target != NULL && ft_strcmp(db->target_name, target->name))
		target = target->next_room;
	if (target && source)
	{
		if (!source->links)
		{
			source->links = malloc(sizeof(t_r) * (source->links_size));
			ft_bzero(source->links, sizeof(struct s_room));
		}
		source->links[source->link_slot++] = target;
	}
	if (target && source)
	{
		if (!target->links)
		{
			target->links = malloc(sizeof(t_r) * (target->links_size));
			ft_bzero(target->links, sizeof(struct s_room));
		}
		target->links[target->link_slot++] = source;
	}
	free(db->source_name);
	free(db->target_name);
}

void	ft_link_rooms(t_db *db)
{
	int		j;
	int		length;

	length = 0;
	db->links_i = 0;
	j = 0;
	while (db->line[db->links_i++] ^ '-')
		++length;
	db->source_name = malloc(sizeof(char*) * (length + 1));
	db->links_i = 0;
	while (j < length)
		db->source_name[j++] = db->line[db->links_i++];
	db->source_name[j] = '\0';
	length = 0;
	while (++db->links_i < ft_strlen(db->line))
		++length;
	db->links_i = db->links_i - length;
	db->target_name = malloc(sizeof(char*) * (length + 1));
	j = 0;
	while (j < length)
		db->target_name[j++] = db->line[db->links_i++];
	db->target_name[j] = '\0';
	ft_link_it(db, db->rooms, db->rooms);
}
