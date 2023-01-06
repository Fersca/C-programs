#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>
#define CANT_CAR 10
#define MAX 10000



/*********************************
*    PROTOTIPOS DE FUNCIONES     *
*********************************/

int validarAlfabetoDC(char *);
int automata(int *, char *);
int columna(int);
void ayuda(void);
void error(int);
int esNumero(char *);
int Archbin(char tipo, char* file,unsigned n,unsigned c);
int binarioatexto (int t, int cpl, char *ao, char *ad, int lc);
void cBxtTstrings(FILE *, FILE *, int, long [], long, long);
void cBxtTintegers(FILE *, FILE *, int, long [], long);
void cBxtTdoubles(FILE *, FILE *, int, long [], long);
void convertBxToT(char *, char *, char, int, long [], long, long);
int getIntLen(int);
long getCantRegs(FILE *, long);
int texto_aleatorio(char, int, int ,char *, int);
int Textabin(char, char *, char *, unsigned, unsigned);
int entero(char *, int *);
int realdoble(char *, double *);
int columna2(int);
int valor(int);


/************************************************************************/


/********************************
*      PROGRAMA PRINCIPAL       *
********************************/

int main(int argc, char *argv[]) {
	long *v;
	int i, est, car;
	char c[2];

	if (argc<=3) {ayuda(); return 0;}
	if (!validarAlfabetoDC(argv[1])) {error(0); return 0;}
	if (!esNumero(argv[2])) {error(8); return 0;}
	est = automata(&car, argv[1]);
	switch (est) {
		case 5: case 7: case 8: /* "ati" o "atd" */
			if (!esNumero(argv[3])) {error(8); return 0;}
			texto_aleatorio(car, atoi(argv[2]), atoi(argv[3]), argv[4], atoi(&(argv[1])[3]));
			break;
		case 9: case 11: case 12: /* "abi" o "abd" */
			Archbin(car, argv[3], atoi(argv[2]), atoi(&(argv[1])[3]));
			break;
		case 16: case 18: case 19: /* "ctbi" o "ctbd" */
			Textabin(car, argv[3], argv[4], atoi(argv[2]), atoi(&(argv[1])[4]));
			break;
		case 23: case 25: case 26: /* "cbtxi" o "cbtxd" */
			v = (long *) malloc((argc-5)*sizeof(long));
			for (i=5; i<argc; i++) {
				if (!esNumero(argv[i])) {error(8); free(v); return 0;}
				v[i-5] = atol(argv[i]);
			}
			convertBxToT(argv[3], argv[4], car, argc-5, v, atoi(&(argv[1])[5]), atoi(argv[2]));
			free(v);
			break;
		case 27: case 29: case 30: /* "cbtzi" o "cbtzd" */
			binarioatexto(car, atoi(argv[2]), argv[3], argv[4], atoi(&(argv[1])[3]));
			break;
		default: /* "Descripcion Codificada no valida" */
			error(0);
	} /* switch */
	return 0;
} /* main() */


/************************************************************************/


/*********************************
*   DECLARACIONES DE FUNCIONES   *
*********************************/

/*
Funcion que reconoce la descripcion codificada.
Retorna el estado en el que finaliza.
*/
int automata(int *caracter, char *cadena) {
							/*	a, b, c, d, i, s, t, x, z, n */
	int tTrans[][CANT_CAR] = {{ 1,31, 2,31,31,31,31,31,31,31}, /* 0 */
							  {31, 4,31,31,31,31, 3,31,31,31}, /* 1 */
							  {31,14,31,31,31,31,13,31,31,31}, /* 2 */
							  {31,31,31, 5, 5, 6,31,31,31,31}, /* 3 */
							  {31,31,31, 9, 9,10,31,31,31,31}, /* 4 */
							  {31,31,31,31,31,31,14,31,31,31}, /* 5 */
							  {31,31,31,31,31,31,31,31,31, 7}, /* 6 */
							  {31,31,31,31,31,31,31,31,31, 8}, /* 7 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 8 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 9 */
							  {31,31,31,31,31,31,31,31,31,11}, /* 10 */
							  {31,31,31,31,31,31,31,31,31,12}, /* 11 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 12 */
							  {31,15,31,31,31,31,31,31,31,31}, /* 13 */
							  {31,31,31,31,31,31,20,31,31,31}, /* 14 */
							  {31,31,31,16,16,17,31,31,31,31}, /* 15 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 16 */
							  {31,31,31,31,31,31,31,31,31,18}, /* 17 */
							  {31,31,31,31,31,31,31,31,31,19}, /* 18 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 19 */
							  {31,31,31,31,31,31,31,21,22,31}, /* 20 */
							  {31,31,31,23,23,24,31,31,31,31}, /* 21 */
							  {31,31,31,27,27,31,31,31,31,31}, /* 22 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 23 */
							  {31,31,31,31,31,31,31,31,31,25}, /* 24 */
							  {31,31,31,31,31,31,31,31,31,26}, /* 25 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 26 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 27 */
							  {31,31,31,31,31,31,31,31,31,29}, /* 28 */
							  {31,31,31,31,31,31,31,31,31,30}, /* 29 */
							  {31,31,31,31,31,31,31,31,31,31}, /* 30 */
							  {31,31,31,31,31,31,31,31,31,31}};/* 31 */
	int estado = 0;

	*caracter = *cadena;
	while ((*caracter != '\0') && (estado != 31)) {
		estado = tTrans[estado][columna(*caracter)];
		*caracter = *(++cadena);
	}
	switch (estado) {
		case 7: case 8: case 11: case 12: case 18:
		case 19: case 25: case 26: case 29: case 30:
			*caracter = 's';
			break;
		default:
			*caracter = *(cadena-1);
	}
	return estado;
} /* automata() */
/***************************/


