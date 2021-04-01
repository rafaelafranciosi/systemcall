#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
	FILE *ptr;
    struct stat st;
    struct rusage me;
    char command[50];

    // Crie um programa que recebe o nome de um arquivo texto na linha de comando.
    if (argc != 2) {
        printf("Quantidade de parametros invalidos.");
		exit(1);
    }
    
	ptr = fopen(argv[1], "r");
	
    if (ptr==NULL) {
		printf("Arquivo nao existe.");
		exit(1);
	}

    /*  Deve-se mostrar o nome do arquivo, juntamente com as permissões que o processo atual 
        (que está sendo executado) possui do arquivo texto.
        Deve ser mostrado se o processo pode ler ou escrever no arquivo.*/
	
    if(access( argv[1], R_OK ) == 0 ) { 
		syscall(SYS_write, 1, "O ARQUIVO PODE SER LIDO", 23); 
        printf("\n");
	}
	if(access( argv[1], W_OK ) == 0 ) { 
		syscall(SYS_write, 1, "O ARQUIVO PODE SER ESCRITO", 26);
        printf("\n");
	}

    /* Mostrar em seguida o tipo do arquivo. Para mostrar o tipo do arquivo deve-se utilizar o comando "file". USAR SYSTE */ 

    strcpy (command, "file -i " );
    strcat(command, argv[1] );
    system(command);

    /* Mostrar o ID e o group ID do arquivo, juntamente com seu tamanho total em bytes, quando foi modificado e quando 
        foi acessado pela última vez.*/

    if (stat(argv[1], &st) == 0) {
        printf("\tID = %ld\n", st.st_dev);
        printf("\tID do Grupo = %d\n", st.st_gid);
        printf("\tTamanho: %ld bytes\n", st.st_size);
        printf("\tUltima Modificacao = %ld\n", st.st_mtime);
        printf("\tUltimo Acesso = %ld\n\n\n", st.st_atime);
    }

    /* Mostrar o PID do processo sendo executado e do pai do processo sendo executado. */
    printf("\tPID do Processo = %d\n", getpid());
    printf("\tPID do Processo Pai = %d\n", getppid());
    
    /* Criar uma função que mostre na saída padrão o conteúdo do arquivo. 
       Para tanto, deve-se utilizar as system calls open, read e write. */

    int fd;
    fd = open(argv[1], O_RDONLY);

    if(fd < 0) {
        printf("Não foi possvel abrir arquivo.\n");
        perror("open");
        return 1;
    }
    else  {
        char content[st.st_size];   
        read(fd, content, sizeof(content));
        write(1, content, sizeof(content));
    }    

    /* Mostrar ainda algumas informações de recursos consumidos pelo processo: uso da CPU em modo usuário, uso da CPU 
    em modo sistema, memória usada pelo processo (total), memória usada para dados e memória utilizada para pilha. */

    if (getrusage(RUSAGE_SELF, &me) == -1 ){
        perror("getrusage()");
        exit(0);
    }

    /*
        No conseguimos mostrar em tela, pois nao temos pratica com C e nao sei qual seria o formato adequado para mostrar.

        printf("Uso em modo usuário: %ld\n",me.ru_utime);
        printf("Uso em modo Sistema: %d\n",me.ru_stime);
        echo (me.ru_utime); 
        echo (me.ru_stime); 
        echo (me.ru_ixrss);
     */

}

