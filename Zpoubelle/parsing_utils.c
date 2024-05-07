#include "../inc/minishell.h"

int ft_verifier(char *new_command)
{
    //int i;

    //while (new_command[i])
    //{
    //    while (new_command[i])
    //}
    (void)new_command;
    return (1);
}

char    *ft_commander(char *new_command, t_quote *quote, t_command *list)
{
    char    *command;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (new_command[i] == ' ')
        i++;
    while (new_command[i + j] && new_command[i + j] != ' ' && new_command[i] != 34 && new_command[i] != 39)
        j++;
    if (j == 0)
    {
        list->index += i;
        return (NULL);
    }
    command = malloc(sizeof(char) * j + 1);
    if (!command)
        return (NULL);
    ft_strlcpy(command, new_command + i, j + 1);
    while (new_command[i + j] && new_command[i + j] == ' ')
        j++;
    list->index += j + i;
    (void)quote;
    return (command);
}

char    *ft_optioner(char *new_command, t_quote *quote, t_command *list)
{
    char    *options;
    int i;
    int j;

    i = 0;
    j = 0;
    while (new_command[i] == ' ')
        i++;
    while (new_command[i + j] == '-' || new_command[i + j] == ' ')
    {
        while (new_command[i + j] == '-')
            j++;
        while (new_command[i + j] != ' ' && new_command[i + j] != 34 && new_command[i + j] != 39)
            j++;
        while (new_command[i + j] == ' ')
            j++;
    }
    list->index += j + i;
    if (j == 0)
        return (NULL);
    options = malloc(sizeof(char) * j + 1);
    if (!options)
        return (NULL);
    ft_strlcpy(options, new_command + i, j);
    (void)quote;
    return (options);
}

char    *ft_filer(char *new_command, t_quote *quote, t_command *list)
{
    char    *file;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (new_command[i] == ' ')
        i++;
    while (new_command[i + j] && new_command[i + j] != ' ' && new_command[i + j] != '|' 
        && new_command[i + j] != '&' && new_command[i + j] != '>' && new_command[i + j] != '<'
        && new_command[i + j] != 34 && new_command[i + j] != 39)
        j++;
    if (j == 0)
    {
        list->index += i;
        return (NULL);
    }
    file = malloc(sizeof(char) * j + 1);
    if (!file)
        return (NULL);
    ft_strlcpy(file, new_command + i, j + 1);
    while (new_command[i + j] && new_command[i + j] == ' ' && new_command[i + j] != 34 && new_command[i + j] != 39)
        j++;
    list->index += j + i;
    (void)quote;
    return (file);
}

char    *ft_operatoror(char *new_command, t_quote *quote, t_command *list)
{
    char *operator;
    int i;
    int j;

    i = 0;
    j = 0;
    while (new_command[i] && new_command[i] == ' ')
        i++;
    while (new_command[i + j] && (new_command[i + j] == '|' || new_command[i + j] == '&' 
    || new_command[i + j] == '>' || new_command[i + j] == '<' || new_command[i + j] == ';'))
        j++;
    if (j == 0)
    {
        list->index += i;
        return (NULL);
    }
    operator = malloc(sizeof(char) * j + 1);
    ft_strlcpy(operator, new_command + i, j + 1);
    while (new_command[i + j] && new_command[i + j] == ' ')
        j++;
    list->index += j + i;
    (void)quote;
    return (operator);
}

int	ft_optioner(t_word *word, t_command *command)
{
	int	i;

	i = 0;
	while ((word->word[i + 1] || word->quote[i + 1]))
	{
		if ((word->word[i + 1] && word->word[i + 1][0] != '-') ||
			(word->quote[i + 1] && word->quote[i + 1][0] != '-'))
			break;
		if (i == 51)//trop d'option, le parsing doit return une erreur alors on met command a NULL;
		{
			command->cmd = NULL;
			break;
		}
		if (word->word[i + 1])
			command->opt[i] = word->word[i + 1];
		else
			command->opt[i] = word->quote[i + 1];
		command->opt[i + 1] = NULL;
		i++;
	}
	return (i);
}

void	ft_filer(t_word *word, t_command *command, int i)
{
	int	j;

	j = 0;
	while ((word->word[i + 1] || word->quote[i + 1]))
	{
		if (j == 51)//trop de file, le parsing doit return une erreur alors on met command a NULL;
		{
			command->cmd = NULL;
			ft_printf("oui");
			break;
		}
		if (word->word[i + 1])
			command->file[j] = word->word[i + 1];
		else
			command->file[j] = word->quote[i + 1];
		command->opt[i + 1] = NULL;
		i++;
		j++;
	}
}