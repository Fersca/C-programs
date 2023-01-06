#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TAM_MAX 100

int main(int arvec, char * argv[])
	{
	
	/* Definiendo Variables */
	int mi_socket, restconnect, destpuerto, bytesenv,bytesrec;
	char destip[20];
	char buffer[TAM_MAX];
	char mensaje[]="GNUTELLA CONNECT/0.4\n\n";
	struct sockaddr_in dest_dir;
	
	/* Validando datos de entrada */
	if (arvec!=3) 
		{
		printf("\nParametros por default, IP: 127.0.0.1 Port: 3002\n");
		strcpy(destip,"127.0.0.1");
		destpuerto=3002; 
		}
	else
		{
		strcpy(destip,argv[1]);
		destpuerto=atoi(argv[2]);	
		}
	/* Programa principal */
	mi_socket=socket(AF_INET, SOCK_STREAM, 0);
	printf("\nSocket numero: %d",mi_socket);
	
	/* Definiendo parametros del socket de destino */
	dest_dir.sin_family=AF_INET;
	dest_dir.sin_port=htons(destpuerto);
	dest_dir.sin_addr.s_addr=inet_addr(destip);
	memset(&(dest_dir.sin_zero),'\0',8);
	
	/* Estableciendo conexion */
	restconnect=connect(mi_socket,(struct sockaddr*)&dest_dir,sizeof(struct sockaddr));
	printf("\nResultados de la conexion: %d",restconnect);
	
	/* Enviando datos */
	bytesenv=send(mi_socket,mensaje,strlen(mensaje),0);
	printf("\nEnvio de datos exitosos: %d",bytesenv);
	
	/* Recibiendo confirmacion */
	bytesrec=recv(mi_socket,buffer,TAM_MAX-1,0);
	printf("\nSe recivieron datos: %d",bytesrec);
	buffer[bytesrec]='\0';
	printf("\nInformacion recibida: %s",buffer);			
	printf("\n");
	close(mi_socket);
	return 0;
	}


