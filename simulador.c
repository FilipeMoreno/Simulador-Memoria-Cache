#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define Tam_Mem 1000

// Variáveis do contador HIT e MISS
int hit = 0, miss = 0;

// menuBusca = 0 (FIFO) | menuBusca = 1 (LRU)
int menuBusca = 0;

// Struct da Memoria Principal
struct memoria_principal
{
    int dado;
    int endereco;
};

// Função para limpar scanf
void limpar(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Função para implementar delay
void delay(int number_of_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + number_of_seconds);
}

// Struct da Cemoria Cache
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

// Variaveis das memorias
struct memoria_principal memP[Tam_Mem];
struct cache cache[2];

// Função para mostrar a memoria cache
int mostrarCache(){

    printf(" |--------------|\n");
    printf(" |-    Cache   -|\n");
    printf(" |--------------|\n");
    // Verifica se existe dados na posição 1 da cache
    if (cache[0].dado == 0){
        printf(" |%i - -/- -/-   |\n", cache[0].endereco);

    // Verifica o endereço de memoria para mostrar na cache (PAR e IMPAR)
    } if (cache[0].end_mem % 2 == 0 && cache[0].dado != 0) {
        printf(" |%i - %i %i |\n", cache[0].endereco, cache[0].par, cache[0].impar);

    } else if (cache[0].end_mem % 2 != 0 && cache[0].dado != 0){
        printf(" |%i - %i %i |\n", cache[0].endereco, cache[0].par, cache[0].impar);
    }

    // Verifica se existe dados na posição 2 da cache
    if (cache[1].dado == 0){
        printf(" |%i - -/- -/-   |\n", cache[1].endereco);

    } if (cache[1].end_mem % 2 == 0 && cache[1].dado != 0) {
        printf(" |%i - %i %i |\n", cache[1].endereco, cache[1].par, cache[1].impar);

    } else if (cache[1].end_mem % 2 != 0 && cache[1].dado != 0) {
        printf(" |%i - %i %i |\n", cache[1].endereco, cache[1].par, cache[1].impar);
    }
    printf(" |--------------|\n\n");
}

// Função para iniciar a cache
void iniciarCache(){

    // Define como 0 as informações posição 1 e 2 da cache
    cache[0].dado = 0;
    cache[1].dado = 0;
    cache[0].par = 0;
    cache[1].par = 0;
    cache[0].impar = 0;
    cache[1].impar = 0;
    cache[0].qtd = 0;
    cache[1].qtd = 0;

    // Define o endereço das posições da cache
    cache[0].endereco = 1;
    cache[1].endereco = 2;

    printf(" Memoria_Cache gerada. \n");
}

// Função para iniciar a memoria Principal
void iniciarMemoriaPrincipal(){

    int i, x;
    srand(time(NULL));

    // Inicia o arquivo da memoria principal
    FILE *memoriaPrincipal;
    memoriaPrincipal=fopen ("memoriaPrincipal.txt","w+");
    if (!memoriaPrincipal)
    {
        printf ("Ocorreu um erro durante a geração do arquivo 'memoria_principal.txt'");
        exit (1);
    }

    // Gera e define numeros aleatorios de 4 dígitos para a memoria principal
    for (i = 0; i < 1300; i++){
        x = rand() % 9000;
        if (x < 1000){
            x = x + 1000;
        }
        memP[i].endereco = i;
        memP[i].dado = x;

        // Coloca os números gerado no arquivo
        fprintf (memoriaPrincipal, "%i - %i \n", memP[i].endereco, memP[i].dado);
    }
    printf(" Memoria_Principal gerada. \n");
}

// Função para o Write-Back
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

// Função para mostrar os HIT e MISS na tela
void mostrarHitMiss(){
    printf("\t Hit: %i \t Miss: %i \n", hit, miss);
}

// Menu para verificar se o usuário deseja realizar outras operações
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
			if (menuBusca = 1){
                menuLRU();
			} else{
                menu2();
			}
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

// Menu para verificar a função que o usuário deseja realizar
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

