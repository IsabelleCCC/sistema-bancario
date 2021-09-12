#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/*
    Projeto - Sistema Bancario
    Isabelle Caroline de Carvalho Costa
*/

void abrirMenu();
void inserirConta();
void inserirCliente();
int selecionarClientePorDocumento();
void imprimirDadosConta();
void imprimirDadosCliente();
void imprimirTodasAsContas();
void imprimirTodosOsClientes();
void atualizarCliente();
void atualizarConta();
void realizarDeposito();
void realizarPix();
void realizarSaque();

typedef struct {
    int numeroConta;
    double saldo;
    int numeroAgencia;
    int tipoConta;
    char titularesConta[5][18]; /*Armazena até 5 cpfs/cnpjs diferentes*/
} Conta[50];
Conta conta;

typedef struct {
    char nome[64];
    char rg[12];
    char endereco[85];
    long int telefone;
    double renda;
    int tipo;
    union {
        char cpf[14];
        char cnpj[18];
    };
} Cliente[50];
Cliente cliente;

/*---------------------- INSERT --------------------*/
/*insercao de uma nova conta*/
void inserirConta(){
    int entry; /*variavel utilizada para validar entradas inseridas pelo usuario*/
    int aux, i, num;

    printf("\n******************** Nova Conta *******************\n");

    for(i=0; i < 50; i++){
        if(conta[i].numeroConta == 0){
            num = i;
            break;
        }
    }

    /*Insercao e validacao - numero da conta*/
    entry = rand() % (999999 + 1 - 100000) + 100000;
    aux = TRUE;
    while(entry != 1){
        for(i = 0; i < 50; i++){ /*Verifica se ja existe uma conta com o numero*/
            if(entry == conta[i].numeroConta){
                aux = FALSE;
            }
        }

        if(aux == TRUE){
            conta[num].numeroConta = entry;
            printf("Numero da conta: %i", conta[num].numeroConta);
            entry = 1;
        }else{
            entry = rand() % (999999 + 1 - 100000) + 100000;
        }
    }

    /*Validacao e gravacao - numero agencia*/
    printf("\nInsira o numero da agencia: ");
    entry = scanf("%i", &conta[num].numeroAgencia);

    while(entry != 1){
        fflush(stdin);
        printf("\nValor inserido invalido. Por favor, digite apenas numeros inteiros: ");
        entry = scanf("%i", &conta[num].numeroAgencia);
    }

    /*Validacao e gravacao - tipo conta*/
    printf("\nInsira o numero referente ao tipo de conta. [1 = Conta Corrente | 2 = Conta Poupanca]: ");
    entry = scanf("%i", &conta[num].tipoConta);

    entry = (conta[num].tipoConta >= 1 && conta[num].tipoConta <=2) ? 1 : 0;
    while(entry != 1){
        fflush(stdin);
        printf("\nValor inserido invalido. Por favor, digite apenas 1 ou 2: ");
        entry = scanf("%i", &conta[num].tipoConta);
    }

    /*Validacao e gravacao - titulares da conta*/
    printf("\nInsira a quantidade de titulares da conta (maximo 5): ");
    entry = scanf("%i", &aux);
    entry = (aux >= 1 && aux <= 5) ? 1 : 0;
    while(entry != 1){
        fflush(stdin);
        printf("\nValor inserido invalido. Por favor, digite um numero menor que 5: ");
        entry = scanf("%i", &aux);
    }

    for(i = 0; i < aux; i++){
        printf("\n Insira o cpf ou cnpj do titular numero %i da conta: ", i+1);
        fflush(stdin);
        scanf("%18[^\n]", conta[num].titularesConta[i]);
    }

    /*insercao saldo*/
    conta[num].saldo = 0;

    printf("Conta criada com sucesso! Resumo:\n");
    printf(" > Numero da conta: %i \n", conta[num].numeroConta);
    printf(" > Agencia: %i \n", conta[num].numeroAgencia);
    printf(" > Tipo de conta: %i \n", conta[num].tipoConta);
    printf(" > Novo saldo: R$%f \n", conta[num].saldo);

    printf("\nVoltando ao menu...\n");
    abrirMenu();
}