/*
Funcion que valida el alfabeto de la descripcion codificada
*/
int validarAlfabetoDC(char *desc) {
	int c=*desc;
    while (c!='\0') {
	if (!(c=='a'||c=='b'||c=='c'||c=='d'||c=='i'||
	    c=='s'||c=='t'||c=='x'||c=='z'||isdigit(c)))
	    return 0;
	c=*(++desc);}
    return 1;
} /* validarAlfabetoDC */
/***************************/


/*
Funcion que determina la columna en la tabla de transiciones
de automata()
*/
int columna(int c) {
    switch (c) {
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'i': return 4;
	case 's': return 5;
	case 't': return 6;
	case 'x': return 7;
	case 'z': return 8;
	default : return 9;
   }
} /* columna() */
/***************************/


/*
Funcion que determina si una cadena es numerica
*/
int esNumero(char *cad){
    int n, car = *cad;

    n=isdigit(car);
	while ((car != '\0') && n)
	car = *(cad++);
    return n;
} /* esNumero() */
/***************************/


/*
Funci½n que genera un archivo binario (Punto 1)
*/
int Archbin(char tipo, char* file,unsigned n,unsigned c) {
    unsigned i,j;
    char* aux3;
	double aux2;
    int aux1;
    FILE* arch;

    /*Validaciones de datos*/
    if(((c>99)||(c<=0))&&(tipo=='s')){
	error(7);
	return 0;
	}
    if(!((n>0)&&(n<=MAX))){
	error(5);
	return 0;
    }
	if((fopen(file,"rb")!=NULL)){
	error(6);
	return 0;
    }
    if(!(arch=fopen(file,"wb"))){
	error(3);
	return 0;
	}

    /*Generaci½n del archivo mediante la funci½n rand*/
    srand(time(NULL));
    switch(tipo){

    /*Tipo Entero*/
    case 'i':
	for(i=0;i<n;i++){
	    aux1=1000 + rand()%9000;
	    fwrite(&aux1,sizeof(int),1,arch);
	}
	break;

    /*Tipo Real Double*/
	case 'd':
	for(i=0;i<n;i++){
	    aux2=(double)(rand()%1000)/1000 + 100 + rand()%900;
	    fwrite(&aux2,sizeof(double),1,arch);
	}
	break;

    /*Tipo string de letras mayœsculas (incluida la letra '¾')*/
    case 's':
	aux3=(char*)malloc((c+1)*(sizeof(char)));
	for(i=0;i<n;i++){
	    for(j=0;j<c;j++)
	    if ((aux1=65+rand()%27)==91)
		aux3[j]='¾';
	    else
	    aux3[j]=aux1;
	    aux3[j]='\0';
	    fwrite(aux3,(c+1)*sizeof(char),1,arch);
	}
	break;
	} /* fin switch */

    fclose(arch);
    printf("\nArchivo creado");
    return 1;
} /* Archbin() */
/***************************/


