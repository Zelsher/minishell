#include "../inc/minishell.h"

void	fill_command(char *new_command, t_command *command, t_command *list, t_quote *quote)
{
	command->command = ft_commander(new_command + list->index, quote, list);
	if (new_command[list->index] == 34 || new_command[list->index] == 39)
	{
		list->index = quote->n[1] + 1;
		quote->used = 1;
		quote = quote->next;
	}
	command->options = ft_optioner(new_command + list->index, quote, list);
	if (new_command[list->index] == 34 || new_command[list->index] == 39)
	{
		list->index = quote->n[1] + 1;
		quote->used = 1;
		quote = quote->next;
	}
	command->files = ft_filer(new_command + list->index, quote, list);
	if (new_command[list->index] == 34 || new_command[list->index] == 39)
	{
		list->index = quote->n[1] + 1;
		quote->used = 1;
		quote = quote->next;
	}
	command->operator = ft_operatoror(new_command + list->index, quote, list);
	if (new_command[list->index] == 34 || new_command[list->index] == 39)
	{
		list->index = quote->n[1] + 1;
		quote->used = 1;
		quote = quote->next;
	}
}

t_command *new_command_list(char *new_command, t_command *list, t_quote *quote)
{
	t_command *command;
	t_command *next;

	command = malloc(sizeof(t_command));
	fill_command(new_command, command, list, quote);
	command->next = NULL;
	command->head = 1;
	//printf("%scommand :%s\n%soptions :%s\n%sfiles :%s\n%soperator :%s%s\n", TC_CYN, command->command, TC_GRN, command->options, TC_MAG, command->files, TC_YEL, command->operator, TC_NRM);
	if (list->head == -1)
	{
		command->index = list->index;
		return (command);
	}
	next = list;
	while (next->next)
		next = next->next;
	next->head = 0;
	next->next = command;
	return (list);
}

void    list_printer(t_quote *list)
{
    int i;

    i = 1;
    while(list && list->used != -1)
    {
        printf("\n---- ELEMENT %d DE QUOTED ----\nquoted :%s\nused :%d\nhead :%d\nn0 :%d\nn1 :%d\n", i, list->quoted, list->used, list->head, list->n[0], list->n[1]);
        list = list->next;
        i++;
    }
}

void    list_printer2(t_command *list)
{
    int i;

    i = 1;
    while(list)
    {
        printf("\n==== ELEMENT %d DE COMMAND ====\ncommand :%s\nfiles :%s\noptions :%s\noperator :%s\nhead :%d\n", i, list->command, list->files, list->options, list->operator, list->head);
        list = list->next;
        i++;
    }
}

t_command ft_parsing(t_command *command, t_quote *quote, char *new_command)
{
	t_quote *point;
	
	quote->used = -1;
	quote->next = NULL;
	quote = ft_quoter(new_command, quote);
	point = quote;
	command->index = 0;
	command->head = -1;
	while (new_command[command->index] != '\0')
	{
		command = new_command_list(new_command, command, quote);
		while (quote && quote->used == 1)
			quote = quote->next;
	}
	list_printer(point);
	list_printer2(command);
	return (*command);
}

/*    
	command.command = ft_commander(new_command);
	printf("apres command:%s\n", new_command);
	command.options = ft_optioner(new_command);
	printf("apres options:%s\n", new_command);
	command.files = ft_filer(new_command);
	printf("apres files:%s\n", new_command);
	command.operator = ft_operatoror(new_command);
	printf("apres operator:%s\n", new_command);
	printf("command :%s\noptions :%s\nfiles :%s\noperator :%s\n", command.command, command.options, command.files, command.operator);
	command -options --opt fichier ||
*/
