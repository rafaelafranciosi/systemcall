/* Crie um programa que recebe o nome de um arquivo texto na linha de comando. Caso não 
seja passado a quantidade correta de argumentos o programa deve encerrar sua execução, 
mostrando uma mensagem adequada. Caso o arquivo não exista, o programa deve mostrar uma 
mensagem e encerrar sua execução.

* Deve-se mostrar o nome do arquivo, juntamente com as permissões que o processo atual 
(que está sendo executado) possui do arquivo texto. 
* Deve ser mostrado se o processo pode ler ou escrever no arquivo.
* Mostrar em seguida o tipo do arquivo. Para mostrar o tipo do arquivo deve-se utilizar o comando "file".
* Mostrar o ID e o group ID do arquivo, juntamente com seu tamanho total em bytes, quando foi modificado e quando 
foi acessado pela última vez.
* Criar uma função que mostre na saída padrão o conteúdo do arquivo. Para tanto, deve-se utilizar as system calls 
open, read e write. 
* Mostrar o PID do processo sendo executado e do pai do processo sendo executado. 
* Mostrar ainda algumas informações de recursos consumidos pelo processo: uso da CPU em modo usuário, uso da CPU 
em modo sistema, memória usada pelo processo (total), memória usada para dados e memória utilizada para pilha.*/


#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv){
	int s;
    char *msgErroExec = "\nErro de execução\n\nUSO: exec <name>\nexec: nome do binario\n<name>: nome do diretorio a criar na pasta /tmp/\n";
    char *sucesso = "Diretorio cirado\nConferir ...\n";
    char msgErroCria[100]; 
    char *base = "/tmp/";
    char diretorio[100];
	
	if (argc != 2){
        write(1, msgErroExec, strlen(msgErroExec));
        return(1);
    }
    strcat(diretorio, base);
    strcat(diretorio, argv[1]);

    s = mkdir(diretorio, 0777);
    if (!s)
        syscall(SYS_write, 1, sucesso, strlen(sucesso));
    else{
        sprintf(msgErroCria, "Problema ao criar diretorio. Retorno %d\n",s);
        syscall(SYS_write, 1, msgErroCria, strlen(msgErroCria));
    }   

	return 0;
}


/*Como verificar se o arquivo existe e as permissões de leitura, escrita e execução*/
int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}



/*Mostrar o ID e o group ID do arquivo, juntamente com seu tamanho total em bytes, 
quando foi modificado e quando foi acessado pela última vez.*/

#include <stdio.h>

int main (int argc, char *argv[])
{
int i, t;
FILE *arq;

if (argc < 2){
fprintf(stderr, "ERRO: faltou parametro\n");
return(1);
}

for (i = 1; i< argc; i++){
if (! (arq = fopen(argv[i],"r"))){
fprintf(stderr, "ERRO ao tentar abrir %s\n", argv[i]);
continue;
}
fseek (arq, 0, SEEK_END);
t = ftell (arq);
fclose(arq);
printf("===> %s\n", argv[i]);
printf("\tTamanho = %i\n", t);
}
}

    /* */
