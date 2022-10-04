#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float nota1, nota2;
  char nome[30];
} Aluno;

Aluno *alunos;

int quantidade = 0, limite = 10;

FILE *report;

void incluir(){
    system("cls || clear");

    if(quantidade < limite){

        printf("Indique o nome do aluno: \n");
        scanf("%s", alunos[quantidade].nome);
        printf("Informe a primeira nota: \n");
        scanf("%f", &alunos[quantidade].nota1);
        printf("Indique a segunda nota: \n");
        scanf("%f", &alunos[quantidade].nota2);

    }

    else{

        alunos = (Aluno *) realloc(alunos, 10 * sizeof(Aluno));
        limite = limite + 10;

        incluir();

    }

    quantidade++;

}

int remover(){

    char nome[10];
    Aluno a;

    printf("Qual aluno gostaria de remover?");
    scanf("%s", nome);

    for(int i = 0;i < quantidade; i++) {

        if(strcmp(nome, alunos[i].nome) == 0){

                a = alunos[i+1];
                alunos[i] = a;
                quantidade--;
                printf("Aluno removido com sucesso! \n\n");
                return 1;
                break;

        }
    }

    printf("O aluno nao existe... \n\n");
    return 0;

}

int pesquisar(){

    char *nome = malloc(10 * sizeof(char));

    printf("Qual aluno gostaria de encontrar? \n");
    scanf("%s", nome);


    for(int i = 0; i < quantidade; i++){

        if(strcmp(nome, alunos[i].nome) == 0){

            system("cls || clear");
            printf("Aluno encontrado! \n");
            printf("Nome: %s \n", alunos[i].nome);
            printf("Nota 1: %.2f \nNota 2: %.2f \n\n", alunos[i].nota1, alunos[i].nota2);
            return 1;
            break;

        }

    }

    printf("O aluno nao existe... \n\n");
    return 0;
}

void relatorio(){
    report = fopen("report.txt", "w+");
    float media = 0;

    system("cls || clear");

    if(report == NULL){
        printf("Erro ao abrir o arquivo");
        exit(0);
    }else{
        system("cls || clear");
        fprintf(report, "---Relatorio dos alunos---\n");

        for(int i = 0; i < quantidade; i++){

            media = (alunos[i].nota1 + alunos[i].nota2) / 2;

            fprintf(report, "Aluno %d - %s \n", i+1, alunos[i].nome);
            printf("Aluno %d - %s \n", i+1, alunos[i].nome);
            fprintf(report, "Nota da primeira prova: %.2f \n", alunos[i].nota1);
            printf("Nota da primeira prova: %.2f \n", alunos[i].nota1);
            fprintf(report, "Nota da segunda prova: %.2f \n", alunos[i].nota2);
            printf("Nota da segunda prova: %.2f \n", alunos[i].nota2);
            fprintf(report, "Media do aluno: %.2f \n", media);
            printf("Media do aluno: %.2f \n", media);

            if(media >= 6){
                fprintf(report, "Situacao: APROVADO!\n\n");
                printf("Situacao: APROVADO!\n\n");
            }
            else if(media < 6 && media >= 4){
                fprintf(report, "Situacao: EM RECUPERACAO!\n\n");
                printf("Situacao: EM RECUPERACAO!\n\n");
            }
            else if(media < 4){
                fprintf(report, "Situacao: REPROVADO!\n\n");
                printf("Situacao: REPROVADO !\n\n");
            }
        }


    }

    fclose(report);
}

void menu(int *selecao){

    printf("Qual acao deseja executar? \n");
    printf("1 - Incluir aluno \n");
    printf("2 - Excluir aluno \n");
    printf("3 - Pesquisar aluno \n");
    printf("4 - Relatório de notas \n");
    printf("5 - Sair \n");

    scanf("%d", selecao);

}

int main(void) {

    alunos = (Aluno *) malloc(10 * sizeof(Aluno));
    int selecao = 0;

    while(1){
        menu(&selecao);

        if(selecao == 1){
            incluir();
        }
        else if(selecao == 2){
            remover();
        }
        else if(selecao == 3){
            pesquisar();
        }
        else if(selecao == 4){
            relatorio();
        }
        else if(selecao == 5){
            printf("Tchau!\n\n");
            return 1;
            break;
        }
        else{
            printf("ACAO INVALIDA! Tente novamente mais tarde.\n");
            break;
        }
    }

    free(alunos);
    return 0;
}