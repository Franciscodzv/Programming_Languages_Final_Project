#ifndef TABLA_VERDAD_H_INCLUDED
#define TABLA_VERDAD_H_INCLUDED

//Las siguientes funciones:
//
//  presedencia
//  aplicar_operacion
//  validar_expresion
//  evaluar_expresion
//
//Fueron adaptadas de:
//  https://www.geeksforgeeks.org/expression-evaluation/

#include <ctype.h>      //Funcion isalpha
#include <math.h>       //Funcion pow
#include <string.h>     //Funcion strcpy

#define MAX 200 //El tamaño maximo de una expresion

//Procedimiento recibe un operador logico
//o un parentesis y devuelve su jerarquia.
int presedencia(char operador)
{
    if(operador == '~')return 5;
    if(operador == '&')return 4;
    if(operador == '|')return 3;
    if(operador == '>')return 2;
    if(operador == '=')return 1;
    return 0;
}

//Procedimiento que recibe dos operandos y un operador
//logico y devuelve el resultado de aplicarles esa
//operacion. Si el operador es el NOT se ignora el
//segundo parametro.
int aplicar_operacion(int a, int b, char operador)
{
    switch(operador)
    {
        case '~': return (!a);
        case '&': return a & b;
        case '|': return a | b;
        case '>': return (!a) | b;
        case '=': return ((!a) | b) & ((!b) | a);
    }
    return 0;
}

