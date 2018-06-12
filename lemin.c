/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/12 13:02:41 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> //delete


#include "lemin.h"

void	ft_validate(t_db *db)
{

}

void	ft_comments(t_db *db)
{
	if (ft_strcmp(db->line, "##start") == 0)
	{
		db->start = 1;
	}
	else if (ft_strcmp(db->line, "##end") == 0)
	{
		db->end = 1;
	}
}

int		ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			++i;
		}
		else
			return (0);

	}
	return (1);
}

void	ft_operate(t_db *db)
{

}

char	*ft_strcpysrc(const char *src)
{
	int i;
	char *dst;

	dst = ft_memalloc(sizeof(char*) * (ft_strlen(src) + 1));
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_lineconcatmap(t_db *db)
{
	char	*str;
	long	size_map;
	long	size_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size_line = ft_strlen(db->line);
	size_map = ft_strlen(db->map);

	if (!(str = (char*)ft_memalloc(sizeof(char*) * (size_line + size_map + 1))))
		db->error = 1;
	while (db->map != NULL && db->map[i])
	{
		str[j++] = db->map[i++];
	}
	if (db->map != NULL)
	{
		free(db->map);
		db->map = NULL;
	}
	if (size_map != 0)
	{
		str[j++] = '\n';
	}
	i = 0;
	while (db->line[i])
	{
		str[j++] = db->line[i++];
	}
	str[j] = '\0';
	db->map = ft_strcpysrc(str);
	free(str);
	str = NULL;
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
	else if (!temp->position)
	{
		temp->start = temp->prev_room->start;
	}
	temp->next_room = NULL;
	if (db->rooms == NULL)
	{
		db->rooms = temp->start;
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
		if (str[i] != 'L' && str[i] != '#' && str[i] != ' ' && str[i] != '-')
		{
			++names;
			while (i < ft_strlen(str) && str[i + 1] != '-')
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



	while (db->line[i++] != '-')
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





	/*search source_name through s_room names */


}

void	ft_check_line(t_db *db)
{
	if (db->ants < 1 && ft_isnumber(db->line))
		db->ants = ft_atoi(db->line);
	else if (db->line[0] == '#' && db->line[1] == '#')
	{
		ft_comments(db);
	}
	else if (ft_isroom(db->line))
	{
		ft_saveroom(db);
	}
	else if (ft_islink(db->line))
	{
		ft_savelink(db);
	}
	else
		db->error = 1;
	ft_lineconcatmap(db);
	free(db->line);
	db->line = NULL;
}

void	ft_init(t_db *db)
{
	db->map = NULL;
	db->ants = 0;
	db->start = 0;
	db->end = 0;
	db->error = 0;
	db->rooms = NULL;
	db->links = NULL;

}

int		main(void)
{
	t_db	db;

	ft_init(&db);
	db.fd = open("../maps", O_RDONLY);
	while (!db.error && ((get_next_line(db.fd, &db.line) > 0)))
	{
		if (db.line[0] == '\0')
			break ;
		ft_check_line(&db);
	}
	free(db.line);
	ft_validate(&db);
	ft_operate(&db);
	ft_printf("%s",db.map);
	close(db.fd);
	exit(0);
}