#include "../inc/minishell.h"

t_quote	*ft_quoter_maker(char *new_command, t_quote *list, char delimiter, int i)
{
	t_quote	*quote;
	t_quote	*next;
	int     n;

	quote = malloc(sizeof(t_quote));
	n = 0;
	while(new_command[n + i] && new_command[n + i] != delimiter)
		n++;
	quote->quoted = malloc(sizeof(char) * n + 1);
	ft_strlcpy(quote->quoted, new_command + i, n + 1);
	quote->n[0] = i - 1;
	quote->n[1] = i + n;
	quote->used = 0;
	quote->next = NULL;
	quote->head = 1;
	if (list->used == -1)
		return (quote);
	next = list;
	while (next->next)
		next = next->next;
	next->head = 0;
	next->next = quote;
	return (list);
}

t_quote	*ft_quoter(char *new_command, t_quote *quote)
{
	char	c;
	int		i;

	i = 0;
	while (new_command[i])
	{
		while (new_command[i] != 34 && new_command[i] != 39 && new_command[i])
			i++;
		c = new_command[i];
		if (c == '\0')
			return (quote);
		quote = ft_quoter_maker(new_command, quote, c, i + 1);
		i++;
		while (new_command[i] != c && new_command[i])
			i++;
		if (new_command[i])
			i++;
	}
	return (quote);
}
