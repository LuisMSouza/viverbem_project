#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *Pacientes;
FILE *Medicos;
FILE *Consultas;

typedef struct
{
    int ddd;
    int numero;
} Telefone;

Telefone telefoneEntity;

typedef struct
{
    char rua[20], comp[20], bairro[20], cidade[20], cep[8], uf[3], num[5], estado[20];
} EnderCard;

typedef struct
{
    int cod, num;
    char nome[50];
    EnderCard endereco;
} PacienteCad;

PacienteCad pacienteEntity;

typedef struct
{
    int cod, num;
    int maxConsultas;
    char nome[50], especialidade[50], turno[20];
} MedicoCad;

MedicoCad medicosEntity;

typedef struct
{
    int dia, mes, ano;
    char hora[8];
} Data;

Data Registro(char message[], int type)
{
    Data d;

    printf("%s (dd/mm/aaaa): ", message);
    scanf("%i/%i/%i", &d.dia, &d.mes, &d.ano);
    if (type)
    {
        printf("%s (xx:xx): ", message);
        fflush(stdin);
        gets(d.hora);
    }

    return (d);
}

Data dataEntity;

typedef struct
{
    int cod, medID, pacienteID;
    Data data;
} ConsultaCad;

ConsultaCad createConsulta;

void IniciarArquivos()
{
    if ((Pacientes = fopen("./data/pacientes.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de pacientes...\n");
        if ((Pacientes = fopen("./data/pacientes.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de pacientes.\n");
            exit(1);
        }
    }
    if ((Medicos = fopen("./data/medicos.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de médicos...\n");
        if ((Medicos = fopen("./data/medicos.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de médicos\n");
            exit(1);
        }
    }
    if ((Consultas = fopen("./data/consultas.txt", "r+b")) == NULL)
    {
        printf("Criando arquivo de consultas...\n");
        if ((Consultas = fopen("./data/consultas.txt", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo de consultas\n");
            exit(1);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    IniciarArquivos(Pacientes, Medicos, Consultas);

    int op;
    do
    {
        printf(
            "Sistema Viver Bem\n\nSeja Bem vindo!\n\nDigite o número "
            "correspondente ao que deseja abaixo: \n\n1 -- Cadastrar paciente --\n2 -- "
            "Cadastrar médico --\n3 -- Cadastrar consulta --\n4 -- Cancelar Consulta --\n5 -- Sair do sistema --\n\n-> ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            cadastraPaciente(Pacientes);
            break;

        case 2:
            cadastraMedico(Medicos);
            break;

        case 3:
            cadastraConsulta(Consultas, Medicos, Pacientes);
            break;
        case 4:
            cancelaConsulta(Consultas);
            break;
        case 5:
            system("cls");
            printf("Programa finalizado. Até breve!\n");
            break;
        case 6:
            break;

        default:
            printf("Opção inválida");
            break;
        }
    } while (op != 5);
    return 0;
}

void CadEndereco(PacienteCad *cad)
{
    PacienteCad e;
    printf("Estado: ");
    fflush(stdin);
    gets(e.endereco.estado);
    printf("Cidade: ");
    fflush(stdin);
    gets(e.endereco.cidade);
    printf("Bairro: ");
    fflush(stdin);
    gets(e.endereco.bairro);
    printf("Rua: ");
    fflush(stdin);
    gets(e.endereco.rua);
    printf("Número: ");
    fflush(stdin);
    scanf("%d", &e.endereco.num);
    printf("Complemento: ");
    fflush(stdin);
    gets(e.endereco.comp);
    printf("CEP: ");
    fflush(stdin);
    gets(e.endereco.cep);

    *cad = e;
}

void cadastraPaciente(FILE *Pacientes)
{
    system("cls");
    printf("\n Cadastrar Paciente\n\n");

    int exist, codigo;
    printf("\nDigite um código para o paciente: ");
    scanf("%i", &codigo);
    exist = VerifyId(Pacientes, codigo);
    if (exist == -1)
    {
        pacienteEntity.cod = codigo;
        printf("Digite o nome do paciente: ");
        fflush(stdin);
        gets(pacienteEntity.nome);

        Registro("Digite a data de nascimento: ", 0);
        cadastraTelefone(&pacienteEntity.num);
        CadEndereco(&pacienteEntity.endereco);

        fseek(Pacientes, 0, SEEK_END);
        fwrite(&pacienteEntity, sizeof(pacienteEntity), 1, Pacientes);
        fflush(Pacientes);

        printf("\n Paciente cadastrado com sucesso!\n");
    }
    else
    {
        printf("Já existe um paciente com esse código!\n");
    }
}

int VerifyId(FILE *Pacientes, int codigo)
{
    int posicao = -1;
    int find = 0;
    fseek(Pacientes, 0, SEEK_SET);
    fread(&pacienteEntity, sizeof(pacienteEntity), 1, Pacientes);
    while (!feof(Pacientes) && !find)
    {
        posicao++;
        if (pacienteEntity.cod == codigo)
        {
            find = 1;
        }
        fread(&pacienteEntity, sizeof(pacienteEntity), 1, Pacientes);
    }
    if (find)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastraMedico(FILE *Medicos)
{
    system("cls");
    printf("\n Cadastrar Medico\n\n");
    MedicoCad m;

    int posicao, codigo;
    printf("\nCódigo: ");
    scanf("%d", &codigo);
    posicao = encontraMedico(Medicos, codigo);
    if (posicao == -1)
    {
        m.cod = codigo;
        printf("Nome: ");
        fflush(stdin);
        gets(m.nome);
        m.maxConsultas = 0;

        printf("Especialidadde: ");
        fflush(stdin);
        gets(m.especialidade);

        cadastraTelefone(&m.num);

        fseek(Medicos, 0, SEEK_END);
        fwrite(&m, sizeof(m), 1, Medicos);
        fflush(Medicos);

        printf("\n Medico cadastrado com sucesso!");
    }
    else
    {
        printf("Já existe um medico com esse código. Inclusão não realizada!\n");
    }
}

int encontraMedico(FILE *Medicos, int codigo)
{
    int posicao = -1, find = 0;
    MedicoCad m;
    fseek(Medicos, 0, SEEK_SET);
    fread(&m, sizeof(m), 1, Medicos);
    while (!feof(Medicos) && !find)
    {
        posicao++;
        if (m.cod == codigo)
        {
            find = 1;
        }
        fread(&m, sizeof(m), 1, Medicos);
    }
    if (find)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastraTelefone(Telefone *cad)
{
    printf("DDD do telefone:    ");
    fflush(stdin);
    scanf("%d", &telefoneEntity.ddd);
    printf("Número do telefone: ");
    fflush(stdin);
    scanf("%i", &telefoneEntity.numero);

    *cad = telefoneEntity;
}

int verifyConsulting(FILE *Consultas, int codigo)
{
    int posicao = -1, find = 0;
    fseek(Consultas, 0, SEEK_SET);
    fread(&createConsulta, sizeof(createConsulta), 1, Consultas);
    while (!feof(Consultas) && !find)
    {
        posicao++;
        if (createConsulta.cod == codigo)
        {
            find = 1;
        }
        fread(&createConsulta, sizeof(createConsulta), 1, Consultas);
    }
    if (find)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastraConsulta(FILE *Consultas, FILE *Medicos, FILE *Pacientes)
{
    system("cls");
    MedicoCad m;
    printf("\n Cadastrar Consulta\n\n");
    int posicaomedico, posicaopaciente, position, codigo, codepaciente, codemedico;
    printf("\nCódigo da consulta: ");
    scanf("%d", &codigo);
    position = verifyConsulting(Consultas, codigo);
    if (position == -1)
    {
        createConsulta.cod = codigo;
        printf("Digite o codigo do medico: ");
        scanf("%i", &codemedico);
        posicaomedico = encontraMedico(Medicos, codemedico);

        if (posicaomedico != -1)
        {
            printf("Digite o codigo do paciente: ");
            scanf("%i", &codepaciente);
            posicaopaciente = VerifyId(Pacientes, codepaciente);
            if (posicaopaciente != -1)
            {
                createConsulta.medID = codemedico;
                createConsulta.pacienteID = codepaciente;
                Registro("Digite a data da consulta: ", 1);
                fwrite(&createConsulta, sizeof(createConsulta), 1, Consultas);
                fflush(Consultas);
                printf("Consulta registrada com sucesso!");
                fclose(Consultas);
            }
            else
            {
                printf("Não é possivel criar essa consulta. Codigo do paciente inválido!\n");
            }
        }
        else
        {
            printf("Não é possivel criar essa consulta. Codigo do medico inválido!\n");
        }
    }
    else
    {
        printf("Não é possivel criar essa consulta. Código de consulta existente!\n");
    }
}

void cancelaConsulta(FILE *Consultas)
{
    int codConsulta;
    printf("\nCódigo da consulta: ");
    scanf("%d", &codConsulta);
    delete('/src/data/consultas.txt');
}

void imprimeConsultaMedico(FILE *Consultas)
{
    system("cls");
    printf("\n Imprimir Consulta\n\n");
    int codMedico;
    printf("\nCódigo do Médico: ");
    scanf("%d", &codMedico);
    int posicao = verifyConsulting(Consultas, codMedico);
    if (posicao != -1)
    {
        fseek(Consultas, posicao * sizeof(createConsulta), SEEK_SET);
        fread(&createConsulta, sizeof(createConsulta), 1, Consultas);
        printf("\nCódigo da consulta: %d", createConsulta.cod);
        printf("\nCódigo do medico: %d", createConsulta.medID);
        printf("\nCódigo do paciente: %d", createConsulta.pacienteID);
        printf("\nData da consulta: %s", createConsulta.data);
    }
    else
    {
        printf("Não existe consulta com esse código!\n");
    }
}

