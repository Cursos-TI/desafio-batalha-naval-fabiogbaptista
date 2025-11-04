#include <stdio.h>

// --- DEFINIÇÕES GLOBAIS ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3 // Todos os navios terão tamanho 3

int main() {

    char linha[TAMANHO_TABULEIRO] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0}; 
    
    // Declara os vetores dos navios
    int navio1[TAMANHO_NAVIO] = {3, 3, 3};
    int navio2[TAMANHO_NAVIO] = {3, 3, 3};
    int navio3[TAMANHO_NAVIO] = {3, 3, 3}; // Novo navio diagonal
    int navio4[TAMANHO_NAVIO] = {3, 3, 3}; // Novo navio antidiagonal

    
    // --- 1. ENTRADA DAS COORDENADAS ---
    
    // Navio 1: Horizontal
    int navio1_linha = 2;
    int navio1_coluna_inicio = 2;

    // Navio 2: Vertical
    int navio2_linha_inicio = 5;
    int navio2_coluna = 5;

    // Navio 3: Diagonal (linha e coluna aumentam)
    int navio3_linha_inicio = 7;
    int navio3_coluna_inicio = 0;

    // Navio 4: Antidiagonal (linha aumenta, coluna diminui)
    int navio4_linha_inicio = 7;
    int navio4_coluna_inicio = 9;
    
    
    printf("Iniciando validacao dos navios...\n");

    
    // --- 2. VALIDAÇÃO DE LIMITES ---
    
    int erro_limite = 0; // 0 = Falso (OK), 1 = Verdadeiro (Erro)

    // Valida Navio 1 (Horizontal)
    if (navio1_linha < 0 || navio1_linha >= TAMANHO_TABULEIRO || 
        navio1_coluna_inicio < 0 || (navio1_coluna_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO)) {
        printf("ERRO: Navio 1 (Horizontal) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Valida Navio 2 (Vertical)
    if (navio2_coluna < 0 || navio2_coluna >= TAMANHO_TABULEIRO ||
        navio2_linha_inicio < 0 || (navio2_linha_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO)) {
        printf("ERRO: Navio 2 (Vertical) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Valida Navio 3 (Diagonal)
    // Precisa checar se a linha E a coluna estouram os limites
    if (navio3_linha_inicio < 0 || (navio3_linha_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) ||
        navio3_coluna_inicio < 0 || (navio3_coluna_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO)) {
        printf("ERRO: Navio 3 (Diagonal) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Valida Navio 4 (Antidiagonal)
    // Precisa checar se a linha estoura para baixo e a coluna estoura para a esquerda (menor que 0)
    if (navio4_linha_inicio < 0 || (navio4_linha_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) ||
        navio4_coluna_inicio < 0 || (navio4_coluna_inicio - (TAMANHO_NAVIO - 1) < 0) || // Checa se a coluna final é < 0
        navio4_coluna_inicio >= TAMANHO_TABULEIRO) {
        printf("ERRO: Navio 4 (Antidiagonal) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Se qualquer erro foi encontrado, encerra o programa
    if (erro_limite == 1) {
        printf("Posicionamento falhou. Verifique as coordenadas.\n");
        return 1; // Retorna 1 para indicar que o programa terminou com erro
    }
    
    printf("Validacao de Limites: OK\n");


    // --- 3. POSICIONAMENTO E VALIDAÇÃO DE SOBREPOSIÇÃO ---
    // (A lógica é: posiciona um, depois checa o próximo antes de posicionar)

    // Posiciona o Navio 1
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio1_linha][navio1_coluna_inicio + i] = navio1[i];
    }

    // Checa e posiciona o Navio 2
    int erro_sobreposicao = 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[navio2_linha_inicio + i][navio2_coluna] != 0) {
            erro_sobreposicao = 1;
            break;
        }
    }
    if (erro_sobreposicao) {
        printf("ERRO: Navio 2 sobrepoe Navio 1!\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio2_linha_inicio + i][navio2_coluna] = navio2[i];
    }

    // Checa e posiciona o Navio 3 (Diagonal)
    erro_sobreposicao = 0; // Reseta a flag de erro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Checa a posição [linha+i][coluna+i]
        if (tabuleiro[navio3_linha_inicio + i][navio3_coluna_inicio + i] != 0) {
            erro_sobreposicao = 1;
            break;
        }
    }
    if (erro_sobreposicao) {
        printf("ERRO: Navio 3 sobrepoe um navio existente!\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio3_linha_inicio + i][navio3_coluna_inicio + i] = navio3[i];
    }
    
    // Checa e posiciona o Navio 4 (Antidiagonal)
    erro_sobreposicao = 0; // Reseta a flag de erro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Checa a posição [linha+i][coluna-i]
        if (tabuleiro[navio4_linha_inicio + i][navio4_coluna_inicio - i] != 0) {
            erro_sobreposicao = 1;
            break;
        }
    }
    if (erro_sobreposicao) {
        printf("ERRO: Navio 4 sobrepoe um navio existente!\n");
        return 1;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio4_linha_inicio + i][navio4_coluna_inicio - i] = navio4[i];
    }


    printf("Validacao de Sobreposicao: OK\n");
    printf("Todos os navios posicionados com sucesso.\n");


    // --- 4. EXIBIR O TABULEIRO ---
    
    printf("\nTABULEIRO DE BATALHA NAVAL\n");
    
    printf("  "); 
    for(int j = 0; j < TAMANHO_TABULEIRO; j++){
        printf("%c ", linha[j]); 
    }
    printf("\n"); 

    for(int i = 0; i < TAMANHO_TABULEIRO; i++) { 
        printf("%d ", i); 
        
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) { 
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n"); 
    }

    return 0; // Sucesso
}