/*
Funcion que genera un archivo binario a partir de uno de texto (punto 4)
*/
binarioatexto (int t, int cpl, char *ao, char *ad, int lc) {
	/* Declaro Variables */
	 int r=0; /* Variable de respuesta s/n */
	 int cl=0; /* Contador de caracteres en la linea */
	 int i; /* Dato leido del Archivo binario de Enteros */
	 double d; /* Dato leido del Archivo Binadio de Double */
	 char *ps; /* Puntero a dato leido del Archivo Binadio de String */
	 char si[6+1]; /* Dato Convertido a String de enteros */
	 char sd[8+1]; /* Dato Convertido a Strind de double */
	 FILE *ftext; /* Archivo de texto */
	 FILE *fbin; /* Srchivo Binario */
	 if ((ps = (char *) malloc ((lc + 1))) == NULL) {
		error(4);
		return 0;
	 } /* Reserva de memoria para dato string leido */
	/* Fin Declaracion
	Funcion de verificaci½n de Existencia del ao (Binario) */
		if (!(existe(ao))){
			error (1); /* Mensaje de error */
			return 0;
		}
	 /* Funcion de verificaci½n de Existencia del ad (Texto) */
		if (existe(ad)){
			/* Preguntar si sobreescibir */
			printf ("El archivo %s existe, quiere sobreescribirlo ? [s/n] ", ad);
			r=fgetc(stdin); /* Lee un caracter desde stdin */
			while (r!='s' && r!='S' && r!='n' && r!='N'){
				printf (" Debe responder Si o No [s/n] ");
				fflush (stdin); /* Limpiar Buffer de entrada */
				r=fgetc(stdin); /* Lee un caracter desde stdin */
			}
			if ((r == 'n') || (r == 'N'))
				return 0; /* Si no quiere sobreescribir sale de la funcion */
		}
		/* Abrir ao y ad */
		if (!(fbin = fopen (ao, "rb"))){
			error (2);
			return 0;
		}
		if (!(ftext = fopen (ad, "wt"))){
			error (3);
			fclose (fbin);
			return 0;
		}
	/* Para determinar que tipo de archivo binario se esta procesando
	   (i) Entero, (d) Double, (s) String */

	switch (t){
	
		case 'i': case 'I': /*  Binario de enteros */
			/* Mientra no eof de ao leer y grabar en ad */
			fread(&i, sizeof(int), 1, fbin);
			while (!feof(fbin)) {
	/* Asumimos que la cantidada de caracteres por linea incluye los blancos, pero no incluye /n */
				sprintf( si,"%i", i); /* Se transforma un int a string */
			/* Se evalua si ya se completo la cantidad de caracteres por linea */
				if ((cl = (cl + strlen(si))) > cpl) {
				fprintf	(ftext, "\n");
				cl = 0;
				 }
				 if (!(cl == strlen(si))){
					fprintf (ftext, "%s", " "); /* Se agrega el espacio en blanco */
					cl++; /* Se incrementa la cantidad de caracteres en la linea */
				 }
				 fprintf (ftext, "%s", si); /* Se agrega un string mas al archivo */
				 fread(&i, sizeof(int), 1, fbin); /* Se vuelve a leer del ao */
			}
			break;
	
		case 'd': case 'D': /* Binario de double */
			/* mientra no eof de ao leer y grabar en ad */
			fread(&d, sizeof(double), 1, fbin);
			while (!feof(fbin)) {
	/* Asumimos que la cantidada de caracteres por linea incluye los blancos, pero no incluye /n */
				sprintf( sd,"%3.3f", d); /* Convierte de double (xxx.xxx) a string */
			/* Se evalua si ya se completo la cantidad de caracteres por linea */
				if ((cl = (cl + strlen(sd))) > cpl) {
					fprintf	(ftext, "\n");
					cl = 0;
				}
				 if (!(cl == strlen(sd))){
					fprintf (ftext, "%s", " "); /* Se agrega el espacio en blanco */
					cl++; /* Se incrementa la cantidad de caracteres en la linea */
				 }
				fprintf (ftext, "%s", sd); /* Se agrega un string mas al archivo */
				fread(&d, sizeof(double), 1, fbin); /* Se vuelve a leer del ao */
			}
			break;
	
		case 's': case 'S': /* Binario de string */
			/* mientra no eof de ao leer y grabar en ad */
			fread(ps, (lc + 1) , 1, fbin);
			while (!feof(fbin)) {
	/* Asumimos que la cantidada de caracteres por linea incluye los blancos, pero no incluye /n */
			/* Se evalua si ya se completo la cantidad de caracteres por linea */
				if ((cl = (cl + strlen(ps))) > cpl) {
					fprintf	(ftext, "\n");
					cl = 0;
				}
				 if (!(cl == strlen(ps))){
					fprintf (ftext, "%s", " "); /* Se agrega el espacio en blanco */
					cl++; /* Se incrementa la cantidad de caracteres en la linea */
				 }
				fprintf (ftext, "%s", ps); /* Se agrega un string mas al archivo */
				fread(ps, (lc + 1) , 1, fbin); /* Se vuelve a leer del ao */
			}
			break;
		}
	fclose (fbin); /* Cierra el Archivo Binario Abierto */
	fclose (ftext); /* Cierra el Archivo de texto Creado */
	free (ps); /* Libera espacio de memoria dinamica */
	return 1; /* Retorna sin error */
} /* binarioatexto() */
/***************************/


/*
Funcion que determina si un archivo existe
*/
int existe (char *arch) {
	FILE *a;

	if ((a= fopen (arch, "r")) == NULL)
	return 0;
	fclose (a);
	return 1;
} /* existe() */
/***************************/


/*
Funcion de error
*/
void error (int e){
	printf("\n");
	switch (e) {
	case 0 : /* Descripcion Codificada no valida */
		printf("La Descripcion Codificada no es valida.\n");
		break;
	case 1 : /* No existe archivo de Origen */
		printf("No existe el Archivo de Origen.\n");
		break;
	case 2 : /* Ocurrio un error al leer Archivo de Origen */
		printf("Ocurrio un error al leer Archivo de Origen.\n");
		break;
	case 3 : /* No se pudo crear el Archivo de Destino */
		printf("No se pudo crear el Archivo de Destino.\n");
		break;
	case 4 : /* No hay suficiente memoria para procesar el Archivo de Origen */
		printf("No hay suficiente memoria para procesar el Archivo de Origen.\n");
		break;
	case 5 : /* Cantidad de campos incorrecta */
		printf("Parÿmetro de Cantidad de Campos incorrecto.\nDebe ser un nœmero entre 1 y %d.\n",MAX);
		break;
	case 6 : /* El archivo ya existe */
		printf("El nombre de archivo asignado corresponde a un archivo existente.\n");
		break;
	case 7 : /* Cantidad de elementos incorrecta */
		printf("Parÿmetro de Cantidad de elementos incorrecto.\nDebe ser un nœmero entre 1 y 99.\n");
		break;
	case 8 : /* Parametro no numerico */
		printf("Un parametro que debe ser numerico no lo es.\n");
		break;
	case 9 : /* Faltan elementos */
		printf("No se ingresaron elementos para procesar.\n");
		break;
	case 10: /* Longitud de l­nea <= 0 */
		printf("La longitud de l­nea del archivo destino "
		"debe encontrarse entre 0 y %d.\n", MAX);
		break;
	case 11: /* Longitud de l­nea < longitud de cadenas */
		printf("La longitud de l­nea del archivo destino de ser "
		"mayor que la longitud de las cadenas a copiar.\n");
		break;
	case 12: /* No se puede asignar memoria dinamica */
		printf("No se pudo asignar memoria dinÿmica "
		"al buffer de lectura.\n");
		break;
	case 13: /* Longitud de l­nea < longitud maxima entero */
		printf("La longitud de l­nea debe ser mayor que %d, "
		"la mÿxima longitud de un entero.\n", (sizeof(int)==2) ? 5 : 10);
		break;
	case 14: /* Longitud de l­nea < longitud maxima real */
		printf("La longitud de l­nea debe ser mayor que 7 "
		"(longitud mÿxima de un real).\n");
		break;
	case 15: /* Contenido de Archivo de Origen incorrecto */
		printf("El contenido de Archivo de Origen es incorrecto.");
	} /* switch */
	printf("Si desea obtener ayuda, llame al programa sin parametros.\n");
} /* error() */
/***************************/