//Funcion que recibe una expresion logica y
//regresa 1 si la expresion evalua a True y
//regresa 0 si la expresion evalua a False.
//Se asume que la expresion tiene como
//operandos solo True y False ('T' y 'F').
int evaluar_expresion(char expresion[])
{
    //Pila para los valores (operandondos)
    int pila_val[MAX];
    //Tamaño de la pila de valores
    int tam_val = 0;

    //Pila para los operadores
    char pila_op[MAX];
    //Tamaño de la pila de operadores
    int tam_op = 0;

    //Recorrer toda la expresion caracter por caracter
    int i = -1;
    for(i = 0; expresion[i] != '\0' ; i++)
    {
        //Si el caracter es un espacio, continuar con
        //la siguiente iteracion
        if(expresion[i] == ' ')
        {
            continue;
        }
        //Si el caracter es un parentesis de apertura,
        //guardar en la pila de valores
        else if(expresion[i] == '(')
        {
            pila_op[tam_op] = expresion[i];
            tam_op++;
        }
        //Si el caracter es T (True)
        //guardar en la pila de valores
        else if(expresion[i] == 'T')
        {
            pila_val[tam_val] = 1;
            tam_val++;
        }
        //Si el caracter es F (False)
        //guardar en la pila de valores
        else if(expresion[i] == 'F')
        {
            pila_val[tam_val] = 0;
            tam_val++;
        }
        //Si el caracter es un parentesis de cierre:
        else if(expresion[i] == ')')
        {
            //Mientras el valor de la cima de la pila
            //de operandores no sea un parentesis de apertura
            while(tam_op > 0 && pila_op[tam_op - 1] != '(')
            {
                int a = 0;
                int b = 0;

                //Si el operador en la cima de la pila
                //operadores es el NOT, sacar un valor de la
                //pila de valores, sino sacar dos valores
                if(pila_op[tam_op-1] == '~')
                {
                    a = pila_val[tam_val - 1];
                    tam_val--;
                }
                else
                {
                    b = pila_val[tam_val - 1];
                    tam_val--;
                    a = pila_val[tam_val - 1];
                    tam_val--;
                }

                //Sacar un operador de la pila de operadores,
                //aplicar la operacion a los valores y guardar el resultado
                //en la pila de valores
                int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
                tam_op--;
                pila_val[tam_val] = res;
                tam_val++;
            }
            //Sacar el parentesis de apertura de la pila de operadores
            tam_op--;
        }
        //El caracter es un operador
        else
        {
            //Mientras la pila de operadores no este vacia
            //y el operador en la cima de la pila de operadores tenga
            //mayor presedencia que el caracter
            while(tam_op > 0 && presedencia(pila_op[tam_op-1]) > presedencia(expresion[i]))
            {
                int a = 0;
                int b = 0;

                //Si el operador en la cima de la pila
                //operadores es el NOT, sacar un valor de la
                //pila de valores, sino sacar dos valores
                if(pila_op[tam_op-1] == '~')
                {
                    a = pila_val[tam_val - 1];
                    tam_val--;
                }
                else
                {
                    b = pila_val[tam_val - 1];
                    tam_val--;
                    a = pila_val[tam_val - 1];
                    tam_val--;
                }

                //Sacar un operador de la pila de operadores,
                //aplicar la operacion a los valores y guardar el resultado
                //en la pila de valores
                int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
                tam_op--;
                pila_val[tam_val] = res;
                tam_val++;
            }

            //Guardar el operador en la pila de operadores
            pila_op[tam_op] = expresion[i];
            tam_op++;
        }
    }

    //Mientras la pila de operadores no este vacia
    while(tam_op > 0)
    {
        int a = 0;
        int b = 0;

        //Si el operador en la cima de la pila
        //operadores es el NOT, sacar un valor de la
        //pila de valores, sino sacar dos valores
        if(pila_op[tam_op-1] == '~')
        {
            a = pila_val[tam_val - 1];
            tam_val--;
        }
        else
        {
            b = pila_val[tam_val - 1];
            tam_val--;
            a = pila_val[tam_val - 1];
            tam_val--;
        }

        //Sacar un operador de la pila de operadores,
        //aplicar la operacion a los valores y guardar el resultado
        //en la pila de valores
        int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
        tam_op--;
        pila_val[tam_val] = res;
        tam_val++;
    }

    //Regresa el resultado de la evaluacion
    return pila_val[tam_val-1];
}
//Funcion que recibe una expresion logica y
//devuelve 1 si la expresion esta bien estructurada y
//usa caracteres validos de otro modo regresa un 0.
int validar_expresion(char expresion[])
{
    //Validar que todos los caracteres sean validos
    char validos[8] = {'~','&','|','>','=','(',')',' '};
    char anterior = ' ';
    int caracter_valido = 1;
    int i = -1;
    for(i = 0; expresion[i] != '\0'; i++)
    {
        //Si hay un par de parentesis vacios regresa 0
        if(anterior == '(' && expresion[i] == ')')
            return 0;

        if(expresion[i] != ' ')
            anterior = expresion[i];

        //Asumir que el caracter es invalido
        caracter_valido = 0;

        if(isalpha(expresion[i]))
            caracter_valido = 1;

        int j = 0;
        for(j = 0; j < 8; j++)
            if(expresion[i] == validos[j])
                caracter_valido = 1;

        if(!caracter_valido)
            return 0;
    }

    //Pila para los valores (operandos)
    int pila_val[MAX];
    //Tamaño de la pila de valores
    int tam_val = 0;

    //Pila para los operadores
    char pila_op[MAX];
    //Tamaño de la pila de operadores
    int tam_op = 0;

    //Recorrer la expresion caracter por caracter
    for(i = 0; expresion[i] != '\0' ; i++)
    {
        //Si el caracter es un espacio, continuar con
        //la siguiente iteracion
        if(expresion[i] == ' ')
        {
            continue;
        }
        //Si el caracter es un parentesis de apertura,
        //guardar en la pila de valores
        else if(expresion[i] == '(')
        {
            pila_op[tam_op] = expresion[i];
            tam_op++;
        }
        //Si el caracter es una variable proposicional
        //guardar un 1 en la pila de valores
        else if(isalpha(expresion[i]))
        {
            pila_val[tam_val] = 1;
            tam_val++;
        }

        //Si el caracter es un parentesis de cierre:
        else if(expresion[i] == ')')
        {
            //Mientras el valor de la cima de la pila
            //de operandores no sea un parentesis de apertura
            while(tam_op > 0 && pila_op[tam_op-1] != '(')
            {
                int a = 0;
                int b = 0;

                //Si el operador en la cima de la pila
                //operadores es el NOT, sacar un valor de la
                //pila de valores, sino sacar dos valores
                if(pila_op[tam_op-1] == '~')
                {
                    //Si la pila de valores esta vacia,
                    //regresa 0
                    if(tam_val < 1)
                        return 0;

                    a = pila_val[tam_val-1];
                    tam_val--;
                }
                else
                {
                    //Si la pila de valores tiene menos
                    //de 2 valores, regresa 0
                    if(tam_val < 2)
                        return 0;

                    b = pila_val[tam_val-1];
                    tam_val--;
                    a = pila_val[tam_val-1];
                    tam_val--;
                }

                //Sacar un operador de la pila de operadores,
                //aplicar la operacion a los valores y guardar el resultado
                //en la pila de valores
                int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
                tam_op--;
                pila_val[tam_val] = res;
                tam_val++;
            }
            //Si la pila de operadores esta vacia
            if(tam_op == 0)
                return 0;

            //Sacar el parentesis de apertura de la pila de operadores
            tam_op--;
        }
        //El caracter es un operador
        else
        {
            //Mientras la pila de operadores no este vacia
            //y el operador en la cima de la pila de operadores tenga
            //mayor presedencia que el caracter
            while(tam_op > 0 && presedencia(pila_op[tam_op-1]) > presedencia(expresion[i]))
            {
                int a = 0;
                int b = 0;

                //Si el operador en la cima de la pila
                //operadores es el NOT, sacar un valor de la
                //pila de valores, sino sacar dos valores
                if(pila_op[tam_op-1] == '~')
                {
                    //Si la pila de valores esta vacia,
                    //regresa 0
                    if(tam_val < 1)
                        return 0;

                    a = pila_val[tam_val-1];
                    tam_val--;
                }
                else
                {
                    //Si la pila de valores tiene menos
                    //de 2 valores, rhttps://www.geeksforgeeks.org/expression-evaluation/egresa 0
                    if(tam_val < 2)
                        return 0;

                    b = pila_val[tam_val-1];
                    tam_val--;
                    a = pila_val[tam_val-1];
                    tam_val--;
                }

                //Sacar un operador de la pila de operadores,
                //aplicar la operacion a los valores y guardar el resultado
                //en la pila de valores
                int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
                tam_op--;
                pila_val[tam_val] = res;
                tam_val++;
            }

            //Guardar el operador en la pila de operadores
            pila_op[tam_op] = expresion[i];
            tam_op++;
        }
    }

    //Mientras la pila de operadores no este vacia
    while(tam_op > 0)
    {
        int a = 0;
        int b = 0;

        //Si el operador en la cima de la pila
        //operadores es el NOT, sacar un valor de la
        //pila de valores, sino sacar dos valores
        if(pila_op[tam_op-1] == '~')
        {
            //Si la pila de valores esta vacia,
            //regresa 0
            if(tam_val < 1)
                return 0;

            a = pila_val[tam_val-1];
            tam_val--;
        }
        else
        {
            //Si la pila de valores tiene menos
            //de 2 valores, regresa 0
            if(tam_val < 2)
                return 0;

            b = pila_val[tam_val-1];
            tam_val--;
            a = pila_val[tam_val-1];
            tam_val--;
        }

        //Sacar un operador de la pila de operadores,
        //aplicar la operacion a los valores y guardar el resultado
        //en la pila de valores
        int res = aplicar_operacion(a, b, pila_op[tam_op-1]);
        tam_op--;
        pila_val[tam_val] = res;
        tam_val++;
    }

    //Si la pila de valores no tiene exactamente un elemento
    //o la pila de operadores no esta vacia, regresa 0
    if(tam_val != 1 || tam_op != 0)
        return 0;

    //La expresion es valida
    return 1;
}