/*Insercao de um novo cliente*/
void inserirCliente(){
    int entry, i;

    printf("\n******************* Novo Cliente ******************\n");

    for(i=0; i < 50; i++){
        if(strlen(cliente[i].cpf) == 0 && strlen(cliente[i].cnpj) == 0){
            break;
        }
    }
    printf("\nInsira o nome do cliente: ");
    fflush(stdin);
    scanf("%64[^\n]", cliente[i].nome);

    printf("\nDigite 1 para Pessoa Fisica ou 2 para Pessoa juridica: ");
    entry = scanf("%i", &cliente[i].tipo);
    if (cliente[i].tipo < 1 && cliente[i].tipo > 2) entry = 0;

    while(entry != 1){
        printf("\nValor invalido. Digite apenas 1 ou 2: ");
        fflush(stdin);
        entry = scanf("%i", &cliente[i].tipo);
        if (cliente[i].tipo < 1 && cliente[i].tipo > 2) entry = 0;
    }

    if(cliente[i].tipo == 1){
        printf("\nInsira o rg do cliente: ");
        fflush(stdin);
        scanf(" %12[^\n]", cliente[i].rg);

        printf("\nInsira o cpf do cliente: ");
        fflush(stdin);
        scanf("%14[^\n]", cliente[i].cpf);
    }else{
        printf("\nInsira o cnpj do cliente: ");
        fflush(stdin);
        scanf(" %18[^\n]", cliente[i].cnpj);
    }

    printf("\nInsira o endereco do cliente: ");
    fflush(stdin);
    scanf("%85[^\n]", cliente[i].endereco);

    printf("\nInsira o telefone do cliente: ");
    entry = scanf("%ld", &cliente[i].telefone);
    if (cliente[i].telefone < 0 || cliente[i].telefone >= 100000000000) entry = 0;

    while(entry != 1){
        printf("\nNumero de telefone invalido. Por favor, digite apenas numeros (max. 11 caracteres): ");
        entry = scanf("%ld", &cliente[i].telefone);
        if (cliente[i].telefone < 0 || cliente[i].telefone >= 100000000000) entry = 0;
    }

    printf("\nInsira a renda mensal do cliente: ");
    entry = scanf("%lf", &cliente[i].renda);

    while(entry != 1){
        printf("\nValor invalido. Por favor, tente novamente inserindo apenas um valor numerico: ");
        entry = scanf("%lf", &cliente[i].renda);
    }

    printf("\nCliente cadastrado com sucesso! Resumo:\n");
    printf(" > Nome: %s\n", cliente[i].nome);
    if(cliente[i].tipo == 1){
        printf(" > Tipo de pessoa: fisica\n");
        printf(" > rg: %s\n", cliente[i].rg);
        printf(" > cpf: %s\n", cliente[i].cpf);
    }else{
        printf(" > Tipo de pessoa: juridica\n");
        printf(" > cnpj: %s\n", cliente[i].cnpj);
    }
    printf(" > Endereco: %s\n", cliente[i].endereco);
    printf(" > Renda: %lf\n", cliente[i].renda);
    printf(" > Telefone: %ld\n", cliente[i].telefone);
    printf("\nVoltando ao menu...\n");
    abrirMenu();
}

/*---------------------- SELECT --------------------*/

