# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

void	child_signal_handler(int signal)
{
	(void)signal;
}

int	init_child_signal(struct sigaction *sa)
{
	sa->sa_handler = child_signal_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}

int	main()
{
	struct sigaction	sa;

	if (!init_child_signal(&sa))
		return (1);
	while (1)
	{
		(void)sa;
	}
	return (0);
}