//Funcion que recibe una cadena y
//regresa la cantidad de caracteres
//que tiene
int calcular_longitud(char cadena[])
{
    int i;
    for (i = 0; cadena[i] != '\0'; i++);
    return i;
}

//Recibe un numero de variables proposicionales,
//el ancho de un expresion y un apuntador a un archivo,
//y guarda en el archivo una linea que sirve para separar
//las filas de una tabla de verdad
void imprimir_separador(int num_var, int ancho, FILE * archivo)
{
    fprintf(archivo, "+");
    int i;
    for(i = 0; i < num_var; i++)
    {
        fprintf(archivo, "-----+");
    }
    for(i = 0; i < ancho + 4; i++)
    {
        fprintf(archivo, "-");
    }
    fprintf(archivo, "+\n");
}

//Procedimiento que imprime el encabezado de una tabla de verdad
//Recibe los siguientes parametros:
//encontrado: arreglo de 0s y 1s que indica para cada caracter si es
//variable de la expresion
//expresion: una expresion logica
//archivo: un apuntador al archivo donde se guarda
void imprimir_encabezado(int encontrado[], char expresion[], FILE * archivo)
{
    fprintf(archivo,"|");
    int i;
    //Revisar todas las posibles variables
    for (i = 0; i < 130; i++)
    {
        if (encontrado[i])
        {
            fprintf(archivo,"  %c  |", i);
        }
    }
    fprintf(archivo,"  %s  |\n", expresion);
}