void ayuda(void) {
	char c;
	printf("\nEste programa genera un archivo segun se indique mediante una Descripcion\n"
		   "Codificada, en forma aleatoria o a partir de otro archivo.\n"
		   "La Descripcion Codificada es un codigo que determina una "
		   "entre varias opciones:\n"
		   "\nLas opciones para generacion aleatoria son:\n"
		   "  -ati, atd, ats01..ats99, abi, abd, abs01..abs99\n"
		   "   Donde el segundo caracter indica si el archivo sera binario o de texto, \n"
		   "   y el tercero el tipo de dato (i: entero, d:real double, s:string)\n"
		   "   En caso de ser este ultimo 's', los dos siguientes caracteres \n"
		   "   deben indicar la longitud de la cadena.\n"
		   "\n   Si el archivo es binario la Descripcion Codificada sera:\n"
		   "   * genera <Tipo de archivo> <cantidad de elementos> <nombre del archivo>\n"
		   "\n   Si el archivo es de texto la Descripcion Codificada sera:\n"
		   "   * genera <Tipo de archivo> <Tama¤o maximo de linea> <cantidad de elementos>\n"
		   "   <Nombre del archivo>\n");
		   scanf("%c",&c);
		printf("\nLas opciones para generacion a partir de un archivo son:\n"
		   "  -ctbi, ctbd, ctbs01..ctbs99\n"
		   "   Donde \"tb\" indica que se debe crear un archivo binario a partir de\n"
		   "   uno de texto.\n"
		   "\n   En este caso la Descripcion Codificada sera:\n"
		   "   * genera <Tipo> <Tama¤o maximo de linea> <Nombre del archivo de origen>\n"
		   "   <Nombre del archivo de destino>\n"
		   "\n  -cbtzi, cbtzd, cbtzs01..cbtzs99, cbtxi, cbtxd, cbtxs01..cbtzs99\n"
		   "   Donde \"bt\" indica que se debe crear un archivo de texto a partir\n"
		   "   de uno binario. 'z' indica que se deben utilizar todos los registros\n"
		   "   del archivo binario y 'x' que se deben utilizar solo los registros de\n"
		   "   las posiciones especificadas.\n"
		   "\n   Si el caracter es 'z' la Descripcion Codificada sera:\n"
		   "   * genera <Tipo> <TamaÏo maximo de linea> <Nombre del archivo de origen>\n"
		   "   <Nombre del archivo de destino>\n"
		   "\n   Si el caracter es 'x' la Descripcion Codificada sera:\n"
		   "   * genera <Tipo> <Tama¤o maximo de linea> <Nombre del archivo de origen>\n"
		   "   <Nombre del archivo de destino> <Posici¢n 1 del archivo>...<Posici¢n n>\n"
		   "\n  -En ambos casos, los siguientes caracteres indican lo mismo que en la\n"
		   "   generacion aleatoria.");
	scanf("%c",&c);
	printf("");
} /* ayuda() */
/***************************/


/*************************************************************************
* convertBxToT: Copia determ. elem. de un archivo binario a uno de texto *
**************************************************************************
* INPUT:                                                                 *
*  char *fsource = Nombre fisico del archivo binario de origen      	 *
*  char *fdest   = Nombre fisico del archivo de texto de destino         *
*  char datatype = Indica si el archivo binario de origen es de:         *
*                       (i) enteros	 / (d) doubles  /  (s) strings   	 *
*  int nelem     = Cantidad de elementos que se intentaran copiar        *
*  long velem[]  = Contiene los numeros de los elementos a copiar	 	 *
*  long stlen    = Longitud de las cadenas si el archivo es de strings   *
*  long linelen  = Longitud de las lineas del archivo de texto. Si es 0, *
*                  se asume que el archivo no estÿ dividido en lineas.   *
*************************************************************************/
void convertBxToT(char *fsource, char *fdest, char datatype, int nelem,
											long velem[], long stlen, long linelen){

	long cantregs;
	FILE *fbin, *ftext;
	int choice;

	/************************-=| VALIDACION |=-***************************/

	/* ERROR 9: No hay elementos para copiar */
	if (!(nelem > 0)) { error(9); return;}
	/* ERROR 1: No existe el archivo de origen */
	if ((fbin = fopen(fsource, "rb")) == NULL) { error(1); return;}
	/* WARNING: El archivo de destino ya exist­a. Sobreescribirlo? */
	if (!((ftext = fopen(fdest, "rt")) == NULL)) {

		printf("\nEl archivo de destino ya existe. "
												"Desea sobreescribirlo (S/N)? ");
		choice = getchar();

		while(choice != 's' && choice != 'S' && choice != 'n' && choice != 'N')
			choice = getchar();

		/* Si elige no sobreescribir, sale con error 6 */
		if (choice == 'n' || choice == 'N'){
			fclose(fbin);
			fclose(ftext);
			error(6);
			return;
		}
	}

	/* ERROR 3: No se puede crear el archivo de destino */
	if ((ftext = fopen(fdest, "wt")) == NULL) {
		fclose(fbin);
		error(3);
		return;
	}



	/************************-=| PROCESO |=-*****************************/

	/* Llamo a funci½n espec­fica para copiar de acuerdo a datatype */
	switch(datatype){
		case 's': case 'S':
			cBxtTstrings(fbin, ftext, nelem, velem, stlen, linelen);
			break;
		case 'i': case 'I':
			cBxtTintegers(fbin, ftext, nelem, velem, linelen);
			break;
		case 'd': case 'D':
			cBxtTdoubles(fbin, ftext, nelem, velem, linelen);
			break;
	}

	fclose(fbin);
	fclose(ftext);
	return;
} /* Fin de convertBxToT */
/***************************/