/*Selecionar cliente por documento*/
int selecionarClientePorDocumento(){
    int tipo, entry, i;
    printf("\nDigite 1 para buscar por CPF ou 2 para buscar por CNPJ: ");
    entry = scanf("%i", &tipo);

    if(tipo < 1 && tipo > 2) entry = 0;
    while(entry != 1){
        printf("\nValor invalido. Por favor, digite apenas 1 ou 2: ");
        fflush(stdin);
        entry = scanf("%i", &tipo);
    }

    if(tipo == 1){
        char doc[14];
        printf("\nInsira o cpf do cliente: ");
        fflush(stdin);
        scanf("%14[^\n]", doc);
        entry = 0;
        while(entry != 1){
            for(i = 0; i < 50; i++){
                if(strcmp(doc, cliente[i].cpf) == 0){
                    return i;
                }
            }
            if(entry != 1){
                printf("\nCPF nao encontrado. Digite um cpf valido ou digite MENU para voltar ao menu: ");
                fflush(stdin);
                scanf("%14[^\n]", doc);
                if(strcmp(doc, "MENU") == 0){
                    printf("\nVoltando ao menu...");
                    abrirMenu();
                    return -1;
                }
            }
        }
    }else{
        char doc[18];
        printf("\nInsira o cnpj do cliente: ");
        fflush(stdin);
        scanf("%18[^\n]", doc);
        entry = 0;
        while(entry != 1){
            for(i = 0; i < 50; i++){
                if(strcmp(doc, cliente[i].cpf) == 0){
                    return i;
                }
            }
            if(entry != 1){
                printf("\nCNPJ nao encontrado. Digite um CNPJ valido ou digite MENU para voltar ao menu: ");
                fflush(stdin);
                scanf("%18[^\n]", doc);
                if(strcmp(doc, "MENU") == 0){
                    printf("\nVoltando ao menu...");
                    abrirMenu();
                    return -1;
                }
            }
        }
    }
    return -1;
}
/*Imprimir dados de uma conta*/
void imprimirDadosConta(){
    int numConta, num, i, entry = 0;
    printf("\n************ Visualizar Dados da Conta ************\n");
    printf("\nDigite o numero da conta: ");
    scanf("%i", &numConta);

    while(entry != 1){
        for(i = 0; i < 50; i++){
            if(numConta == conta[i].numeroConta){
                num = i;
                entry = 1;
                break;
            }
        }
        if(entry != 1){
            printf("\nConta nao encontrada. Digite uma conta valida ou digite 0 para retornar ao menu.");
            scanf("%i", &numConta);
            if(numConta == 0){
                printf("\nVoltando ao menu...");
                abrirMenu();
                return;
            }
        }
    }

    printf(" > Numero da conta: %i\n", conta[num].numeroConta);
    printf(" > Numero da agencia: %i\n", conta[num].numeroAgencia);
    if(conta[num].tipoConta == 1) printf(" > Tipo de conta: corrente\n");
    else printf(" > Tipo de conta: poupanca\n");
    printf(" > Saldo: %lf\n", conta[num].saldo);
    for(i = 0; i < 5; i++){
        if(strlen(conta[num].titularesConta[i]) > 0){
            printf(" > Titular %i: %s\n", i, conta[num].titularesConta[i]);
        }
    }

    printf("\nVoltando ao menu...\n");
    abrirMenu();
}

/*Imprimir dados de um cliente*/
void imprimirDadosCliente(){
    int num;
    printf("\n*********** Visualizar Dados do Cliente ***********\n");

    num = selecionarClientePorDocumento();
    if (num < 0 || num > 50) return;

    printf(" > Nome: %s\n", cliente[num].nome);
    if(cliente[num].tipo == 1){
        printf(" > Tipo de pessoa: fisica\n");
        printf(" > rg: %s\n", cliente[num].rg);
        printf(" > cpf: %s\n", cliente[num].cpf);
    }else{
        printf(" > Tipo de pessoa: juridica\n");
        printf(" > cnpj: %s\n", cliente[num].cnpj);
    }
    printf(" > Endereco: %s\n", cliente[num].endereco);
    printf(" > Renda: %lf\n", cliente[num].renda);
    printf(" > Telefone: %ld\n", cliente[num].telefone);
    printf("\nVoltando ao menu...\n");
    abrirMenu();
}

