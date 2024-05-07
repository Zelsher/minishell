/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:05:56 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/29 18:05:56 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static long long int	ft_seeder(char *time)
{
	int					i;
	long long int		num;

	i = 1;
	while (time[i - 1] != '.')
		i++;
	num = ft_atoi(time + i);
	if (time[i] != '0' || time[i + 1] != '0')
		num *= ft_power(ft_atoi(time + i), 2);
	while (time[i] != '.')
		i++;
	if (time[i + 1] == '0' && time[i + 2] == '0')
	{
		i -= 2;
		while (time[i + 1] == 0)
			i--;
		num *= ft_power(ft_atoi(time + i), 2);
	}
	else
		num *= ft_power(ft_atoi(time + i + 1), 2);
	return (num);
}

static int	ft_seed_len(long long int seed)
{
	long long int	temp;
	int				moove;
	int				i;

	i = 1;
	if (seed < 0)
		seed = seed * -1;
	temp = seed;
	while (temp >= 10)
	{
		i++;
		temp /= 10;
	}
	moove = i - (ft_nbr_reducer(seed, 1));
	if (moove < 5)
		moove = 5;
	seed = (ft_nbr_reducer(seed, moove));
	while (seed > 65536)
		seed /= 10;
	return ((int)seed);
}

int	ft_random_seed(long long int seed)
{
	int		fd;
	char	*time;

	if (seed < 0)
		seed *= -1;
	if (seed == 0)
	{
		fd = open("/proc/uptime", O_RDONLY);
		if (fd == 0)
		{
			ft_printf("Erreur ft_random, verifier /proc/uptime");
			return (0);
		}
		time = get_next_line(fd);
		close(fd);
		seed = ft_seed_len(ft_seeder(time));
		free(time);
	}
	else
	{
		seed = (1664525 * seed + 1013904223) % 4294967296;
		seed = ft_seed_len(seed);
	}
	return (seed);
}

#include <stdio.h>

long long int	ft_randomizer(long long int seed, long long int num, long long int max, int sign)
{
	long long int	len;
	int				temp;

	len =  ft_nbr_max_pos(max);
	temp = 0;
	while (num >= max)
	{
		seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
		temp = (temp << 3) | (seed % 8);
		temp = ft_nbr_reducer(temp, 1);
		if (len != 1)
			num += - ((num / len) * len) + (temp * len);
		else
			num = temp;
	}
	seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
	temp = (temp << 3) | (seed % 8);
	temp = ft_nbr_reducer(temp, 1);
	if (sign && (temp != 0 && temp < 5))
		num *= -1;
	return (num);
}

long long int	ft_random(int seed, long long int max, int sign)
{
	long long int	num;
	int				len;

	if (max == 0)
		return (0);
	len = ft_nbrlen(max);
	num = (1664525 * seed + 1013904223) % 4294967296;
	num = ft_nbr_reducer(num, len);
	num = ft_randomizer(seed , num, max, sign);
	return (num);
}
