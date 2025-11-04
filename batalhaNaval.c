#include <stdio.h>

int main() {

    char linha[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int tabuleiro[10][10] = {0}; 
    
    // Declara os vetores dos navios
    int navio1[3] = {3, 3, 3};
    int navio2[3] = {3, 3, 3};

    
    // --- 1. ENTRADA DAS COORDENADAS ---
        
    // Navio 1: Horizontal
    int navio1_linha = 2;
    int navio1_coluna_inicio = 2;

    // Navio 2: Vertical
    int navio2_linha_inicio = 3;
    int navio2_coluna = 8;
    
    printf("Iniciando validacao dos navios...\n");

    
    // --- 2. VALIDAÇÃO DE LIMITES ---
    // Checa se os navios cabem dentro do tabuleiro 10x10
    
    int erro_limite = 0; // 0 = Falso (OK), 1 = Verdadeiro (Erro)

    // Valida Navio 1 (Horizontal)
    if (navio1_linha < 0 || navio1_linha >= 10 || 
        navio1_coluna_inicio < 0 || (navio1_coluna_inicio + 3 > 10)) {
        
        printf("ERRO: Navio 1 (Horizontal) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Valida Navio 2 (Vertical)
    if (navio2_coluna < 0 || navio2_coluna >= 10 ||
        navio2_linha_inicio < 0 || (navio2_linha_inicio + 3 > 10)) {
        
        printf("ERRO: Navio 2 (Vertical) esta fora dos limites do tabuleiro!\n");
        erro_limite = 1;
    }

    // Se 'erro_limite' for 1, encerra o programa
    if (erro_limite == 1) {
        printf("Posicionamento falhou. Verifique as coordenadas.\n");
        return 1; // Retorna 1 para indicar que o programa terminou com erro
    }
    
    printf("Validacao de Limites: OK\n");


    // --- 3. POSICIONAMENTO E VALIDAÇÃO DE SOBREPOSIÇÃO ---

    // Primeiro, posicionamos o Navio 1 no tabuleiro
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio1_linha][navio1_coluna_inicio + i] = navio1[i];
    }

    // Agora, ANTES de posicionar o Navio 2, checamos se ele se sobrepõe ao Navio 1
    int erro_sobreposicao = 0;
    for (int i = 0; i < 3; i++) {
        // Verifica se a célula que o Navio 2 quer usar já está ocupada (== 3)
        if (tabuleiro[navio2_linha_inicio + i][navio2_coluna] != 0) {
            erro_sobreposicao = 1;
            break; // Já sabemos que sobrepõe, podemos parar o loop
        }
    }

    // Se 'erro_sobreposicao' for 1, encerra o programa
    if (erro_sobreposicao == 1) {
        printf("ERRO: Os navios estao se sobrepondo!\n");
        printf("Posicionamento falhou.\n");
        return 1; // Termina com erro
    }

    printf("Validacao de Sobreposicao: OK\n");

    // Se chegou até aqui, é seguro posicionar o Navio 2
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio2_linha_inicio + i][navio2_coluna] = navio2[i];
    }


    // --- 4. EXIBIR O TABULEIRO ---
    // Esta parte só será executada se todas as validações passarem
    
    printf("\nTABULEIRO DE BATALHA NAVAL\n");
    
    // Imprime o cabeçalho das colunas (A-J)
    printf("  "); 
    for(int j = 0; j < 10; j++){
        printf("%c ", linha[j]); 
    }
    printf("\n"); 

    // Imprime as linhas e o conteúdo do tabuleiro
    for(int i = 0; i < 10; i++) { 
        printf("%d ", i); 
        
        for(int j = 0; j < 10; j++) { 
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n"); 
    }

    return 0; // Sucesso
}