/*************************************************************************
* cBxtTstrings: Utilizada en convertBxToT cuando el origen es de strings *
* ***********************************************************************/
void cBxtTstrings(FILE *fbin, FILE *ftext, int nelem, long velem[],
														  long stlen, long linelen){

	long lenCurLine = 0, strLenReal, cantregs;
	char *string;
	int i;

	/************************-=| VALIDACION |=-***************************/

	/* ERROR 10: La longitud de l­nea es menor que 0 */
	if (!(linelen >= 0)) {
		 error(10);
		 return;
	}
	else
		if(linelen != 0)  /* Si la longitud de l­nea es != 0  */
			/* ERROR 11: La longitud de l­nea es menor que long. de strings */
			if (!(linelen > stlen)) {
				error(11);
				return;
			}

	/* ERROR 12: No se pudo asignar memoria dinÿmica al buffer de lectura */
	if ((string = (char*) malloc(stlen + 1)) == NULL) { error(12); return;}


	/*************************-=| PROCESO |=-*****************************/

	/* Obtengo la cantidad de registros del archivo de origen para saber
		si los elementos pedidos existen realmente en el origen. */
	cantregs = getCantRegs(fbin, stlen);

	string[stlen] = '\0'; /* Escribo '\0' al final del buffer de lectura.*/

	for(i=0; i < nelem; i++){	/* Ciclo hasta procesar todos los elementos */

		if ( ! (velem[i] > 0 && velem[i] <= cantregs))
			/* Si el elemento esta fuera de [1;cantregs] muestra error y sale */
			printf ("ERROR: El elemento %d no existe en el archivo "
												"de origen.\n", velem[i]);
		else{
			/* Si todo ok, copia el elemento solicitado */
			fseek(fbin, stlen * (velem[i] - 1), SEEK_SET); /* busco elemento */
			fread(string, stlen, 1, fbin); /* lo leo al buffer */
			strLenReal = strlen(string); /* veo long. real de string leida */
			if (linelen != 0 && (lenCurLine += strLenReal + 1) > linelen) {
				/* Si se sobrepaso longitud de l­nea permitida, escribo '\n' */
				fputc('\n', ftext);   /*  éŽŽ> + 1 por el espacio */
				lenCurLine = strLenReal + 1; /* reseteo long. actual de l­nea */
			}
			fprintf (ftext, "%s ", string); /* guardo buffer en arch. destino */
		} /* fin del else */
	} /* fin del for */

	free(string); /* libero el buffer */
} /* Fin de cBxtTstrings */
/***************************/


/*************************************************************************
* cBxtTintegers: Utilizada en convertBxToT cuando el origen es de ints   *
* ***********************************************************************/
void cBxtTintegers(FILE *fbin, FILE *ftext, int nelem, long velem[],
																				long linelen){

	long lenCurLine = 0, cantregs;
	int buffer, buffLen, i;  /* buffer: bloque de bytes leidos del archivo binario */


	/************************-=| VALIDACION |=-***************************/

	/* ERROR 13: La longitud de l­nea es menor que la longitud mÿxima de
					los enteros + el espacio y es distinta de cero. */
	if (linelen < ((sizeof(int) == 2) ? 6 : 11))
		 if (linelen != 0){
				error(13);
				return;
		 }

	/*************************-=| PROCESO |=-*****************************/

	/* Obtengo la cantidad de registros del archivo de origen para saber
		si los elementos pedidos existen realmente en el origen. */
	cantregs = getCantRegs(fbin, sizeof(int));

	for(i=0; i < nelem; i++){	/* Ciclo hasta procesar todos los elementos */

		if ( ! (velem[i] > 0 && velem[i] <= cantregs))
			/* Si el elemento esta fuera de [1;cantregs] muestra error */
			printf ("ERROR: El elemento %d no existe en el archivo "
												"de origen.\n", velem[i]);
		else{
			/* Si todo ok, copia el elemento solicitado */
			fseek(fbin, sizeof(int) * (velem[i] - 1), SEEK_SET); /* busco elem.*/
			fread(&buffer, sizeof(int), 1, fbin); /* lo leo al buffer */
			buffLen = getIntLen(buffer);
			if (linelen != 0 && (lenCurLine += buffLen + 1) > linelen) {
				/* Si se sobrepaso longitud de l­nea permitida, escribo '\n' */
				fputc('\n', ftext);   /*  éŽŽ> + 1 por el espacio */
				lenCurLine = buffLen + 1; /* reseteo largo l­nea actual */
			}
				fprintf (ftext, "%d ", buffer); /* guardo buffer en arch. destino */

		} /* fin del else */
	} /* fin del for */

} /* Fin de cBxtTintegers */
/***************************/


