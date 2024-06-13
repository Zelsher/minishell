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

void mshell_signal_handler(int signal)
{
    printf("parent %d reçoit %d\n", getpid(), signal);
}

void child_signal_handler(int signal)
{
    printf("enfant %d reçoit %d\n", getpid(), signal);
    // Ignore the signal
    if (signal == SIGINT)
    {
        printf("enfant %d ignore SIGINT\n", getpid());
    }
}

int init_signal(int mod)
{
    struct sigaction sa;

    if (mod == 0)
    {
        sa.sa_handler = mshell_signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
    }
    else if (mod == 1)
    {
        sa.sa_handler = child_signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
    }
    if (sigaction(SIGINT, &sa, NULL) == -1)
        return (0);
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        return (0);
    return (1);
}

int main()
{
    int verif;
    int pid[2];
    char **a;

    a = malloc(sizeof(char *) * 2);
    a[0] = NULL;
    init_signal(0);
    pid[0] = fork();
    if (pid[0] == 0)
    {
        init_signal(1);  // Configurer le gestionnaire de signaux pour l'enfant
        while (1)
            pause();  // Utiliser pause() pour attendre les signaux
        execve("./minishell", a, a);  // Cette ligne ne sera jamais atteinte
    }
    printf("pid principal : %d\npid enfant : %d\n", getpid(), pid[0]);
	//signal()
    while (1)
    {
        // Attendre que le processus enfant se termine
        if (waitpid(pid[0], &verif, 0) == -1)
        {
            if (errno == EINTR)
                continue;  // Si interrompu par un signal, continuer la boucle
            else
                break;  // Sinon, sortir de la boucle
        }
        else
            break;  // Le processus enfant est terminé
    }
    printf("Fini\n");
    free(a);
}
