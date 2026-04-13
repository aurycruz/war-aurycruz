#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int total) {
    for(int i = 0; i < total; i++) {

        printf("\nCadastro do Territorio %d\n", i + 1);

        printf("Nome do territorio: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void mostrarTerritorios(Territorio *mapa, int total) {

    printf("\n=== MAPA DE TERRITORIOS ===\n");

    for(int i = 0; i < total; i++) {
        printf("\nTerritorio %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Se atacante vencer
    if(dadoAtacante > dadoDefensor) {

        printf("O atacante venceu!\n");

        // território defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // metade das tropas do atacante vão para o território conquistado
        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    }
    else {

        printf("O defensor venceu!\n");

        // atacante perde uma tropa
        atacante->tropas -= 1;

        if(atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {

    int total;

    // Inicializa gerador de números aleatórios
    srand(time(NULL));

    printf("=== WAR - Simulador de Ataque ===\n");

    printf("Digite o numero de territorios: ");
    scanf("%d", &total);

    // Alocação dinâmica de memória
    Territorio *mapa = (Territorio*) calloc(total, sizeof(Territorio));

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, total);

    // Mostrar territórios cadastrados
    mostrarTerritorios(mapa, total);

    int atacante, defensor;

    printf("\nEscolha o territorio atacante (numero): ");
    scanf("%d", &atacante);

    printf("Escolha o territorio defensor (numero): ");
    scanf("%d", &defensor);

    // Validação básica
    if(atacante == defensor) {
        printf("Erro: um territorio nao pode atacar ele mesmo.\n");
    }
    else if(strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Erro: nao pode atacar territorio da mesma cor.\n");
    }
    else {
        atacar(&mapa[atacante], &mapa[defensor]);
    }

    // Mostrar mapa após ataque
    mostrarTerritorios(mapa, total);

    // Liberação de memória
    liberarMemoria(mapa);

    return 0;
}