/*************************************************************************
* cBxtTdoubles: Utilizada en convertBxToT cuando el origen es de ints    *
*************************************************************************/
void cBxtTdoubles(FILE *fbin, FILE *ftext, int nelem, long velem[],
																				long linelen){

	long lenCurLine = 0, cantregs;
	double buffer;
	int i;  /* buffer: bloque de bytes leidos del archivo binario */

	/************************-=| VALIDACION |=-***************************/

	/* ERROR 14: La longitud de l­nea es menor que 7 + 1 = 8 y != 0
				  asumo reales en [0.000;999.999] ŽŽŽë   ·ŽŽ espacio  */

	if (linelen < 8 & linelen != 0){
		error(14);
		return;
	}

	/*************************-=| PROCESO |=-*****************************/

	/* Obtengo la cantidad de registros del archivo de origen para saber
		si los elementos pedidos existen realmente en el origen. */
	cantregs = getCantRegs(fbin, sizeof(double));

	for(i=0; i < nelem; i++){	/* Ciclo hasta procesar todos los elementos */

		if ( ! (velem[i] > 0 && velem[i] <= cantregs))
			/* Si el elemento esta fuera de [1;cantregs] muestra error */
			printf ("ERROR: El elemento %d no existe en el archivo "
												"de origen.\n", velem[i]);
		else{
			/* Si todo ok, copia el elemento solicitado */
			fseek(fbin, sizeof(double) * (velem[i] - 1), SEEK_SET); /* busco elem.*/
			fread(&buffer, sizeof(double), 1, fbin); /* lo leo al buffer */
			if(buffer > 1000.000)
				/* Fuera de rango: Informo por pantalla que se omite elem. */
				printf("El elemento %d ha sido omitido por encontrarse "
								"fuera de [0.000;999.999].\n", velem[i]);
			else{
				if (linelen != 0 && (lenCurLine += 7 + 1) > linelen) {
					/* Si se sobrepaso longitud de l­nea permitida, escribo '\n'*/
					fputc('\n', ftext);   /*  éŽŽ> + 1 por el espacio */
					lenCurLine = 7 + 1; /* reseteo largo l­nea actual */
				}
				fprintf (ftext, "%07.3f ", buffer); /* guardo buffer en dest. */
			} /* fin del else interno */
		} /* fin del else externo */
	} /* fin del for */

} /* Fin de cBxtTdoubles */
/***************************/


/*************************************************************************
* getCantRegs: Devuelve la cantidad de registros de un archivo dado	 	 *
**************************************************************************
* INPUT:                                                                 *
*  FILE *file: archivo del cual se quiere saber la cantidad de registros *
*  int *regsize: tamaÏo de cada registro.				 				 *
*************************************************************************/
long getCantRegs(FILE *file, long regsize){

	fseek(file, 0, SEEK_END);

	return (ftell(file) + 1) / regsize;
} /* Fin de getCantRegs */
/***************************/


/*************************************************************************
* getIntLen: Devuelve la cantidad de digitos de un entero dado		 *
**************************************************************************
* INPUT:                                                                 *
*  int num: numero del que se desea conocer la cantidad de digitos	 *
*************************************************************************/
int getIntLen(int num){
	/* Si enteros de 16 bits, max. long. = 5, si 32 bits, max long = 10 */
	int longi;

	longi = (sizeof(int) == 2) ? 5 : 10;

	/* Ciclo hasta que num / 10^longi != 0 */
	while (!(num / pow(10,longi)) && longi>0)
		longi--;

	/* Si longi=0 el numero es 0. Retorno longitud 1. */
	if (longi == 0) return 1;

	/* Si el numero era negativo, sumo uno por el signo menos */
	if (num<0) longi++;

	/* Retorno la longitud */
	return longi;
} /* Fin de getIntLen */
/***************************/


