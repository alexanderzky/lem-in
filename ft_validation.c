/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:39:18 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/20 16:23:01 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_validate(t_db *db)
{
	if (db->ants < 1 || db->ants > 2147483647)
	{
		ft_printf("ERROR ants\n");
		exit(0);
	}
	if (!db->rooms)
	{
		ft_printf("ERROR rooms\n");
		exit(0);
	}
	if (!db->rooms_flag || !db->links_flag || db->error)
	{
		ft_printf("ERROR rooms || links || error\n");
		exit(0);
	}
	ft_check_rooms(db);
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

void	ft_check_way(t_db *db)
{
	t_r		*temp;
	size_t	index;

	index = 0;
	temp = db->rooms->start;
	while (index < temp->links_size)
	{
		if (temp->links[index]->step != 2147483647)
		{
			return ;
		}
		index++;
	}
	ft_printf("ERROR no way\n");
	exit(0);
}

int		ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (ft_atoi(str) < 0 || ft_atoi(str) > 2147483647)
		return (0);
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

char	*ft_strcpysrc(const char *src)
{
	int		i;
	char	*dst;

	dst = ft_memalloc(sizeof(char*) * (ft_strlen(src) + 1));
	i = 0;
	while (src[i] ^ '\0')
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}
