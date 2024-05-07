#include "libft.h"

//main de test de random sur une sequence de 10000 nombres
//pourcentage de doublons estime : 99.995%

int main()
{
	int i;
	int	seed;
	int	j;
	int doublons;
	int	count;
	int	len;
	long long int	*result;

	i = 0;
	len = 10000;
	seed = ft_random_seed(0);
	result = malloc(sizeof(int) * len);
	while (i < len)
	{
		j = 0;
		result[i] = ft_random(seed, len, 0);
		seed = ft_random_seed(seed);
		ft_printf("Result : ==%d==\n____________\n", result[i]);
		while (j != i)
		{
			if (result[j] == result[i])
			{
				doublons++;
				break;
			}
			j++;
		}
		i++;
	}
	i = 0;
	ft_printf("\nDoublons : %d\n", doublons);
	j = 0;
	while (j < len)
	{
		count = 0;
		i = 0;
		while(i < len)
		{
			if (result[i] == j)
				count++;
			i++;
		}
		if (count)
			ft_printf("Caractere %d : %d fois\n", j, count);
		j++;
	}
	return(0);
}