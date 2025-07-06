#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(){
    int opcion;
    do{
        printf("\n= = = = MENU PRINCIPAL = = = =\n");
        printf("1 - Listas\n");
        printf("2 - Pilas\n");
        printf("3 - Colas\n");
        printf("4 - Arboles Binarios\n");
        printf("5 - Arboles N-arios\n");
        printf("6 - Arboles Binarios de Busqueda\n");
        printf("0 - Salir\n");

        printf("\nSeleccione una opcion -> ");
        scanf("%d",&opcion);

        switch (opcion)
        {
        case 1:
            break;
        
        case 4:
            break;
        
        case 0:
            printf("\nChau puta\n");
            system("pause");
            break;
            
        default:
            printf("Opcion invalida (como vos, parece...)\n");
            system("pause");
            break;
        }

        system("cls");
    } while (opcion != 0);
    return 0;
}