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

// Exibir territórios
void exibirMapa(Territorio *mapa, int total) {

    printf("\n=== MAPA DE TERRITORIOS ===\n");

    for(int i = 0; i < total; i++) {

        printf("\nTerritorio %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("Dado atacante: %d\n", dadoAtacante);
    printf("Dado defensor: %d\n", dadoDefensor);

    if(dadoAtacante > dadoDefensor) {

        printf("Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    }
    else {

        printf("Defensor venceu!\n");

        atacante->tropas--;

        if(atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

// Função que sorteia missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {

    int sorteio = rand() % totalMissoes;

    strcpy(destino, missoes[sorteio]);
}

// Exibir missão (passagem por valor)
void exibirMissao(char* missao) {

    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n", missao);
}

// Verificar missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    int territoriosAzuis = 0;

    for(int i = 0; i < tamanho; i++) {

        if(strcmp(mapa[i].cor, "Azul") == 0)
            territoriosAzuis++;
    }

    // Exemplo simples de verificação
    if(territoriosAzuis >= 3)
        return 1;

    return 0;
}

// Liberar memória
void liberarMemoria(Territorio* mapa, char* missao) {

    free(mapa);
    free(missao);
}

int main() {

    srand(time(NULL));

    int total;

    printf("=== WAR ESTRUTURADO ===\n");

    printf("Digite o numero de territorios: ");
    scanf("%d", &total);

    // Alocação dinâmica de territórios
    Territorio *mapa = (Territorio*) calloc(total, sizeof(Territorio));

    cadastrarTerritorios(mapa, total);

    exibirMapa(mapa, total);

    // Vetor de missões
    char* missoes[] = {

        "Conquistar 3 territorios",
        "Eliminar todas as tropas vermelhas",
        "Controlar metade do mapa",
        "Dominar territorios com mais de 10 tropas",
        "Conquistar territorios consecutivos"
    };

    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = (char*) malloc(200 * sizeof(char));

    // Sorteio da missão
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // Mostrar missão apenas uma vez
    exibirMissao(missaoJogador);

    int atacante, defensor;

    printf("\nEscolha territorio atacante: ");
    scanf("%d", &atacante);

    printf("Escolha territorio defensor: ");
    scanf("%d", &defensor);

    // Validação de ataque
    if(atacante == defensor) {

        printf("Erro: territorio nao pode atacar a si mesmo.\n");
    }
    else if(strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {

        printf("Erro: nao pode atacar territorio aliado.\n");
    }
    else {

        atacar(&mapa[atacante], &mapa[defensor]);
    }

    // Mostrar mapa atualizado
    exibirMapa(mapa, total);

    // Verificar missão
    if(verificarMissao(missaoJogador, mapa, total)) {

        printf("\nMISSÃO CUMPRIDA! VOCE VENCEU!\n");
    }

    // Liberar memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}