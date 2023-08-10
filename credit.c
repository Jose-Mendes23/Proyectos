#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long numero_de_tarjeta;
    printf("Ingrese su numero de tarjeta: ");
    scanf("%ld", &numero_de_tarjeta);

    // Inicio del algoritmo del Lunh

    int suma = 0;
    int par = 0;
    long t = numero_de_tarjeta;

    while(t > 0){
        int digito = t % 10;
        t /= 10;

        if(par){
            digito *= 2;

            if(digito > 9){
                digito = (digito % 10) + 1;
            }
        }
        suma += digito;
        par =! par;
    }

    //Identificamos el Banco

    int longitud = 0;
    t = numero_de_tarjeta;

    while(t > 0){
        t /= 10;
        longitud ++;
    }

    int primer_digito = numero_de_tarjeta / 1000000000000000;
    int dos_primeros = (numero_de_tarjeta / 100000000000000) % 100;

    if ((suma % 10) == 0){

        if (longitud == 15 && primer_digito == 3 && (dos_primeros == 34 || dos_primeros == 37)){
            printf("AMEX\n");
        }
        else if ((longitud == 13 || longitud == 16) && primer_digito == 4){
            printf("VISA\n");
        }
        else if (longitud == 16 && dos_primeros >= 51 && dos_primeros <= 55){
            printf("MASTERCARD\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }
    return 0;
}


