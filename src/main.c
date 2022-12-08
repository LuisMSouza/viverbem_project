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
    if (Clientes = fopen("./data/clientes.txt", "a+b") == NULL)
    {
        printf("Criando arquivo de clientes...");
    }
    if (Medicos = fopen("./data/medicos.txt", "a+b") == NULL)
    {
        printf("Criando arquivo de médicos...");
    }
    if (Consultas = fopen("./data/consultas.txt", "a+b") == NULL)
    {
        printf("Criando arquivo de consultas...");
    }
}

int main(void)
{
    setlocale(LC_ALL, "portuguese");
    IniciarArquivos(Clientes, Medicos, Consultas);

    int op;

    printf("Sistema Viver Bem\n\nSeja Bem vindo!\n\nDigite o número "
           "correspondente ao que deseja abaixo: \n\n1 - Cadastrar cliente\n2 - "
           "Cadastrar consulta\n3- Cadastrar médico\n4 - Sair do sistema\n\n->");
    scanf("%i", &op);
    while (op > 4 || op < 1)
    {
        system("cls");
        printf(
            "Sistema Viver Bem\n\nSeja Bem vindo!\n\nDigite o número "
            "correspondente ao que deseja abaixo: \n\n1 - Cadastrar cliente\n2 - "
            "Cadastrar consulta\n3- Cadastrar médico\n4 - Sair do sistema\n\n-> ");
        scanf("%i", &op);
    }
    switch (op)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        system("cls");
        printf("Programa finalizado. Até breve!\n");
        break;
    }
    return 0;
}