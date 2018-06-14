/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:01:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/14 13:00:34 by ozalisky         ###   ########.fr       */
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

void	ft_savelink(t_db *db)
{
	int i;
	int j;
	int length;
	char *source_name;
	char *target_name;
	t_r *source;
	t_r *target;

	t_l *prev_link;

	length = 0;
	i = 0;
	j = 0;



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
	i = i - length;
	target_name = ft_memalloc(sizeof(char*) * (length + 1));
	j = 0;
	while (j < length)
	{
		target_name[j++] = db->line[i++];
	}
	target_name[j] = '\0';

	source = db->rooms->start;
	while (source && ft_strcmp(source_name, source->name))
	{
		source = source->next_room;
	}

	target = db->rooms->start;
	while (target && ft_strcmp(target_name, target->name))
	{
		target = target->next_room;
	}

	if (target && source)
	{
		prev_link = source->links;
		while (prev_link != NULL)
		{
			prev_link = prev_link->next_link;
		}
		prev_link = ft_memalloc(sizeof(t_l));
//	prev_link = source->links;

		prev_link->room = target;
		prev_link->connected = 0;
		prev_link->next_link = NULL;

		if (source->links == NULL)
		{
			source->links = prev_link;
		}
		else if (source->links->next_link == NULL)
		{
			source->links->next_link = prev_link;
		}
	}
}