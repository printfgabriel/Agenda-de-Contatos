#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char texto_t[80];

typedef struct Contato_S
{
    texto_t nome;
    texto_t endereco;
    texto_t telefone_res;
    texto_t telefone_cel;
    texto_t data_nascimento;
    struct Contato_S *proximo;
} Contato; 

typedef struct Lista_S
{
    Contato *inicio;
    Contato *fim;
    int quantos;
} ListaEncadeada;


void carregarLista(ListaEncadeada *lista){
    int quantos = 0;
    char linha[500], *token;
    const char delimitador[5] = ";";
    texto_t teste;
    FILE *arq = fopen("dados.txt", "r");
    if (arq != NULL) // arquivo existe
    {
        
        fscanf(arq, "%d\n", &quantos);
        // Contato *auxFim = lista->fim;
        for (int i = 0; i < quantos; i++)
        {
            //alocando o novo contato
            Contato *novo = (Contato *) malloc(sizeof(Contato));
            //decifrando linha e  criando novo
            fgets(linha, 499, arq);

            token = strtok(linha, delimitador);
            sscanf(token, "%[^\n]s", teste);
            strcpy(novo->nome, teste);
            
            token = strtok(NULL, delimitador);
            sscanf(token, "%[^\n]s", teste);
            strcpy(novo->endereco, teste);

            token = strtok(NULL, delimitador);
            sscanf(token, "%[^\n]s", teste);
            strcpy(novo->telefone_res, teste);
 
            token = strtok(NULL, delimitador);
            sscanf(token, "%[^\n]s", teste);
            strcpy(novo->telefone_cel, teste);

            token = strtok(NULL, delimitador);
            sscanf(token, "%[^\n]s", teste);
            strcpy(novo->data_nascimento, teste);
            
            if (lista->quantos == 0){ // Primeiro
                lista->inicio = novo;
                lista->fim = novo;
            }
            else {  // Ja tem item na lista
                lista->fim->proximo =novo;
                lista->fim =novo;

            }
            lista->quantos++;
        }
    }
    else // arquivo não existe
    {
        FILE *arq = fopen("dados.txt", "w");
    }
        fclose(arq);
}

void salvarArquivo(ListaEncadeada *lista){
    FILE *arq = fopen("dados.txt", "w");
    fprintf(arq, "%d\n", lista->quantos);
    Contato *aux = lista->inicio;
    while (aux != NULL)
    {
        fprintf(arq, "%s;%s;%s;%s;%s;\n", aux->nome, aux->endereco, aux->telefone_res, aux->telefone_cel, aux->data_nascimento);
        aux = aux->proximo;
    }
    
    fclose(arq);
}

void mostrarContato(Contato *cont) {
    printf("Nome: %s\n", cont->nome);
    printf("Endereco: %s\n", cont->endereco);
    printf("Telefone celular: %s\n", cont->telefone_cel);
    printf("Telefone residencial: %s\n", cont->telefone_res);
    printf("Data de nascimento: %s\n", cont->data_nascimento);
}


Contato* novoContato() {
    fflush(stdin);
    Contato *novoAdd = malloc(sizeof(Contato));
    printf("Digite o nome: ");
    fgets(novoAdd->nome, 79, stdin);
    if ((strlen(novoAdd->nome) > 0) && (novoAdd->nome[strlen(novoAdd->nome) - 1] == '\n'))
        novoAdd->nome[strlen (novoAdd->nome) - 1] = '\0';
    fflush(stdin);

    printf("Digite o endereco: ");
    fflush(stdin);
    fgets(novoAdd->endereco, 79, stdin);
    if ((strlen(novoAdd->endereco) > 0) && (novoAdd->endereco[strlen(novoAdd->endereco) - 1] == '\n'))
        novoAdd->endereco[strlen (novoAdd->endereco) - 1] = '\0';

    printf("Digite o telefone residencial: ");
    fflush(stdin);
    scanf("%s", novoAdd->telefone_res);

    printf("Digite o telefone celular: ");
    fflush(stdin);
    scanf("%s", novoAdd->telefone_cel);

    printf("Digite a data de nascimento: ");
    fflush(stdin);
    scanf("%s", novoAdd->data_nascimento);
    novoAdd->proximo = NULL; //inserir no final ent o proximo é NULL
    return novoAdd;
} 
// inserir sempre no final
void inserirNoFim(ListaEncadeada *lista)
{
    printf("Quantos: %d\n", lista->quantos);
    Contato *novo = novoContato();
    Contato *auxFim = lista->fim;
    if(novo == NULL){
        printf("Nao foi possivel adicionar o contato!\n");
        return;
    }

    if (lista->quantos == 0){ // Primeiro
        lista->inicio = novo;
        lista->fim = novo;
    }
    
    else {  // Ja tem item na lista
        lista->fim = auxFim->proximo = novo;
    }
    lista->quantos++;
    printf("Contato adicionado!\n");
    return;
}