/*Imprimir dados de todos os clientes de uma agencia*/
void imprimirTodosOsClientes(){
    int numAgencia, entry, num, i;
    printf("\n********** Visualizar todos os Clientes ***********\n");
    printf("\nDigite o numero da agencia: ");
    scanf("%i", &numAgencia);

    while(entry != 1){
        for(i = 0; i < 50; i++){
            if(numAgencia == conta[i].numeroAgencia){
                num = i;
                entry = 1;
                break;
            }
        }
        if(entry != 1){
            printf("\nAgencia nao encontrada. Digite uma agencia valida ou digite 0 para retornar ao menu.");
            fflush(stdin);
            scanf("%i", &numAgencia);
            if(numAgencia == 0){
                printf("\nVoltando ao menu...");
                abrirMenu();
                return;
            }
        }
    }

    entry = 0;
    for(i = num; i < 50; i++){
        if(conta[i].numeroAgencia == numAgencia){
            for(int j = 0; j < 50; j++){
                for(int k = 0; k < 5; k++){
                    if(strlen(conta[i].titularesConta[k]) > 0){
                        if(strcmp(conta[i].titularesConta[k], cliente[j].cpf) == 0){
                            entry = 1;
                            printf("\n-------------------------------------------------\n");
                            printf(" > Nome: %s\n", cliente[j].nome);
                            printf(" > Tipo de pessoa: fisica\n");
                            printf(" > rg: %s\n", cliente[j].rg);
                            printf(" > cpf: %s\n", cliente[j].cpf);
                            printf(" > Endereco: %s\n", cliente[j].endereco);
                            printf(" > Renda: %lf\n", cliente[j].renda);
                            printf(" > Telefone: %ld\n", cliente[j].telefone);

                        }else if(strcmp(conta[i].titularesConta[k], cliente[j].cnpj) == 0){
                            entry = 1;
                            printf("\n-------------------------------------------------\n");
                            printf(" > Nome: %s\n", cliente[j].nome);
                            printf(" > Tipo de pessoa: juridica\n");
                            printf(" > cnpj: %s\n", cliente[j].cnpj);
                            printf(" > Endereco: %s\n", cliente[j].endereco);
                            printf(" > Renda: %lf\n", cliente[j].renda);
                            printf(" > Telefone: %ld\n", cliente[j].telefone);
                        }
                    }
                }
            }
        }
    }
    if(entry != 1){
        printf("\nNenhum cliente encontrado na agencia.");
    }
    printf("\nVoltando ao menu...");
    abrirMenu();
    return;
}

/*Imprimir dados de todas as contas de um tipo de uma agencia*/
void imprimirTodasAsContas(){
    int numAgencia, entry, num, tipo, i;
    printf("\n*********** Visualizar todas as Contas ************\n");
    printf("\nDigite o numero da agencia: ");
    scanf("%i", &numAgencia);

    while(entry != 1){
        for(i = 0; i < 50; i++){
            if(numAgencia == conta[i].numeroAgencia){
                num = i;
                entry = 1;
                break;
            }
        }
        if(entry != 1){
            printf("\nAgencia nao encontrada. Digite uma agencia valida ou digite 0 para retornar ao menu.");
            fflush(stdin);
            scanf("%i", &numAgencia);
            if(numAgencia == 0){
                printf("\nVoltando ao menu...");
                abrirMenu();
                return;
            }
        }
    }

    printf("\nInsira o tipo de conta que deseja visualizar [1 = Conta Corrente | 2 = Conta Poupanca]: ");
    entry = scanf("%i", &tipo);

    entry = (tipo >= 1 && tipo <=2) ? 1 : 0;
    while(entry != 1){
        fflush(stdin);
        printf("\nValor inserido invalido. Por favor, digite apenas 1 ou 2: ");
        entry = scanf("%i", &tipo);
    }

    entry = 0;
    for(i = num; i < 50; i++){
        if(conta[i].numeroAgencia == numAgencia && conta[i].tipoConta == tipo){
            printf("\n-------------------------------\n");
            printf(" > Numero da conta: %i\n", conta[i].numeroConta);
            printf(" > Numero da agencia: %i\n", conta[i].numeroAgencia);
            printf(" > Saldo: %lf\n", conta[i].saldo);
            for(int j = 0; j < 5; j++){
                if(strlen(conta[i].titularesConta[j]) > 0){
                    entry = 1;
                    printf(" > Titular %i: %s\n", j, conta[i].titularesConta[j]);
                }
            }
        }
    }
    if(entry != 1){
        printf("\nNenhuma conta encontrada na agencia.");
    }
    printf("\nVoltando ao menu...");
    abrirMenu();
    return;
}