/*
Funcion que genera un archivo de texto aleatorio (punto 2)
*/
int texto_aleatorio(char parametro, int caracteres, int cantidad, char * archivo, int largo){

	/* DEFINICION DE VARIABLES DE LA FUNCION */
	FILE * arch;
	int contc=0;
	int numero=0;
	int numero3=0;
	int i=0;
	char text[100]="";
	char linea[MAX]="";
	char letra[2]="";


	srand(time(NULL)); /* COMIENZA EL RANDOM EN MEMORIA */

	/* Verifica si los parametros de la cantidad de caracteres por linea y la cantidad
	de elementos a generar son corrector */

	if ((cantidad<0)||(caracteres<0)){
		/* "Ni la cantidad de caracteres por linea ni la cantidad de elementos a generar pueden ser un valor negativo y el valor mÿximo para ambas variables es 10.000" */
		error(10);
		return 0;
	}
	if (cantidad==0){
		 /*	La cantidad de elementos a generar no puede ser cero.*/
			error(7);
			return 0;
	}
	else
		if (caracteres>MAX){
			/* La maxima cantidad de caracteres es MAX.*/
			error(12);
			return 0;
		}

	/* Verifica si se puede abrir el archivo sin problemas */

	arch=fopen(archivo,"rt");
	if (!(arch==NULL)){
		   /* El archivo ya existe en este directorio */
		error(6);
		fclose(arch);
		return 0;
	}
	arch=fopen(archivo,"wt");
	if (arch==NULL){
		  /* No se puede abrir el archivo especificado */
		error(3);
		fclose(arch);
		return 0;
	}

	/* PROCESA EN EL CASO DE RECIBIR UNA I COMO PERAMETRO */

	if ((parametro=='i')||(parametro=='I')){

		/* TRUNCA LA CANTIDAD DE CARACTERES A 5 EN EL CASO DE QUE LA CANTIDAD
		INDICADA SEA MENOR A 5, ESTO SE HACE PORQUE EL NUMERO A GENERAR ES DE
		4 CARACTERES 1000..9999 MAS EL NULO DEL FINAL */

		if (caracteres<5) {
			caracteres=5;
			printf("Se ha redondeado la cantidad de caracteres a 5");
		}

		/* SE VA DECREMENTANDO LA CANTIDAD DE ELEMENTOS A GENERAR HASTA LLEGAR
		A CERO, QUE ES CUANDO TERMINA */

		while(cantidad!=0){
			contc=0;
			linea[0]='\0';

			/* GENERA LOS NUMEROS ALEATORIOS Y LOS GUARDA EN LA VARIABLE
			LINEA QUE DESPUES SERA COPIADA AL ARCHIVO, EFECTUA ESTO
			MIENTRAS LA CANTIDAD DE CARACTERES RESTANTES SEA MAYOR A 5
			QUE ES LA MENOR CANTIDAD DE CARACTERES A AGREGAR */

			while ((cantidad!=0)&&(caracteres-contc)>=5){
				numero=1000+rand()%8999;
				sprintf(text,"%d ",numero);
				strcat(linea, text);
				contc=contc+5;
				cantidad--;
			}

			/* GRABA LA LINEA GENERADA EN EL ARCHIVO */
			strcat(linea,"\n");
			fprintf(arch,"%s",linea);
		}

		/* CIERRA EL ARCHIVO Y DEVUELVE EL CONTROL AL PROGRAMA PRINCIPAL */
		fclose(arch);
		return 1;
	}

	/* PROCESA EN EL CASO DE RECIBIR UNA D COMO PARAMETRO */


	if ((parametro=='d')||(parametro=='D')){

		/* TRUNCA LA CANTIDAD DE CARACTERES A 8 EN EL CASO DE QUE LA CANTIDAD
		INDICADA SEA MENOR A 8, ESTO SE HACE PORQUE EL NUMERO A GENERAR ES DE
		7 CARACTERES 999.999 MAS EL NULO DEL FINAL */

		if (caracteres<8) {
			caracteres=8;
			printf("Se ha redondeado la cantidad de caracteres a 7");
		}

		/* SE VA DECREMENTANDO LA CANTIDAD DE ELEMENTOS A GENERAR HASTA LLEGAR
		A CERO, QUE ES CUANDO TERMINA */

		while(cantidad!=0){
			contc=0;
			linea[0]='\0';

			/* GENERA LOS NUMEROS ALEATORIOS Y LOS GUARDA EN LA VARIABLE
			LINEA CON UN DETERMINADO FORMATO 999.999,
			QUE DESPUES SERA COPIADA AL ARCHIVO, EFECTUA ESTO
			MIENTRAS LA CANTIDAD DE CARACTERES RESTANTES SEA MAYOR 8
			QUE ES LA CANTIDAD MAXIMA QUE SE PUEDE AGREGAR */

			while ((cantidad!=0)&&(caracteres-contc)>=8){
				numero=100+rand()%899;
				numero3=100+rand()%899;
				sprintf(text,"%d.%d ",numero,numero3);
				strcat(linea, text);
				contc=contc+8;
				cantidad--;
			}

			/* GRABA LA LINEA GENERADA EN EL ARCHIVO */
			strcat(linea,"\n");
			fprintf(arch,"%s",linea);
		}

		/* CIERRA EL ARCHIVO Y DEVUELVE EL CONTROL AL PROGRAMA PRINCIPAL */
		fclose(arch);
		return 1;
	}

	/* PROCESA EN EL CASO DE RECIBIR UNA S COMO PARAMETRO */

	if ((parametro=='s')||(parametro=='S')){
		numero=largo;

		if (caracteres<=numero)	{
			caracteres=numero+1;
			printf("Se ha redondeado la cantidad de caracteres por linea como para que entre solo un elemento.");
		}
		while(cantidad!=0){
			contc=0;
			linea[0]='\0';

			/* GENERA LOS STRINGS ALEATORIOS Y LOS GUARDA EN LA VARIABLE
			LINEA QUE DESPUES SERA COPIADA AL ARCHIVO, EFECTUA ESTO
			MIENTRAS LA CANTIDAD DE CARACTERES RESTANTES SEA MAYOR A LA
			CANTIDAD DE CARACTERES INDICADOS DESPUES DE LA LETRA S
			PARA PODER SEGUIR AGREGANDO CARACTERES EN ESA LINEA */

			while ((cantidad!=0)&&(caracteres-contc)>=numero+1){
				text[0]='\0';

				/* GENERA LA CADENA DE TEXTO ALEATORIA */

				for(i=0;strlen(text)<numero;i++){
					letra[0]=65+rand()%25;
					strcat(text,letra);}
				strcat(text," ");
				strcat(linea, text);
				contc=contc+numero+1;
				cantidad--;
			}

			/* GRABA LA LINEA GENERADA EN EL ARCHIVO */
			strcat(linea,"\n");
			fprintf(arch,"%s",linea);
		}

		/* CIERRA EL ARCHIVO Y DEVUELVE EL CONTROL AL PROGRAMA PRINCIPAL */
		fclose(arch);
		return 1;
	}
	return 0;
} /* texto_aleatorio() */
/***************************/



