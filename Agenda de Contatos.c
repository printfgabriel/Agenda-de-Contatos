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


            printf("Terminou copiar %s\n", novo->nome);
            
            if (lista->quantos == 0){ // Primeiro
                lista->inicio = novo;
                lista->fim = novo;
            }
            else {  // Ja tem item na lista
                lista->fim->proximo =novo;
                lista->fim =novo;

            }
            lista->quantos++;
            // printf("Adicionou %s \n", novo->nome);
        }
    }
    else // arquivo não existe
    {
        FILE *arq = fopen("dados.txt", "w");
        fprintf(arq, "%s", "0");
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
int inserirNoFim(ListaEncadeada *lista)
{
    printf("Quantos: %d\n", lista->quantos);
    Contato *novo = novoContato();
    Contato *auxFim = lista->fim;
    if(novo == NULL)
        return 0;

    if (lista->quantos == 0){ // Primeiro
        lista->inicio = novo;
        lista->fim = novo;
    }
    
    else {  // Ja tem item na lista
        lista->fim = auxFim->proximo = novo;
    }
    lista->quantos++;
    return 1;
}

int inserirNoInicio(ListaEncadeada *lista)
{
    Contato *novo = novoContato();

    if(novo == NULL)
        return 0;
    
    
    if (lista->quantos == 0){ // primeiro item 
        lista->inicio = novo;
        lista->fim = novo;
        printf("Tem nada\n");
    }
    else{ //ja tem outro(s) contato(s)
        Contato *aux = lista->inicio;
        novo->proximo = aux;
        lista->inicio = novo;
        printf("Tem contato, ent inicio aponta pro novo q aponta pro ex-inicio\n");
    }
    lista->quantos++;
    
    return 1;
}

// 1: se foi excluído com sucesso
// 0: se contato não existe na lista
void excluirContato(ListaEncadeada *lista, texto_t nomePesquisar){
    if (lista->quantos == 0)
    {
        printf("Ops, voce nao possui nenhum contato :(\n");
        return;
    }
    
    // texto_t nomePesquisar;
    // printf("Digite o nome do contato que deseja excluir: ");
    // scanf("%s", nomePesquisar);
    fflush(stdin);
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
                return;
            }

            if (cont == 1) // se for o primeiro item, o inicio tem que ser o proximo dele ||FUNCIONANDO||
            {
                lista->inicio = aux->proximo;
                lista->quantos--;
                return;
            }
            
            if(aux->proximo == NULL) // se for o ultimo da lista, o proximo do anterior dele é NULL  ||FUNCIONANDO||
            {
                free(aux);
                auxAnt->proximo = NULL;
                lista->fim = auxAnt;
                lista->quantos--;
                return;
            }
            else // Se ele tiver no meio da lista, o prox do anterior é o prox dele 
            {    
                auxAnt->proximo = NULL;
                auxAnt->proximo = aux->proximo;
                lista->quantos--;
                return;
            } 
        }
        auxAnt = aux;
        aux = aux->proximo;
    }
    printf("Esse contato nao existe!");
    return;
};

void excluirNoFim(ListaEncadeada *lista) {
    Contato *aux = lista->fim;
    excluirContato(lista, aux->nome);
}
void excluirNoInicio(ListaEncadeada *lista){
    Contato *aux = lista->inicio;
    excluirContato(lista, aux->nome);
}
// NULL: se contato não existe na lista
// !NULL: contato existe na lista

Contato* pesquisarContato(ListaEncadeada *Lista){
    texto_t nomePesquisar;
    printf("Digite o nome a ser pesquisado: ");
    scanf("%s", nomePesquisar);
    fflush(stdin);
    Contato *aux = Lista->inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->nome, nomePesquisar) == 0)
        {
            mostrarContato(aux);
            return aux;
        }
        
        aux = aux->proximo;
    }
    printf("Esse contato nao existe!");
    return NULL;
}
void listarContatos(ListaEncadeada *lista){
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
    printf("\n1. Adicionar no fim\n");
    printf("2. Adicionar no inicio\n");
    printf("3. Remover\n");
    printf("4. Remover do inicio\n");
    printf("5. Remover do fim\n");
    printf("6. Pesquisar\n");
    printf("7. Listar contatos\n");
    printf("8. Sair\n");
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
        printf("Considerou NULL o anterior\n");
        lista->inicio = dois;
        return lista->inicio;
    }
    anterior->proximo = dois;
    printf("%s %s %s %s\n", anterior->nome, anterior->proximo->nome, anterior->proximo->proximo->nome, anterior->proximo->proximo->proximo->nome);
    // free(aux);
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
            printf("RODA GATINHO RODA\n");
            if (strcmp(aux->nome, aux->proximo->nome) > 0) { // se o proximo for menor
                Contato *guardarAux = auxAnterior; // PROBLEMA AQUI
                printf("SAIU DA FUNCAO: %s . %s\n", aux->nome, aux->proximo->nome);
                aux = trocarContatosLugar(lista ,aux, aux->proximo, auxAnterior); // troca de lugar um com outro
                printf("VOLTOU PRA FUNCAO: %s . %s\n", aux->nome, aux->proximo->nome);
            }
            printf("Como a lista ta: %s %s %s %s\n", lista->inicio->nome, lista->inicio->proximo->nome, lista->inicio->proximo->proximo->nome, lista->inicio->proximo->proximo->proximo->nome);
            auxAnterior = aux;
            aux = aux->proximo;
        }
        tamCmpr--;
    }
}

int main() { 

    ListaEncadeada *lista = (ListaEncadeada *)  malloc(sizeof(ListaEncadeada));
    lista->quantos = 0;
    lista->inicio = lista->fim = NULL;
    carregarLista(lista);
    Contato *contatoAux = malloc(sizeof(Contato));
    texto_t nomeAux;
    int opcao;
    do{
        printf("Quantos: %d\n", lista->quantos);
        opcao = menu();
        fflush(stdin);
        switch (opcao)
        {
            case 1: contatoAux = inserirNoFim(lista);
                if(contatoAux != NULL)
                    printf("Contato adicionado ao fim da lista!");
                else 
                    printf("Nao foi possivel adicionar o contato!"); 
                break;
            case 2: inserirNoInicio(lista); break;
            case 3: printf("Digite o nome do contato que deseja exluir: ");
                    scanf("%s", nomeAux); 
                    excluirContato(lista, nomeAux);
                    break;
            case 4: excluirNoInicio(lista); break;
            case 5: excluirNoFim(lista); break;
            case 6: pesquisarContato(lista); break;
            case 7: listarContatos(lista); break;
            default: break;
        }
        system("pause");
        system("cls");
    }while(opcao != 8);
    ordernarContatos(lista);
    salvarArquivo(lista);
    return 0;
}


