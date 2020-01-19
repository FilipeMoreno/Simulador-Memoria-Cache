#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define Tam_Mem 1001

char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int hit = 0, miss = 0;

struct memoria_principal
{
    int dado;
    int endereco;
};

void limpar(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void delay(int number_of_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + number_of_seconds);
}

struct cache
{
    int endereco;
    int end_par;
    int end_impar;
    int par;
    int impar;
    int dado;
    bool ultimo;
    int qtd;
    int end_mem;
};

struct memoria_principal memP[Tam_Mem];
struct cache cache[2];

int mostrarCache(){

    printf(" |--------------|\n");
    printf(" |-    Cache   -|\n");
    printf(" |--------------|\n");
    if (cache[0].dado == 0){
        printf(" |%i - -/- -/-   |\n", cache[0].endereco);

    } if (cache[0].end_mem % 2 == 0 && cache[0].dado != 0) {
        printf(" |%i - %i %i |\n", cache[0].endereco, cache[0].par, cache[0].impar);

    } else if (cache[0].end_mem % 2 != 0 && cache[0].dado != 0){
        printf(" |%i - %i %i |\n", cache[0].endereco, cache[0].par, cache[0].impar);
    }
    if (cache[1].dado == 0){
        printf(" |%i - -/- -/-   |\n", cache[1].endereco);

    } if (cache[1].end_mem % 2 == 0 && cache[1].dado != 0) {
        printf(" |%i - %i %i |\n", cache[1].endereco, cache[1].par, cache[1].impar);

    } else if (cache[1].end_mem % 2 != 0 && cache[1].dado != 0) {
        printf(" |%i - %i %i |\n", cache[1].endereco, cache[1].par, cache[1].impar);
    }
    printf(" |--------------|\n\n");
}

void iniciarCache(){

    cache[0].dado = 0;
    cache[1].dado = 0;
    cache[0].par = 0;
    cache[1].par = 0;
    cache[0].impar = 0;
    cache[1].impar = 0;
    cache[0].endereco = 1;
    cache[1].endereco = 2;

    printf(" Memoria_Cache gerada. \n");
}

void iniciarMemoriaPrincipal(){

    int i, x;
    srand(time(NULL));
    FILE *memoriaPrincipal;
    memoriaPrincipal=fopen ("memoriaPrincipal.txt","w+");
    if (!memoriaPrincipal)
    {
        printf ("Ocorreu um erro durante a geração do arquivo 'memoria_principal.txt'");
        exit (1);
    }

    for (i = 0; i < 1300; i++){
        x = rand() % 9000;
        if (x < 1000){
            x = x + 1000;
        }
        memP[i].endereco = i;
        memP[i].dado = x;
        fprintf (memoriaPrincipal, "%i - %i \n", memP[i].endereco, memP[i].dado);
    }
    printf(" Memoria_Principal gerada. \n");

}

void salvarMemoriaPrincipal(){

    int i;

    FILE *memoriaPrincipal;
    memoriaPrincipal=fopen ("memoriaPrincipal.txt","w+");
    if (!memoriaPrincipal)
    {
        printf ("Ocorreu um erro durante a geração do arquivo 'memoria_principal.txt'");
        exit (1);
    }

    for (i = 0; i < 1300; i++){
        fprintf (memoriaPrincipal, "%i - %i \n", memP[i].endereco, memP[i].dado);
    }
    printf(" Memoria_Principal reescrita. \n");

}

void mostrarHitMiss(){
    printf("\t Hit: %i \t Miss: %i \n", hit, miss);
}

void menu()
{
	int opcao_menu;
    printf("\n Voce deseja realizar outra operacao?\n");
    printf(" 1 - Sim\n");
    printf(" 2 - Nao\n");
    printf(" -> ");
    scanf("%i", &opcao_menu);
    limpar();
    switch (opcao_menu)
    {
        case 1:
			system("@cls||clear");
            menu2();
            break;
        case 2:
            printf("\n");
            printf(" Finalizando o programa...\n");
			printf(" Ate mais!\n");
			break;
        default:
            printf(" Ei, digite uma opcao valida!\n");
            menu();
            break;
    }
}