/*-------------------- UPDATE ----------------------*/
void atualizarCliente(){
    /*exceto cpf*/
    int num, option, entry;
    num = selecionarClientePorDocumento();
    if (num < 0 || num > 50){
        printf("\nCliente nao encontrado. Voltando ao menu...");
        abrirMenu();
        return;
    }

    printf("\nDigite o numero equivalente a informacao que deseja atualizar:");
    printf("\n  1 - Nome");
    printf("\n  2 - Endereco");
    printf("\n  3 - Renda");
    printf("\n  4 - Telefone\n");

    entry = scanf("%i", &option);
    entry = (option >= 1 && option <= 4) ? 1 : 0;
    while(entry != 1){
        fflush(stdin);
        printf("\nValor invalido. Por favor, digite um valor entre 1 e 4 ou digite 0 se quiser retornar ao menu.");
        entry = scanf("%i", &option);
        if(option == 0){
            printf("\nVoltando ao menu...");
            abrirMenu();
        }
    }

    switch(option) {
        case 1:
            printf("\nDigite o novo nome: ");
            fflush(stdin);
            entry = scanf("%64[^\n]", cliente[num].nome);
            while(entry != 1){
                fflush(stdin);
                printf("\nValor invalido. Por favor, insira um nome valido: ");
                entry = scanf("%64[^\n]", cliente[num].nome);
            }
        break;

        case 2:
            printf("\nDigite o novo endereco: ");
            fflush(stdin);
            entry = scanf("%85[^\n]", cliente[num].endereco);
            while(entry != 1){
                fflush(stdin);
                printf("\nValor invalido. Por favor, insira um endereco valido: ");
                entry = scanf("%85[^\n]", cliente[num].endereco);
            }
        break;

        case 3:
            printf("\nDigite a nova renda: ");
            fflush(stdin);
            entry = scanf("%lf", &cliente[num].renda);
            while(entry != 1){
                fflush(stdin);
                printf("\nValor invalido. Por favor, insira um valor numerico.");
                entry = scanf("%lf", &cliente[num].renda);
            }
        break;

        case 4:
            printf("\nDigite o novo telefone: ");
            fflush(stdin);
            entry = scanf("%ld", &cliente[num].telefone);
            if (cliente[num].telefone < 0 || cliente[num].telefone > 999999999999) entry = 0;
            while(entry != 1){
                fflush(stdin);
                printf("\nValor invalido. Por favor, insira valor numerico: ");
                entry = scanf("%ld", &cliente[num].telefone);
                if (cliente[num].telefone < 0 || cliente[num].telefone > 999999999999) entry = 0;
            }
        break;

        default:
            printf("\nOcorreu um erro. Voltando ao menu...");
            abrirMenu();
            return;
        break;
    }

    printf("\nDados atualizados com sucesso! Resumo:\n");
    printf(" > Nome: %s\n", cliente[num].nome);
    if(cliente[num].tipo == 1){
        printf(" > Tipo de pessoa: fisica\n");
        printf(" > rg: %s\n", cliente[num].rg);
        printf(" > cpf: %s\n", cliente[num].cpf);
    }else{
        printf(" > Tipo de pessoa: juridica\n");
        printf(" > cnpj: %s\n", cliente[num].cnpj);
    }
    printf(" > Endereco: %s\n", cliente[num].endereco);
    printf(" > Renda: %lf\n", cliente[num].renda);
    printf(" > Telefone: %ld\n", cliente[num].telefone);
    printf("\nVoltando ao menu...\n");
    abrirMenu();

}

void atualizarConta(){
    int numConta, num, i, aux, entry = 0;
    printf("\n************* Atualizar Dados da Conta ************\n");
    printf("\nDigite o numero da conta: ");
    scanf("%d", &numConta);

    while(entry != 1){
        for(i = 0; i < 50; i++){
            if(numConta == conta[i].numeroConta){
                num = i;
                entry = 1;
                break;
            }
        }
        if(entry != 1){
            printf("\nConta nao encontrada. Digite uma conta valida ou digite 0 para retornar ao menu.");
            fflush(stdin);
            scanf("%i", &numConta);
            if(numConta == 0){
                printf("\nVoltando ao menu...");
                abrirMenu();
                return;
            }
        }
    }

    printf("\nInsira a nova quantidade de titulares da conta (maximo 5): ");
    entry = scanf("%d", &aux);
    entry = (aux >= 1 && aux <= 5) ? 1 : 0;
    while(entry != 1){
        fflush(stdin);
        printf("\nValor inserido invalido. Por favor, digite um numero menor que 5: ");
        entry = scanf("%d", &aux);
    }

    for(i = 0; i < aux; i++){
        printf("\nInsira o cpf ou cnpj do titular numero %i da conta: ", i+1);
        fflush(stdin);
        scanf("%18[^\n]", conta[num].titularesConta[i]);
    }

    printf("\nDados atualizados com sucesso! Resumo:\n");
    printf(" > Numero da conta: %i\n", conta[num].numeroConta);
    printf(" > Numero da agencia: %i\n", conta[num].numeroAgencia);
    if(conta[num].tipoConta == 1) printf(" > Tipo de conta: corrente");
    else printf(" > Tipo de conta: poupanca");
    printf(" > Saldo: %lf\n", conta[num].saldo);
    for(i = 0; i < 5; i++){
        if(strlen(conta[num].titularesConta[i]) > 0){
            printf(" > Titular %i: %s\n", i, conta[num].titularesConta[i] + 1);
        }
    }

    printf("\nVoltando ao menu...\n");
    abrirMenu();

}

