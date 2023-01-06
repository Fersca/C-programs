#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG 10
#define TAM_MAX 100  

int main(int arvec, char * argv[])
	{
	/* Definicin de Variables */
	int mi_socket, nuevo_socket, sin_size, restbind, restlisten, restaccept;
	int bytesrec,bytesenv,mi_puerto; 
	char miip[20];
	char buffer[TAM_MAX];
	char texto[]="GNUTELLA OK\n\n";
	struct sockaddr_in mi_dir;
	struct sockaddr_in dest_dir;
	
	/* Validacion de datos de entrada */
	if(arvec!=3)
	    {
	    printf("\nSe Tomaran los valores por default, IP: 127.0.0.1 Puerto: 3002\n");
	    strcpy(miip,"127.0.0.1");
	    mi_puerto=3002;
	    }
	else
	    {
	    strcpy(miip,argv[1]);
	    mi_puerto=atoi(argv[2]);
	    }
	
	/* Programa principal */
	mi_socket=socket(AF_INET, SOCK_STREAM, 0);
	printf("\nSocket numero: %d",mi_socket);

	/* Estableciendo parametros de mi socket */
	mi_dir.sin_family=AF_INET;
	mi_dir.sin_port=htons(mi_puerto);
	mi_dir.sin_addr.s_addr=inet_addr(miip);
	memset(&(mi_dir.sin_zero),'\0',8);
	
	/* Haciendo Binding */
	restbind=bind(mi_socket,(struct sockaddr *)&mi_dir, sizeof(struct sockaddr));
	printf("\nResultado Binding: %d", restbind);
	
	/* Haciendo listening */
	restlisten=listen(mi_socket, BACKLOG);
	printf("\nResultado Listen: %d",restlisten);
	sin_size=sizeof(struct sockaddr_in);
	
	/* Aceptando conexiones nuevas */
	nuevo_socket=accept(mi_socket, (struct sockaddr *)&dest_dir, &sin_size);
	printf("\nNuevo Socket: %d", nuevo_socket);
	
	/* Reciviendo datos */
	bytesrec=recv(nuevo_socket,buffer, TAM_MAX-1,0);
	printf("\nDatos Recividos: %d",bytesrec);
	buffer[bytesrec]='\0';
	printf("\nInformacion Recivida: %s",buffer);
		
	/* Enviando datos de respuesta */
	
	if(strcmp(buffer,"GNUTELLA CONNECT/0.4\n\n")==0)
	    {
	    bytesenv=send(nuevo_socket,texto,strlen(texto),0);
	    printf("\nConfirmacin enviada: %d",bytesenv);
	    }
	
	/* Cerrando sockets */
	close(nuevo_socket);
	close(mi_socket);
	printf("\n");
	return 0;
	}