void menu2(){

    int opcao_menu;

    printf("\n Voce deseja: \n");
    printf(" 1 - Buscar informacao\n");
    printf(" 2 - Alterar informacao\n");
    printf(" -> ");
    scanf("%i", &opcao_menu);
    limpar();
    switch (opcao_menu)
    {
        case 1:
			system("@cls||clear");
            buscarCache();
            break;
        case 2:
			system("@cls||clear");
            editarCache();
            break;
        default:
            printf(" Ei, digite uma opcao valida!\n");
            menu2();
            break;
    }
}

int buscarCache(){

    int x, i, end_mem;
    bool par;

    mostrarCache();
    mostrarHitMiss();

    printf("\n Digite o endereco da memoria principal: ");
    scanf("%i", &end_mem);

    if (end_mem % 2 == 0){
        par = true;
    }

    // VERIFICAÇÃO DAS 2 POSIÇÕES DA CACHE VAZIA
    if (cache[0].dado == 0 && cache[1].dado == 0){
        cache[0].dado = memP[end_mem].dado;
        if (memP[end_mem].endereco % 2 == 0){
            cache[0].par = memP[end_mem].dado;
            cache[0].impar = memP[end_mem + 1].dado;
            cache[0].end_par = memP[end_mem].endereco;
            cache[0].end_impar = memP[end_mem + 1].endereco;
        } else if (memP[end_mem].endereco % 2 != 0)  {
            cache[0].par = memP[end_mem -1].dado;
            cache[0].impar = memP[end_mem].dado;
            cache[0].end_par = memP[end_mem - 1].endereco;
            cache[0].end_impar = memP[end_mem].endereco;
        }
        cache[0].end_mem = memP[end_mem].endereco;
        cache[0].ultimo = true;
        cache[1].ultimo = false;
        printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
        salvarMemoriaPrincipal();
        miss++;
        mostrarHitMiss();
        mostrarCache();
        system("pause");
        system("@cls||clear");
        menu();
    } else if (cache[0].dado != 0 && cache[1].dado == 0){
        if (cache[0].end_par == memP[end_mem].endereco || cache[0].end_impar == memP[end_mem].endereco) {
            printf("\n Dado ja existente na Memoria Cache!\n Hit!\n\n");
            hit++;
            mostrarHitMiss();
            mostrarCache();
            system("pause");
            system("@cls||clear");
            menu();
        }
        cache[1].dado = memP[end_mem].dado;
        if (memP[end_mem].endereco % 2 == 0){
            cache[1].par = memP[end_mem].dado;
            cache[1].impar = memP[end_mem + 1].dado;
            cache[1].end_par = memP[end_mem].endereco;
            cache[1].end_impar = memP[end_mem + 1].endereco;
        } else if (memP[end_mem].endereco % 2 != 0)  {
            cache[1].par = memP[end_mem - 1].dado;
            cache[1].impar = memP[end_mem].dado;
            cache[1].end_par = memP[end_mem - 1].endereco;
            cache[1].end_impar = memP[end_mem].endereco;
        }
        cache[1].end_mem = memP[end_mem].endereco;
        cache[1].ultimo = true;
        cache[0].ultimo = false;
        salvarMemoriaPrincipal();
        printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
        miss++;
        mostrarHitMiss();
        mostrarCache();
        system("pause");
        system("@cls||clear");
        menu();
    } else if (cache[0].dado != 0 && cache[1].dado != 0) {
        if (cache[0].end_par == memP[end_mem].endereco || cache[0].end_impar == memP[end_mem].endereco)
        {
            printf("\n Dado ja existente na Memoria Cache!\n Hit!\n\n");
            hit++;
            mostrarHitMiss();
            mostrarCache();
            system("pause");
            system("@cls||clear");
            menu();
        }
        else if (cache[1].end_par == memP[end_mem].endereco || cache[1].end_impar == memP[end_mem].endereco)
        {
            printf("\n Dado ja existente na Memoria Cache!\n Hit!\n\n");
            hit++;
            mostrarHitMiss();
            mostrarCache();
            system("pause");
            system("@cls||clear");
            menu();
        } else {
            if (cache[1].ultimo == true){
                cache[0].dado = memP[end_mem].dado;
                if (memP[end_mem].endereco % 2 == 0){
                    cache[0].par = memP[end_mem].dado;
                    cache[0].impar = memP[end_mem + 1].dado;
                    cache[0].end_par = memP[end_mem].endereco;
                    cache[0].end_impar = memP[end_mem + 1].endereco;
                } else if (memP[end_mem].endereco % 2 != 0)  {
                    cache[0].par = memP[end_mem - 1].dado;
                    cache[0].impar = memP[end_mem].dado;
                    cache[0].end_par = memP[end_mem - 1].endereco;
                    cache[0].end_impar = memP[end_mem].endereco;
                }
                cache[0].end_mem = memP[end_mem].endereco;
                cache[0].ultimo = true;
                cache[1].ultimo = false;
                salvarMemoriaPrincipal();
                printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
                miss++;
                mostrarHitMiss();
                mostrarCache();
                system("pause");
                system("@cls||clear");
                menu();
            }
            else if (cache[0].ultimo == true){
                cache[1].dado = memP[end_mem].dado;
                if (memP[end_mem].endereco % 2 == 0){
                    cache[1].par = memP[end_mem].dado;
                    cache[1].impar = memP[end_mem + 1].dado;
                    cache[1].end_par = memP[end_mem].endereco;
                    cache[1].end_impar = memP[end_mem + 1].endereco;
                } else if (memP[end_mem].endereco % 2 != 0)  {
                    cache[1].par = memP[end_mem - 1].dado;
                    cache[1].impar = memP[end_mem].dado;
                    cache[1].end_par = memP[end_mem - 1].endereco;
                    cache[1].end_impar = memP[end_mem].endereco;
                }
                cache[1].end_mem = memP[end_mem].endereco;
                cache[1].ultimo = true;
                cache[0].ultimo = false;
                salvarMemoriaPrincipal();
                printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
                miss++;
                mostrarHitMiss();
                mostrarCache();
                system("pause");
                system("@cls||clear");
                menu();
            }
        }
    }
}

