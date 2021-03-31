#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *ptr;
	char nomeArquivo[20];
    struct stat st;
    
    // Crie um programa que recebe o nome de um arquivo texto na linha de comando.
    printf("Informe o nome de um Arquivo existente.\n");
	scanf("%s", nomeArquivo);
	ptr = fopen(nomeArquivo, "r");
	
    if (ptr==NULL) {
		printf("Arquivo nao existe.");
		exit(1);
	}

    /*  Deve-se mostrar o nome do arquivo, juntamente com as permissões que o processo atual 
        (que está sendo executado) possui do arquivo texto.
        Deve ser mostrado se o processo pode ler ou escrever no arquivo.*/
	
    if(access( nomeArquivo, R_OK ) == 0 ) { 
		syscall(SYS_write, 1, "O ARQUIVO PODE SER LIDO", 23); 
        printf("\n");
	}
	if(access( nomeArquivo, W_OK ) == 0 ) { 
		syscall(SYS_write, 1, "O ARQUIVO PODE SER ESCRITO", 26);
        printf("\n");
	}

    /* Mostrar em seguida o tipo do arquivo. Para mostrar o tipo do arquivo deve-se utilizar o comando "file".*/

    /* Mostrar o ID e o group ID do arquivo, juntamente com seu tamanho total em bytes, quando foi modificado e quando 
        foi acessado pela última vez.*/

    if (stat(nomeArquivo, &st) == 0) {
        printf("\tID = %ld\n", st.st_dev);
        printf("\tID do Grupo = %d\n", st.st_gid);
        printf("\tTamanho: %ld bytes\n", st.st_size);
        printf("\tUltima Modificacao = %ld\n", st.st_mtime);
        printf("\tUltimo Acesso = %ld\n\n\n", st.st_atime);
    }

    /* Mostrar o PID do processo sendo executado e do pai do processo sendo executado. */

    printf("\tPID do Processo = %d\n", getpid());
    printf("\tPID do Processo Pai = %d\n", getppid());
    
}

/* Mostrar ainda algumas informações de recursos consumidos pelo processo: uso da CPU em modo usuário, uso da CPU 
em modo sistema, memória usada pelo processo (total), memória usada para dados e memória utilizada para pilha. */