// 1: se foi excluído com sucesso
// 0: se contato não existe na lista
void excluirContato(ListaEncadeada *lista){
    if (lista->quantos == 0) {
        printf("Ops, voce nao possui nenhum contato :(\n");
        return;
    }
    
    texto_t nomePesquisar;
    printf("Digite o nome do contato que deseja excluir: ");
    fflush(stdin);
    fgets(nomePesquisar, 79, stdin);
    if ((strlen(nomePesquisar) > 0) && (nomePesquisar[strlen(nomePesquisar) - 1] == '\n'))
        nomePesquisar[strlen (nomePesquisar) - 1] = '\0';

    Contato *aux = lista->inicio;
    Contato *auxAnt = lista->inicio;
    int cont = 0;
    
    while (aux != NULL)
    {
        cont++;
        if (strcmp(aux->nome, nomePesquisar) == 0)
        {
            if (lista->quantos == 1) // se so tiver um contato, a lista passa a ser NULL  ||FUNCIONANDO||
            {
                lista->inicio = NULL;
                lista->fim = NULL;
                lista->quantos = 0;
                printf("Contato removido!\n");
                return;
            }

            if (cont == 1) // se for o primeiro item, o inicio tem que ser o proximo dele ||FUNCIONANDO||
            {
                lista->inicio = aux->proximo;
                lista->quantos--;
                printf("Contato removido!\n");
                return;
            }
            
            if(aux->proximo == NULL) // se for o ultimo da lista, o proximo do anterior dele é NULL  ||FUNCIONANDO||
            {
                free(aux);
                auxAnt->proximo = NULL;
                lista->fim = auxAnt;
                lista->quantos--;
                printf("Contato removido!\n");
                return;
            }
            else // Se ele tiver no meio da lista, o prox do anterior é o prox dele 
            {    
                auxAnt->proximo = NULL;
                auxAnt->proximo = aux->proximo;
                lista->quantos--;
                printf("Contato removido!\n");
                return;
            } 
        }
        auxAnt = aux;
        aux = aux->proximo;
    }
    printf("Esse contato nao existe!");
    return;
};

// NULL: se contato não existe na lista
// !NULL: contato existe na lista

void pesquisarContato(ListaEncadeada *lista){
    if (lista->quantos == 0){
        printf("Ops, voce nao possui nenhum contato :(\n");
        return;
    }
    texto_t nomePesquisar;
    
    printf("Digite o nome a ser pesquisado: ");
    fflush(stdin);
    fgets(nomePesquisar, 79, stdin);
    if ((strlen(nomePesquisar) > 0) && (nomePesquisar[strlen(nomePesquisar) - 1] == '\n'))
        nomePesquisar[strlen (nomePesquisar) - 1] = '\0';
    Contato *aux = lista->inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->nome, nomePesquisar) == 0)
        {
            mostrarContato(aux);
            return;
        }
        
        aux = aux->proximo;
    }
    printf("Esse contato nao existe!");
    return;
}
void listarContatos(ListaEncadeada *lista){
    if (lista->quantos == 0)
    {
        printf("Ops, voce nao possui nenhum contato :(\n");
        return;
    }
    
    Contato *aux = lista->inicio;
    while(aux != NULL){
        mostrarContato(aux);
        printf("*****\n");
        aux = aux->proximo;
    }
    return;
}

