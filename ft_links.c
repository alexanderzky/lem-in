/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:01:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/08/18 18:56:12 by ozalisky         ###   ########.fr       */
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

void		*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	void	*new;

	new = ft_memalloc(newsize);
	ft_bzero(new, sizeof(struct s_room));
	if (ptr)
	{
		ft_memcpy(new, ptr, oldsize);
		free(ptr);
	}
	return (new);
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

//	t_l *tmp_link;
//	t_r *next_link;
//	t_l *prev_link;

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
	while (target != NULL && ft_strcmp(target_name, target->name))
	{
		target = target->next_room;
	}



	if (target && source)
	{
		if (!target->links)
		{
			target->links = (struct s_room**)malloc(sizeof(struct s_room*) * (++target->links_size));
			ft_bzero(target->links, sizeof(struct s_room));
		}
		else
		{
//			target->links = realloc(target->links, target->links_size + 1);
//			target->links = ft_realloc(target->links[0],
//											target->links_size + 1,
//											target->links_size);
			target->links = ft_realloc(target->links, sizeof(struct s_room *) *
													  (target->links_size + 1),
									   sizeof(struct s_room *) *
											   target->links_size);
			++target->links_size;
		}

		target->links[target->links_size - 1] = source;
		db->tempSize = sizeof(target->links);
//		target->links[target->links_size] = NULL;  под вопросом без нала падает в поиске путей с налом не видит линков
	}

	if (target && source)
	{
		if (!source->links)
		{
			source->links = (struct s_room**)malloc(sizeof(struct s_room*) * (++source->links_size));
			ft_bzero(source->links, sizeof(struct s_room));
		}
		else
		{
//			source->links = realloc(source->links, sizeof(struct s_room*) * (source->links_size + 1));
			source->links = ft_realloc(source->links, sizeof(struct s_room *) *
													  (source->links_size + 1),
									   sizeof(struct s_room *) *
									   source->links_size);
			++source->links_size;
		}

		source->links[source->links_size - 1] = target;
		db->tempSize = sizeof(source->links);

//		source->links[source->links_size] = NULL;
	}
}