//Procedimiento que guarda en un archivo una fila de una tabla de verdad
//en base a una posible sustitucion de las variables proposicionales
//encontrado: arreglo de 0s y 1s que indica para cada caracter si es
//variable de la expresion
//expresion: una expresion logica
//indice: arreglo que indica para cada varible de la expresion que indice
//se le asigno
//Bitmask: una mascara de bits que indica para cada variable de
//la expresion si se sustituye por False o por True
//ancho: el tamaño de la expresion
//archivo: un apuntador al archivo donde se guarda
void imprimir_fila(int encontrado[], char expresion[], int indice[], int bitmask, int ancho, FILE * archivo)
{
    //Guardar en archivo las celdas de los valores
    //de las variables de la expresion en base a bitmask
    char copia[MAX];
    fprintf(archivo,"|");
    int i;
    for (i = 0; i < 130; i++)
    {
        if(encontrado[i])
        {
            int indx = indice[i];//archivo: un apuntador al archivo donde se guarda
            if((bitmask >> indx) & 1)
            {
                fprintf(archivo,"  T  |");
            }
            else
            {
                fprintf(archivo,"  F  |");
            }
        }
    }

    //Crear una copia de la expresion
    strcpy(copia, expresion);

    //Sustituir las variables de la copi//archivo: un apuntador al archivo donde se guardaa
    int j;
    for(j = 0; copia[j] != '\0'; j++)
    {
        if(isalpha(copia[j]) && expresion[i] != 'T' && expresion[i] != 'F')
        {
            int letra = copia[j];
            int indx = indice[letra];
            if((bitmask >> indx) & 1)
            {
                copia[j] = 'T';
            }
            else
            {
                copia[j] = 'F';
            }
        }
    }

    //Calcular el resultado de evaluar la expresion
    int valor_verdad = evaluar_expresion(copia);
    int k;

    //Guardar en archivo la celda del resultado
    int posicion_variable = (ancho + 5) / 2;
    for (k = 1; k <= ancho + 4; k++)
    {
        if(k == posicion_variable)
        {
            if(valor_verdad)
            {
                fprintf(archivo, "T");
            }
            else
            {
                fprintf(archivo, "F");
            }
        }
        else
        {
            fprintf(archivo, " ");
        }
    }
    fprintf(archivo, "|\n");
}

//Procedimiento que recibe una expresion logica y el nombre de un archivo
//de salida y genera su tabla de verdad y la guarda
//en el archivo de salida. Se asume que la expresion es valida
void generar_tabla(char expresion[MAX], char nombre_archivo_salida[])
{
    //Indica el indice que se le asigna a cada variable de la expresion
    int indice[MAX];
    //Indica para cada caracter si es variable de la expresion
    int encontrado[MAX];
    int num_variables = 0;

    //Declarar y abrir archivo de salida
    FILE * archivo = fopen(nombre_archivo_salida, "w");
    fprintf(archivo, "Tabla de verdad de: %s\n\n", expresion);

    //Inicializar arreglo de encontrados
    int i = -1;
    for(i = 0; i < 200; i++)
    {
        encontrado[i] = 0;
    }

    //Asignar un indice a cada variable de la expresion
    for(i = 0; expresion[i] != '\0'; i++)
    {
        if(isalpha(expresion[i]))
        {
            int letra = expresion[i];
            if(encontrado[letra] == 0 &&
               expresion[i] != 'T' && expresion[i] != 'F')
               {
                    encontrado[letra] = 1;
                    indice[letra] = num_variables;
                    num_variables++;
               }
        }
    }

    //Imprimir el encabezado de la tabla
    int ancho = calcular_longitud(expresion);
    imprimir_separador(num_variables, ancho,archivo);
    imprimir_encabezado(encontrado, expresion,archivo);
    imprimir_separador(num_variables, ancho, archivo);

    //Evaluar cada sustitucion
    int num_renglones = pow(2, num_variables);
    int bitmask;
    for(bitmask = num_renglones - 1; bitmask >= 0; bitmask--)
    {
        imprimir_fila(encontrado, expresion, indice, bitmask, ancho, archivo);
        imprimir_separador(num_variables, ancho, archivo);
    }

    //cerrar archivo
    fclose(archivo);
}

#endif // TABLA_VERDAD_H_INCLUDED