/*
Funcion que genera archivo binario a partir de uno de texto(punto 3)
   Parÿmetros: Tipo de Archivo, Nombre del archivo de texto,
   Nombre del archivo binario, Mÿximo de caracteres por l­nea
   y cantidad de elementos(solo para cadenas, sino mandar cero).
*/
int Textabin(char tipo, char *file1, char *file2, unsigned n, unsigned c) {

	char *aux,*aux3, *p;
	double aux2;
	int aux1;
	FILE *arch1, *arch2;

	/*Validaciones de datos*/
	if(((c>99)||(c<=0))&&(tipo=='s')) {
		error(7);
		return 0;
	}
	if(!((n>0)&&(n<=MAX))) {
		error(5);
		return 0;
	}
	if(!(arch1=fopen(file1,"rt"))) {
		error(2);
		return 0;
	}
	if((fopen(file2,"rb")!=NULL)) {
		error(6);
		fclose(arch1);
		return 0;
	}
	if(!(arch2=fopen(file2,"wb"))) {
		error(3);
		fclose(arch1);
		return 0;
	}

	aux=(char*)malloc((n+1)*(sizeof(char)));

	while(fgets(aux,n+1,arch1)) {
		p=strtok(aux," \n");
		while(p!=NULL) {
			switch(tipo) {

				/*Tipo Entero*/
				case 'i':
					if(!(entero(p,&aux1))) {
						error(15);
						fclose(arch1);
						fclose(arch2);
						return 0;
					}
					fwrite(&aux1,sizeof(int),1,arch2);
					break;

				/*Tipo Real Double*/
				case 'd':
					if(!(realdoble(p,&aux2))) {
						error(15);
						fclose(arch1);
						fclose(arch2);
						return 0;
					}
				fwrite(&aux2,sizeof(double),1,arch2);
				break;

				/*Tipo string de */
				case 's':
					aux3=(char*)malloc((c+1)*(sizeof(char)));
					strcpy(aux3,p);
					fwrite(aux3,c+1,1,arch2);
					break;
			} /* switch */
		p=strtok(NULL," \n");
		} /* while interno */
	} /* while externo */
	fclose(arch1);
	fclose(arch2);
	printf("\nArchivo creado");
	return 1;
} /* Textabin() */
/***************************/


/*
Funcion que comprueba si la cadena es un entero.
*/
int entero(char *cadena, int *num) {
	static tabla[4][3]={{2,1,1},
						{2,3,3},
						{2,3,3},
						{3,3,3}};
	int i, actual=0;
	int caracter=*cadena;
	double auxiliar=0;
	int signo=1;
	double auxdec;

	for(i=0;cadena[i]!='\0';i++) if(!(isdigit(cadena[i])||cadena[i]=='+'||cadena[i]=='-')) return 0;
		while(caracter!='\0'){
			actual=tabla[actual][columna2(caracter)];
			switch(actual){
				case 1:
					if(caracter=='-') signo=-1;
					break;
				case 2:
					auxiliar=10*auxiliar+valor(caracter);
					break;
			}
		caracter=*(++cadena);
		}
		if(actual==2){
		*num=signo*auxiliar;
		return 1;
	}
	else return 0;
} /* entero() */
/***************************/


/*
Funcion que comprueba si la cadena es un real double.
*/
int realdoble(char *cadena, double *num){
	static tabla[6][4]={{1,2,2,3},
				{1,5,5,3},
				{1,5,5,3},
				{4,5,5,5},
				{4,5,5,5},
				{5,5,5,5}};
	int i,j, actual=0;
	int caracter=*cadena;
	double auxiliar=0;
	double auxdec=0;
	int signo=1;

	for(i=0;cadena[i]!='\0';i++) if(!(isdigit(cadena[i])||cadena[i]=='+'||cadena[i]=='-'||cadena[i]=='.')) return 0;
		i=0;
		while(caracter!='\0'){
			actual=tabla[actual][columna2(caracter)];
			switch(actual){
				case 2:
					if(caracter=='-') signo=-1;
					break;
				case 1:
					auxiliar=10*auxiliar+valor(caracter);
					break;
				case 4:
					i++;
					auxdec=10*auxdec+valor(caracter);
					break;
			} /* switch */
			caracter=*(++cadena);
		} /* while */
		if(actual==0||actual==1||actual==4){
		for(j=0;j<i;j++) auxdec=0.1*auxdec;
		*num=(double) signo*auxiliar + auxdec;
		return 1;
	} /* for */
	else return 0;
} /* realdoble() */
/***************************/


/*Declaraci½n de una funci½n auxiliar del aut½mata que asigna la columna correspondiente*/
int columna2 (int c){
	switch (c){
		case '+': return 1;
		case '-': return 2;
		case '.': return 3;
		default : return 0;
	}
} /* columna2() */
/***************************/


/*
Funcion auxiliar de los automatas realdoble() y entero()
*/
int valor(int c){
	return (c-'0');
} /* valor() */
/***************************/