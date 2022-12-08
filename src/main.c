#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *Clientes;
FILE *Medicos;
FILE *Consultas;

typedef struct
{
    int cod, num;
    char nome[50];
} ClientCad;

typedef struct
{
    char rua[20], bairro[20], cidade[20], cep[8];
} EnderCard;

typedef struct
{
    int dia, mes, ano;
} DataNasc;

DataNasc Registro(char message[])
{
    DataNasc user;

    printf("%s (dd/mm/aaaa): ", message);
    scanf("%i/%i/%i", &user.dia, &user.mes, &user.ano);

    return (user);
}

void IniciarArquivos()
{
    if (Clientes = fopen('./data/clientes.txt', 'a+b') == NULL)
    {
        printf("Arquivo de clientes criado com sucesso!");
    }
    if (Medicos = fopen('./data/medicos.txt', 'a+b') == NULL)
    {
        printf("Arquivo de médicos criado com sucesso!");
    }
    if (Consultas = fopen('data/consultas.txt', 'a+b') == NULL)
    {
        printf("Arquivo de consultas criado com sucesso!");
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    IniciarArquivos(Clientes, Medicos, Consultas);

    
    return 0;
}