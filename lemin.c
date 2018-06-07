/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/07 20:22:05 by ozalisky         ###   ########.fr       */
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
			i++;
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
		i++;
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
//	db->map = str;
	free(str);
	str = NULL;



}

void	ft_check_line(t_db *db)
{
	if (db->ants < 1 && ft_isnumber(db->line))
		db->ants = ft_atoi(db->line);
	else if (db->line[0] == '#' && db->line[1] == '#')
	{
		ft_comments(db);
	}
//	else if ()
//	{
//
//	}
	ft_lineconcatmap(db);
	free(db->line);
	db->line = NULL;
}

int		main(void)
{
	t_db	db;

	db.map = NULL;
	db.fd = open("../maps", O_RDONLY);
	while(get_next_line(db.fd, &db.line) > 0)
	{

		if (db.line[0] == '\0')
			break ;
		ft_check_line(&db);
//		free(db.line);
	}
	free(db.line);
	ft_validate(&db);
	ft_operate(&db);
	ft_printf("%s",db.map);
	close(db.fd);
	exit(0);
}