#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100
#define MAX_TEXTO 100


typedef struct {
    int id;
    char descricao[MAX_TEXTO];
} Tarefa;


void exibirMenu() {
    printf("\n--- Sistema de Gerenciamento de Tarefas ---\n");
    printf("1. Adicionar tarefa\n");
    printf("2. Listar tarefas\n");
    printf("3. Remover tarefa\n");
    printf("4. Salvar e sair\n");
    printf("Escolha uma opcao: ");
}


void adicionarTarefa(Tarefa tarefas[], int *contador) {
    if (*contador >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }
    
    Tarefa novaTarefa;
    novaTarefa.id = *contador + 1;
    
    printf("Digite a descricao da tarefa: ");
    getchar();  
    fgets(novaTarefa.descricao, MAX_TEXTO, stdin);
    novaTarefa.descricao[strcspn(novaTarefa.descricao, "\n")] = 0;
    
    tarefas[*contador] = novaTarefa;
    (*contador)++;
    
    printf("Tarefa adicionada com sucesso!\n");
}


void listarTarefas(Tarefa tarefas[], int contador) {
    if (contador == 0) {
        printf("Nao ha tarefas cadastradas.\n");
        return;
    }

    printf("\nTarefas cadastradas:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", tarefas[i].id, tarefas[i].descricao);
    }
}


void removerTarefa(Tarefa tarefas[], int *contador) {
    if (*contador == 0) {
        printf("Nao ha tarefas para remover.\n");
        return;
    }

    int id;
    printf("Digite o ID da tarefa a ser removida: ");
    scanf("%d", &id);

    if (id < 1 || id > *contador) {
        printf("Tarefa invalida!\n");
        return;
    }

    for (int i = id - 1; i < *contador - 1; i++) {
        tarefas[i] = tarefas[i + 1];
    }
    
    (*contador)--;
    printf("Tarefa removida com sucesso!\n");
}


void salvarTarefas(Tarefa tarefas[], int contador) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "%d;%s\n", tarefas[i].id, tarefas[i].descricao);
    }

    fclose(arquivo);
    printf("Tarefas salvas com sucesso!\n");
}


void carregarTarefas(Tarefa tarefas[], int *contador) {
    FILE *arquivo = fopen("tarefas.txt", "r");
    if (arquivo == NULL) {
        printf("Nao ha tarefas salvas.\n");
        return;
    }

    while (fscanf(arquivo, "%d;%[^\n]\n", &tarefas[*contador].id, tarefas[*contador].descricao) != EOF) {
        (*contador)++;
    }

    fclose(arquivo);
}

int main() {
    Tarefa tarefas[MAX_TAREFAS];
    int contador = 0;
    int opcao;

    carregarTarefas(tarefas, &contador);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarTarefa(tarefas, &contador);
                break;
            case 2:
                listarTarefas(tarefas, contador);
                break;
            case 3:
                removerTarefa(tarefas, &contador);
                break;
            case 4:
                salvarTarefas(tarefas, contador);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