// número de itens na lista
int tamanho(ListaEncadeada *Lista){
    int cont = 0;
    Contato *aux = Lista->inicio;
    while (aux != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    return cont;
}

int menu ()
{
    int opcao;
    printf("\n--- Agenda de Contatos ---\n");
    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Pesquisar\n");
    printf("4. Alterar contato\n");
    printf("5. Listar contatos\n");
    printf("6. Sair\n");
    printf("Opcao: ");

    scanf("%d", &opcao);
    fflush(stdin);
    return opcao;
}
Contato* trocarContatosLugar(ListaEncadeada *lista ,Contato *um, Contato *dois, Contato *anterior){
    Contato *aux = dois->proximo;
    dois->proximo = um;
    um->proximo = aux;
    if (anterior == NULL){
        lista->inicio = dois;
        return lista->inicio;
    }
    anterior->proximo = dois;
    return dois;
}
void ordernarContatos(ListaEncadeada *lista){
    int tam, tamCmpr;
    tam = lista->quantos;       // TAM = 3 
    tamCmpr = tam - 1;          // TAMCMPR = 2
    for (int i = 1; i < tam; i++) { // percorre a lista
        Contato *aux = lista->inicio;
        Contato *auxAnterior = NULL;
        for(int j = 0; j < tamCmpr; j++) { // percorre a lista comparando
            if (strcasecmp(aux->nome, aux->proximo->nome) > 0) { // se o proximo for menor
                aux = trocarContatosLugar(lista ,aux, aux->proximo, auxAnterior); // troca de lugar um com outro
            }
            auxAnterior = aux;
            aux = aux->proximo;
        }
        tamCmpr--;
    }
}
void alterarContato(ListaEncadeada *lista) {
    if (lista->quantos == 0) { // Caso nao tenha contatos
        printf("Ops, voce nao possui nenhum contato :(\n");
        return;
    }
    int cont = 0;
    Contato *aux = lista->inicio;
    Contato *auxAnt = NULL;
    texto_t nomeAlterar;
    
    printf("Digite o nome do contato que deseja alterar: ");
    fgets(nomeAlterar, 79, stdin);
    if ((strlen(nomeAlterar) > 0) && (nomeAlterar[strlen(nomeAlterar) - 1] == '\n'))
        nomeAlterar[strlen (nomeAlterar) - 1] = '\0';

    while (aux != NULL)
    {
        cont++;
        if (strcmp(nomeAlterar, aux->nome) == 0) // Quando achar o contato
        {
            printf("\n*Modifique o contato*\n");
            Contato *novo = novoContato();
            if(lista->quantos == 1){ // Ser tiver apenas 1 contato
                lista->inicio = novo;
                lista->fim = novo;
                free(aux), free(auxAnt);
                return;
            }
            if (cont == 1) // se for o primeiro item, o inicio tem q apontar pro novo q tem q apontar pro proximo do aux
            {
                lista->inicio = novo;
                lista->inicio->proximo = aux->proximo;
                free(aux);
                printf("Contato alterado!\n");
                return;
            }
            
            if(aux->proximo == NULL) // se for o ultimo da lista, o ant é o novo e o fim aponta pro novo
            {
                free(aux);
                auxAnt->proximo = novo;
                lista->fim = auxAnt;
                printf("Contato alterado!\n");
                return;
            }
            else // Se ele tiver no meio da lista, o ant aponta pro novo que aponta pro aux.proximo
            {    
                auxAnt->proximo = novo;
                novo->proximo = aux->proximo;
                printf("Contato alterado!\n");
                free(aux);
                return;
            } 
            
        }
        auxAnt = aux;
        aux = aux->proximo;
    }
    printf("Esse contato nao existe, verifique a ortografia ou tente adiciona-lo!\n");
}

int main() { 

    ListaEncadeada *lista = (ListaEncadeada *)  malloc(sizeof(ListaEncadeada));
    lista->quantos = 0;
    lista->inicio = lista->fim = NULL;
    carregarLista(lista);
    int opcao;
    do{
        printf("Quantos: %d\n", lista->quantos);
        opcao = menu();
        fflush(stdin);
        switch (opcao)
        {
            case 1: inserirNoFim(lista); break;
            case 2: excluirContato(lista); break;
            case 3: pesquisarContato(lista); break;
            case 4: alterarContato(lista); break;
            case 5: listarContatos(lista); break;
            default: break;
        }
        system("pause");
        system("cls");
    }while(opcao != 6);
    ordernarContatos(lista);
    salvarArquivo(lista);
    return 0;
}