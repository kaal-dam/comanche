#include "signals.h"
#include <sys/wait.h>
#include <stdio.h>

/*Si process pere recoit le signal SIGCHLD il termine son fils pour que celui ci ne reste pas zombie*/
void traitement_signal(){
    int status;
    if(waitpid(-1, &status, WNOHANG)==-1){
        perror("waitpid");
    }
}

/*Fonction qui sert au serveur a ignorer les SIGPIPE et a ne pas laisser de processus zombies*/
void initialiser_signaux(){
    if(signal(SIGPIPE, SIG_IGN)==SIG_ERR){
        perror("signal");
    }
    struct sigaction sa;
    sa.sa_handler=traitement_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=(SA_RESTART);
    /*Si on recoit un signal SIGCHLD*/
    if(sigaction(SIGCHLD, &sa, NULL)==-1){
        perror("sigaction(SIGCHLD)");
    }
}
