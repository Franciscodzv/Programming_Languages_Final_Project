#include <stdio.h>
#include <stdlib.h>
#include <assert.h>         //Funcion assert
#include <conio.h>          //Funcion getch
#include "tabla_verdad.h"   //Funciones para generar tabla de verdad

#define nombre_archivo_salida "TRUTH TABLE.txt"
#define OPCION_SALIR '4'

//Procedimiento que valida las funciones
//evaluar_expresion y validar_expresion
//con algunos ejemplos de entrada.
void pruebas()
{
    //Probar funcion para evaluar expresion
    assert(evaluar_expresion("~(T & F)") == 1);
    assert(evaluar_expresion("~F") == 1);

    assert(evaluar_expresion("~T") == 0);
    assert(evaluar_expresion("(T & F)") == 0);

    //Probar funcion para validar expresion
    assert(validar_expresion("a^") == 0);
    assert(validar_expresion("amdgi") == 0);
    assert(validar_expresion("&^~") == 0);
    assert(validar_expresion("b > a ^ ~b") == 0);
    assert(validar_expresion("ferwiog5%$") == 0);
    assert(validar_expresion("a * b") == 0);
    assert(validar_expresion(" ") == 0);
    assert(validar_expresion("()") == 0);
    assert(validar_expresion("(a)()") == 0);
    assert(validar_expresion("()a&b") == 0);

    assert(validar_expresion("~(~b)") == 1);
    assert(validar_expresion("p | (q & (r | ~(p)))") == 1);
    assert(validar_expresion("p & ~s | ~q & r") == 1);
    assert(validar_expresion("~A") == 1);
    assert(validar_expresion("~~b") == 1);
    assert(validar_expresion("a | b") == 1);
}

//Procedimiento que recibe el nombre de un archivo
//e imprime sus contenido en pantalla en caso de que lo
//encuentre y muestra un mensaje sino.
void imprimir_archivo(char nombre_archivo[])
{
    FILE *archivo = fopen(nombre_archivo, "r");

    if(archivo == NULL)
    {
        printf("File doesn't exist'");
    }
    else
    {
        char letra;
        fscanf(archivo, "%c", &letra);
        while(!feof(archivo))
        {
            printf("%c", letra);
            fscanf(archivo, "%c", &letra);
        }
    }
}

//Procedimiento que muestra un mensaje y
//espera a que el usuario presione una tecla
void pausa()
{
    printf("\nPress any key to continue");
    getch();
}

int main()
{
    pruebas();
    char expresion[MAX];
    char respuesta_menu = ' ';

    do
    {
        //Limpiar la pantalla
        system("cls");

        //Mostrar menu
        imprimir_archivo("menu.txt");

        //Leer opcion
        scanf("%c%*c", &respuesta_menu);

        switch(respuesta_menu)
        {
            //Generar tabla de verdad de expresion logica
            case '1':
                system("cls");
                printf("TRUTH TABLE GENERATOR\n\n");
                printf("Enter a logical expression: ");
                gets(expresion);
                if(validar_expresion(expresion) == 1)
                {
                    generar_tabla(expresion, nombre_archivo_salida);
                    printf("\n");
                    imprimir_archivo(nombre_archivo_salida);
                    printf("\nThe table was saved in the file%s.\n", nombre_archivo_salida);
                }
                else
                {
                    printf("\nThe expression entered is not valid.");
                    printf("\nCheck your expression and re-enter it.\n");
                }
                pausa();
                break;

            //Mostrar instrucciones del programa
            case '2':
                system("cls");
                imprimir_archivo("instrucciones.txt");
                pausa();
                break;

            //Mostrar informacion del programa
            case '3':
                system("cls");
                imprimir_archivo("about.txt");
                pausa();
                break;

            //Mostrar mensaje de terminar el programa
            case '4':
                printf("\nHave a nice day!\n\n");
                pausa();
                break;

            //Mostrar mensaje de opcion invalida
            default:
                printf("\nYou must enter a number between 1 and %c.\n", OPCION_SALIR);
                pausa();
                break;
        }
    }
    while(respuesta_menu != OPCION_SALIR);

    return 0;
}