/*transacoes bancarias*/
void realizarDeposito(){
    double valor;
    int numConta, i, num, idCliente, aux = 0;

    printf("\n****************** Novo Deposito ******************\n");

    idCliente = selecionarClientePorDocumento();
    if (idCliente < 0 || idCliente > 50){
        printf("\nCliente nao encontrado. Voltando ao menu...");
        abrirMenu();
        return;
    }

    printf("\nDigite o numero da conta: ");
    scanf("%i", &numConta);

    while(aux == 0){
        for(i = 0; i < 50; i++){
            if(conta[i].numeroConta == numConta){
                num = i;
                aux = 1;
                break;
            }
        }
        if(aux == 0){
            fflush(stdin);
            printf("\nConta nao encontrada. Digite um numero de uma conta existente ou digite 0 para voltar ao menu: ");
            scanf("%i", &numConta);
            if(numConta == 0){
                printf("\nVoltando ao menu...");
                abrirMenu();
            }
        }
    }

    printf("\nInsira o valor do deposito: R$");
    scanf("%lf", &valor);

    if((conta[num].saldo = conta[num].saldo + valor)){
        printf("\n-------------------------------\n");
        printf("Transacao realizada com sucesso! Resumo:\n");
        printf("Numero da conta: %i \n", conta[num].numeroConta);
        printf("Cliente: %s \n", cliente[idCliente].nome);
        printf("Novo saldo: R$%f \n", conta[num].saldo);
        printf("\n\n Voltando ao menu...");
        abrirMenu();
        return;
    }
    printf("Nao foi possivel realizar o deposito. Voltando ao menu...");
    abrirMenu();
    return;
}

/*Saque*/
void realizarSaque(){
    double valor, saldo;
    int numConta, i, num, idCliente, aux = 0;

    printf("\n******************* Novo Saque ********************\n");
    idCliente = selecionarClientePorDocumento();
    if (idCliente < 0 || idCliente > 50){
        printf("\nCliente nao encontrado. Voltando ao menu...");
        abrirMenu();
        return;
    }

    printf("\nInsira o valor do saque: R$");
    scanf("%lf", &valor);

    printf("\nDigite o numero da conta: ");
    scanf("%i", &numConta);

    while(aux == 0){
        for(i = 0; i < 50; i++){
            if(conta[i].numeroConta == numConta){
                num = i;
                aux = 1;
                break;
            }
        }
        if(aux == 0){
            fflush(stdin);
            printf("\nConta nao encontrada. Digite um numero de uma conta existente: ");
            scanf("%i", &numConta);
        }
    }

    saldo = conta[num].saldo;
    if(saldo < valor) {
        printf("\nSaldo insuficiente. Voltando ao menu...\n");
        abrirMenu();
        return;
    }

    saldo = saldo - valor;

    if((conta[num].saldo = saldo)){
        printf("\n-------------------------------\n");
        printf("Numero da conta: %d \n", conta[num].numeroConta);
        printf("Cliente: %s \n", cliente[idCliente].nome);
        printf("Agencia: %d \n", conta[num].numeroAgencia);
        printf("Tipo de conta: %d \n", conta[num].tipoConta);
        for(i=0; i<5; i++){
            if(strlen(conta[num].titularesConta[i]) > 0){
                printf("Titular %d: %s \n", i+1, conta[num].titularesConta[i]);
            }
        }
        printf("Novo saldo: R$%f \n", conta[num].saldo);
        printf("Voltando ao menu...\n");
        abrirMenu();
        return;
    }
    printf("Nao foi possivel realizar o saque. Voltando ao menu...");
    abrirMenu();
    return;
}

