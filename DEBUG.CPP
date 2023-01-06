/*De Nardo Martin*//*leg:113769-4*//*A¤o:2003*/
/*EJERCICIO 4:Programa que recorre la memoria informando su contenido*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <ctype.h>
union dato {long puntero1;
	    int vect[2];};
union dato punt;
char huge*puntero;
void proceso ();
void main ()
{
char opcion;
clrscr();
textcolor(0x9);
cprintf("Ingrese Segmento: ");
scanf("%x",&punt.vect[1]);
cprintf("Ingrese Desplazamiento: ");
scanf("%x",&punt.vect[0]);
puntero=(char far*)punt.puntero1;
proceso();
textcolor(0x9);
cprintf ("\n\r¨Que Desea Hacer?\n\rS: Mostrar 10 Lineas Siguientes\n\r"
	"R: Mostrar 10 Lineas Anteriores\n\rD: Cambiar Direccion\n\rQ: Salir\n\r");
textcolor (2);
cprintf("Opcion: ");
textcolor(0x3);
opcion=getche();
while (1)
{
switch (opcion)
	{case 's':
		proceso();break;
	case 'r':
	{
		puntero=puntero-(((0x10)*10)*2);
		proceso();
	}break;
	case 'q':{exit(opcion-'q');}break;
	case 'd':
		{textcolor(0x9);
		cprintf ("\n\rIngrese Nuevo Segmento: ");
		scanf("%x",&punt.vect[1]);
		cprintf ("Ingrese Nuevo Desplazamiento: ");
		scanf("%x",&punt.vect[0]);
		puntero=(char far*)punt.puntero1;
		proceso();
		}break;
	default: {
		textcolor(0x4);
		cprintf("­Opcion No Valida!");}break;
	}
textcolor(0x9);
cprintf ("\n\r¨Que Desea Hacer?\n\rS: Mostrar 10 Lineas Siguientes\n\r"
	"R: Mostrar 10 Lineas Anteriores\n\rD: Cambiar Direccion\n\rQ: Salir\n\r");
textcolor(0x2);
cprintf("Opcion: ");
textcolor(0x3);
opcion=getche();
}
}
void proceso()
{
int i,l,k;
unsigned char vec[16];
for(i=0;i<10;i++)
	{
	textcolor(4);
	cprintf("\n\r%p ",puntero);
	for(k=0;k<16;k++)
		{vec[k]=*puntero;
		puntero++;}
	textcolor(7);
	for(k=0;k<16;k++)
		cprintf("%x ",vec[k]);
	for(k=0;k<16;k++)
		{textcolor(3);
		if (isprint(vec[k]))
			cprintf("%c ",vec[k]);
		else
			cprintf(".");
	}       }
}