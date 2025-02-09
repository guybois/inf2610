Continuité de l'exemple 2 de la page 17. On montre ici comment un thread du programme principal peut cancellé un thread  fils avec
pthread_cancel(th); et comment le fils peut s'en protégé avec pthread_setcancelstate(int state, int *oldstate) (p. 24)  