/*Pix*/
void realizarPix(){
    double valor;
    int numConta, numConta2, i, num, num2, aux = 0, idCliente;

    printf("\n****************** Realizar Pix *******************\n");
    idCliente = selecionarClientePorDocumento();
    if (idCliente < 0 || idCliente > 50){
        printf("\nCliente nao encontrado. Voltando ao menu...");
        abrirMenu();
        return;
    }

    printf("\nDigite o numero da sua conta: ");
    scanf("%i", &numConta);

    while(aux == 0){
        for(i = 0; i < 50; i++){
            if(conta[i].numeroConta == numConta){
                num = i;
                aux = 1;
                break;
            }
        }
        if(aux == 0){
            fflush(stdin);
            printf("\nConta nao encontrada. Digite um numero de uma conta existente: ");
            scanf("%i", &numConta);
        }
    }

    printf("\nInsira o valor do Pix: R$");
    scanf("%lf", &valor);

    printf("\nDigite o numero da conta a receber o Pix: ");
    scanf("%i", &numConta2);

    while(aux == 0){
        for(i = 0; i < 50; i++){
            if(conta[i].numeroConta == numConta2){
                num2 = i;
                aux = 1;
                break;
            }
        }
        if(aux == 0){
            fflush(stdin);
            printf("\nConta nao encontrada. Digite um numero de uma conta existente: ");
            scanf("%i", &numConta2);
        }
    }

    if((conta[num].saldo < valor)) {
        printf("\nSaldo insuficiente. Voltando ao menu...\n");
        abrirMenu();
        return;
    }

    if((conta[num].saldo -= valor) && (conta[num2].saldo += valor)){
        printf("\nTransacao bem sucedida! Seu novo saldo: R$%lf \n", conta[num].saldo);
        printf("Voltando ao menu...\n");
        abrirMenu();
        return;
    }
    printf("\nNao foi possivel realizar o pix. Voltando ao menu...\n");
    abrirMenu();
    return;
}

/*Menu*/
void abrirMenu(){
    printf("\n********************* m e n u ******************\n");
    printf("|                                                 |\n");
    printf("| Criar:                                          |\n");
    printf("|   1 - Novo cliente                              |\n");
    printf("|   2 - Nova conta                                |\n");
    printf("|                                                 |\n");
    printf("| Visualizar:                                     |\n");
    printf("|   3 - Dados de uma conta                        |\n");
    printf("|   4 - Dados de um Cliente                       |\n");
    printf("|   5 - Todos os clientes de uma agencia          |\n");
    printf("|   6 - Todas as contas de um tipo de uma agencia |\n");
    printf("|                                                 |\n");
    printf("| Atualizar:                                      |\n");
    printf("|   7 - Dados de um cliente                       |\n");
    printf("|   8 - Dados de uma conta                        |\n");
    printf("|                                                 |\n");
    printf("| Transacoes:                                     |\n");
    printf("|   9  - Deposito                                 |\n");
    printf("|   10 - Saque                                    |\n");
    printf("|   11 - Pix                                      |\n");
    printf("|                                                 |\n");
    printf("| Outros:                                         |\n");
    printf("|   12 - Sair                                     |\n");
    printf("|                                                 |\n");
    printf("***************************************************\n");
    int choice;
    scanf("%i", &choice);

    switch(choice){
        case 1:
            inserirCliente();
            break;
        case 2:
            inserirConta();
            break;
        case 3:
            imprimirDadosConta();
            break;
        case 4:
            imprimirDadosCliente();
            break;
        case 5:
            imprimirTodosOsClientes();
            break;
        case 6:
            imprimirTodasAsContas();
            break;
        case 7:
            atualizarCliente();
            break;
        case 8:
            atualizarConta();
            break;
        case 9:
            realizarDeposito();
            break;
        case 10:
            realizarSaque();
            break;
        case 11:
            realizarPix();
            return;
            break;
        case 12:
            return;
            break;
        default:
            return;
    }
}

/*main*/
int main() {
    abrirMenu();
    return 0;
}