int editarCache(){

    int endereco_memoria, new_dado, bloco, x;

    mostrarCache();

    printf("\n Digite o endereco da cache a ser alterada: ");
    scanf("%i", &endereco_memoria);
    endereco_memoria -= 1;

    if (cache[endereco_memoria].dado == 0) {
        printf("\n Voce deve buscar um valor primeiro... \n");
        menu2();
    }

    if (endereco_memoria > 1 || endereco_memoria < 0 ){
        printf("\n Endereco invalido... \n");
        editarCache();
    }

    printf("\b Digite o bloco que deseja editar (1 ou 2): ");
    scanf("%i", &bloco);

    if (bloco < 0 || bloco > 2){
        printf("\n Bloco invalido... \n\n");
        editarCache();
    }

    printf("\n Digite o novo dado: (Ex: 0000): ");
    scanf("%i", &new_dado);

    if (bloco == 1){
        cache[endereco_memoria].par = new_dado;
        x = cache[endereco_memoria].end_par;
        memP[x].dado = cache[endereco_memoria].par;
    } else if (bloco == 2){
        cache[endereco_memoria].impar = new_dado;
        x = cache[endereco_memoria].end_impar;
        memP[x].dado = cache[endereco_memoria].impar;
    }
    printf("\n Dado alterado com sucesso! \n");

    mostrarCache();
    menu();

}

main(){

    int i, end_mem;

    iniciarCache();
    iniciarMemoriaPrincipal();
    delay(500);
    printf("\n ================================================================== \n");
    printf(" Trabalho de Arquitetura e Organizacao de Computadores \n");
    printf(" Informatica - UEM \n");
    printf(" ================================================================== \n");
    printf("\n");
    system("pause");
    system("@cls || clear");
    menu2();

}