void menuLRU(){

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
            buscarCacheLRU();
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


// Função para buscar um dado da memoria principal para a cache
int buscarCache(){

    int x, i, end_mem;
    bool par;
    // Mostra a memoria cache junto com os HIT e MISS
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
        // VERIFICA SE O ENDEREÇO DIGITADO É PAR
        if (memP[end_mem].endereco % 2 == 0){
            cache[0].par = memP[end_mem].dado;
            cache[0].impar = memP[end_mem + 1].dado;
            cache[0].end_par = memP[end_mem].endereco;
            cache[0].end_impar = memP[end_mem + 1].endereco;
        // VERIFICA SE O ENDEREÇO DIGITADO É ÍMPAR
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
        // VERIFICA SE EXISTE DADO NA POSIÇÃO 1 E A POSIÇÃO 2 ESTA VAZIA
    } else if (cache[0].dado != 0 && cache[1].dado == 0){
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
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
        // VERIFICA SE O ENDEREÇO DIGITADO É PAR
        if (memP[end_mem].endereco % 2 == 0){
            cache[1].par = memP[end_mem].dado;
            cache[1].impar = memP[end_mem + 1].dado;
            cache[1].end_par = memP[end_mem].endereco;
            cache[1].end_impar = memP[end_mem + 1].endereco;
        // VERIFICA SE O ENDEREÇO DIGITADO É ÍMPAR
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
    // VERIFICA SE AS 2 POSIÇÕES ESTÃO CHEIAS
    } else if (cache[0].dado != 0 && cache[1].dado != 0) {
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
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
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
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
            // VERIFICA SE FOI O ULTIMO (FIFO)
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
            // VERIFICA SE FOI O ULTIMO (FIFO)
            else if (cache[0].ultimo == true){
                cache[1].dado = memP[end_mem].dado;
                // VERIFICA SE O ENDEREÇO DIGITADO É PAR
                if (memP[end_mem].endereco % 2 == 0){
                    cache[1].par = memP[end_mem].dado;
                    cache[1].impar = memP[end_mem + 1].dado;
                    cache[1].end_par = memP[end_mem].endereco;
                    cache[1].end_impar = memP[end_mem + 1].endereco;
                // VERIFICA SE O ENDEREÇO DIGITADO É IMPAR
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

int buscarCacheLRU(){

    int x, i, end_mem;
    bool par;
    // Mostra a memoria cache junto com os HIT e MISS
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
        // VERIFICA SE O ENDEREÇO DIGITADO É PAR
        if (memP[end_mem].endereco % 2 == 0){
            cache[0].par = memP[end_mem].dado;
            cache[0].impar = memP[end_mem + 1].dado;
            cache[0].end_par = memP[end_mem].endereco;
            cache[0].end_impar = memP[end_mem + 1].endereco;
        // VERIFICA SE O ENDEREÇO DIGITADO É ÍMPAR
        } else if (memP[end_mem].endereco % 2 != 0)  {
            cache[0].par = memP[end_mem -1].dado;
            cache[0].impar = memP[end_mem].dado;
            cache[0].end_par = memP[end_mem - 1].endereco;
            cache[0].end_impar = memP[end_mem].endereco;
        }
        cache[0].end_mem = memP[end_mem].endereco;
        cache[0].qtd++;
        printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
        salvarMemoriaPrincipal();
        miss++;
        mostrarHitMiss();
        mostrarCache();
        system("pause");
        system("@cls||clear");
        menu();
        // VERIFICA SE EXISTE DADO NA POSIÇÃO 1 E A POSIÇÃO 2 ESTA VAZIA
    } else if (cache[0].dado != 0 && cache[1].dado == 0){
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
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
        // VERIFICA SE O ENDEREÇO DIGITADO É PAR
        if (memP[end_mem].endereco % 2 == 0){
            cache[1].par = memP[end_mem].dado;
            cache[1].impar = memP[end_mem + 1].dado;
            cache[1].end_par = memP[end_mem].endereco;
            cache[1].end_impar = memP[end_mem + 1].endereco;
        // VERIFICA SE O ENDEREÇO DIGITADO É ÍMPAR
        } else if (memP[end_mem].endereco % 2 != 0)  {
            cache[1].par = memP[end_mem - 1].dado;
            cache[1].impar = memP[end_mem].dado;
            cache[1].end_par = memP[end_mem - 1].endereco;
            cache[1].end_impar = memP[end_mem].endereco;
        }
        cache[1].end_mem = memP[end_mem].endereco;
        cache[1].qtd++;
        salvarMemoriaPrincipal();
        printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
        miss++;
        mostrarHitMiss();
        mostrarCache();
        system("pause");
        system("@cls||clear");
        menu();
    // VERIFICA SE AS 2 POSIÇÕES ESTÃO CHEIAS
    } else if (cache[0].dado != 0 && cache[1].dado != 0) {
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
        if (cache[0].end_par == memP[end_mem].endereco || cache[0].end_impar == memP[end_mem].endereco)
        {
            printf("\n Dado ja existente na Memoria Cache!\n Hit!\n\n");
            hit++;
            cache[0].qtd++;
            mostrarHitMiss();
            mostrarCache();
            system("pause");
            system("@cls||clear");
            menu();
        }
        // VERIFICA SE O DADO SOLICITADO JÁ EXISTE NA CACHE
        else if (cache[1].end_par == memP[end_mem].endereco || cache[1].end_impar == memP[end_mem].endereco)
        {
            printf("\n Dado ja existente na Memoria Cache!\n Hit!\n\n");
            hit++;
            cache[1].qtd++;
            mostrarHitMiss();
            mostrarCache();
            system("pause");
            system("@cls||clear");
            menu();
        } else {
            if (cache[0].qtd > cache[1].qtd){
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
                cache[0].qtd++;
                salvarMemoriaPrincipal();
                printf("\n Dado carregado para Memoria Cache!\n Miss!\n\n");
                miss++;
                mostrarHitMiss();
                mostrarCache();
                system("pause");
                system("@cls||clear");
                menu();
            }
            else if (cache[1].qtd > cache[0].qtd){
                cache[1].dado = memP[end_mem].dado;
                // VERIFICA SE O ENDEREÇO DIGITADO É PAR
                if (memP[end_mem].endereco % 2 == 0){
                    cache[1].par = memP[end_mem].dado;
                    cache[1].impar = memP[end_mem + 1].dado;
                    cache[1].end_par = memP[end_mem].endereco;
                    cache[1].end_impar = memP[end_mem + 1].endereco;
                // VERIFICA SE O ENDEREÇO DIGITADO É IMPAR
                } else if (memP[end_mem].endereco % 2 != 0)  {
                    cache[1].par = memP[end_mem - 1].dado;
                    cache[1].impar = memP[end_mem].dado;
                    cache[1].end_par = memP[end_mem - 1].endereco;
                    cache[1].end_impar = memP[end_mem].endereco;
                }
                cache[1].end_mem = memP[end_mem].endereco;
                cache[1].qtd++;
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

// FUNÇÃO PARA EDITAR O DADO NA CACHE
int editarCache(){

    int endereco_memoria, new_dado, bloco, x;

    mostrarCache();

    printf("\n Digite o endereco da cache a ser alterada: ");
    scanf("%i", &endereco_memoria);
    endereco_memoria -= 1;

    // VERIFICA SE A CACHE ESTÁ VAZIA
    if (cache[endereco_memoria].dado == 0) {
        printf("\n Voce deve buscar um valor primeiro... \n");
        menu2();
    }

    // VERIFICA SE O ENDEREÇO DIGITADO PELO USUÁRIO É VALIDO
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

// FUNÇÃO PRINCIPAL
main(){

    int i, end_mem, opcao;

    printf("\n ================================================================== \n");
    printf(" Simulador de Memoria Cache \n");
    printf(" Trabalho de Arquitetura e Organizacao de Computadores \n");
    printf(" Informatica - UEM \n");
    printf(" Alunos: \n");
    printf(" Filipe Moreno - RA: 111839 \n");
    printf(" Raul Victor - RA: 111874 \n");
    printf(" ================================================================== \n");
    printf("\n");
    system("pause");
    system("@cls || clear");
    iniciarCache();
    iniciarMemoriaPrincipal();
    delay(500);
    printf("\n Para comecar, escolha uma opcao: \n");
    printf(" 1 - FIFO \n");
    printf(" 2 - LRU \n");
    printf(" -> ");
    scanf("%i", &opcao);
    if (opcao == 1){
        menu2();
    } else if (opcao == 2){
        menuBusca = 1;
        menuLRU();
    } else {
        printf("\n Opcao invalida...");
        main();
    }
}
