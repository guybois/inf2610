#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_SIZE 100

int fd[2];  // Pipe (fd[0] = lecture, fd[1] = écriture)

void* writer_thread(void* arg) {
    const char* messages[] = {"Message 1", "Message 2", "Message 3", NULL};

    for (int i = 0; messages[i] != NULL; i++) {
        write(fd[1], messages[i], strlen(messages[i]) + 1);  // Écriture dans le pipe
        printf("Écrivain: envoyé -> %s\n", messages[i]);
        sleep(1);  // Simuler un délai entre les envois
    }

    close(fd[1]);  // Fermer l'écriture après l'envoi
    return NULL;
}

void* reader_thread(void* arg) {
    char buffer[BUFFER_SIZE];

    while (1) {
        ssize_t bytesRead = read(fd[0], buffer, BUFFER_SIZE);
        if (bytesRead <= 0) {
            break;  // Fin de lecture si le pipe est fermé
        }
        printf("Lecteur: reçu -> %s\n", buffer);
    }

    close(fd[0]);  // Fermer la lecture après la réception
    return NULL;
}

int main() {
    pthread_t writer, reader;

    if (pipe(fd) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }

    pthread_create(&writer, NULL, writer_thread, NULL);
    pthread_create(&reader, NULL, reader_thread, NULL);

    pthread_join(writer, NULL);
    pthread_join(reader, NULL);

    return 0;
}



