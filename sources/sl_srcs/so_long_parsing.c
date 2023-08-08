/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:16:24 by mapfenni          #+#    #+#             */
/*   Updated: 2023/06/07 18:53:43 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	arg_parsing(int ac, char **av, t_data *data)
{
	if (ac > 2 || ac < 2)
	{
		ft_printf("Error\n");
		ft_printf("Launch with the name of the map file as only argument\n");
		return (1);
	}
	if (ac == 2)
	{
		ft_printf("Checking map...\n", av[1]);
		return (check_map(av[1], data));
	}
	return (0);
}

char	**ft_copy_map(char **map)
{
	int		y;
	char	**new_map;

	y = 0;
	new_map = malloc(sizeof(char *) * (ft_tablen(map) + 1));
	while (map && map[y])
	{
		new_map[y] = ft_strdup(map[y]);
		y++;
	}
	new_map[y] = NULL;
	return (new_map);
}

int	check_map(char *name, t_data *data)
{
	int		i;
	int		n;
	char	*str;

	str = ".ber";
	i = ft_strlen(name);
	n = 4;
	while (n--)
	{
		if (name[i - 1] != str[n])
			return (ft_printf("Error\nWrong map format, please use '.ber'"));
		i--;
	}
	data->map = ft_split_read(name);
	if (data->map)
		data->copy_map = ft_copy_map(data->map);
	if (data->map == NULL || check_walls(data->map))
		return (1);
	if (check_cep(data->map, data, 0, -1))
		return (1);
	if (flood_fill(data))
		return (1);
	ft_printf("Starting game !\n");
	return (0);
}

int	check_walls(char **tab)
{
	int	x;
	int	y;

	y = 0;
	x = ft_strlen(tab[0]);
	while (tab[y] != NULL)
	{
		if (x != ft_strlen(tab[y]))
			return (ft_printf("Error\nPlease use a rectangular map"));
		y++;
	}
	while (x--)
	{
		if (tab[0][x] != '1' || tab[ft_tablen(tab) - 1][x] != '1')
			return (ft_printf("Error\nMap is missing walls"));
	}
	while (y--)
	{
		if (tab[y][0] != '1' || tab[y][ft_strlen(tab[y]) - 1] != '1')
			return (ft_printf("Error\nMap is missing walls"));
	}
	return (0);
}

int	check_cep(char **tab, t_data *data, int i, int y)
{
	int	e;
	int	p;

	e = 0;
	p = 0;
	while (tab[++y] != NULL)
	{
		i = -1;
		while (tab[y][++i] != '\0')
		{
			if (tab[y][i] == 'E')
				e++;
			else if (tab[y][i] == 'C')
				data->items++;
			else if (tab[y][i] == 'P' && ++p)
			{
				data->play_x = i;
				data->play_y = y;
				tab[y][i] = '0';
			}
			else if (!is_ecp(tab[y][i]))
				return (ft_printf("Error\nUnknown element in map"));
		}
	}
	return (ecp_values(e, data->items, p));
}
