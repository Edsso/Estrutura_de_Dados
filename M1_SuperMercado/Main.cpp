#include <iostream>
#include <windows.h> // Include para adicionar o Sleep, que basicamente serve para dar um delay a certas partes do código

#include "Armazem.cpp"
#include "Menus.cpp"

#define TEMPO 3000 // 3000 = 3s
#define CARTAOTAXA 0.05  // 0.05 = 5%

using namespace std;

int main(){

    Lista <Produto> listaDeProduto, listaDoCarrinho, listaDeEstatistica; // Cria uma lista de produtos
    inicializarProdutos(listaDeProduto);// Inicializar a lista
    lerAquivo("Estoque.txt", listaDeProduto); // Inicializa o arquivo para a lista cadeada
    inicializarProdutos(listaDoCarrinho);
    inicializarProdutos(listaDeEstatistica);

    int op = 0;

    while(true){

        // Menu principal
        do{

            menuPrincipal();  

            verificadorDigitacao(op);

        }while (op <1 || op >4);   

        switch (op){
            case 1:{ // Menu funcionario
                        
                do{
                                
                    menuFuncionario();

                    verificadorDigitacao(op);

                    switch (op){
                        case 1:{ // Procurar Produto

                            system("cls");
                            cout << "Deseja ver um produto de qual forma?\n";
                                    
                            do{

                                cout << "\n\t 1- Por nome?\n";
                                cout << "\t 2- Por categoria?\n";
                                cout << "\t 3- Ou quer ver os produtos que tem desconto?\n\n";
                                cout << "A sua escolha vai ser: ";
                                cin >> op;

                            }while (op <1 || op >3);

                            if (op == 1){
                                    
                                string nome;
                                cout << "Qual produto deseja ver: ";
                                cin >> nome;

                                system("cls");
                                transformaParaMaiusculo(nome);
                                Produto* produtoNomeEncontrado = pesquisarProdutoPorNome(&listaDeProduto, nome); //Mostra os produtos na lista

                                    if (produtoNomeEncontrado){
                                        cout << "Produto " << produtoNomeEncontrado->nome << " encontrado | Valor de: " << produtoNomeEncontrado->preco << " Reais | Estoque: " << produtoNomeEncontrado->quantidade << "\n";
                                    }
                                    else{
                                        cout << "Produto nao encontrado.\n";
                                    }   

                                Sleep(TEMPO);

                            }

                            else if (op == 2){

                                system("cls");
                                string categoria;
                                cout << "Qual categoria de produto deseja ver: ";
                                cin >> categoria;
                                            
                                system("cls");

                                cout << "Categoria selecionada: ";

                                transformaParaMaiusculo(categoria);
                                pesquisarProdutoCategoria(&listaDeProduto, categoria);

                                Sleep(TEMPO);
                                        
                            }

                            else{

                                system("cls");
                                cout << "Os produtos atualmente com desconto do estoque sao: ";

                                mostrarTodosProdutosComDesconto(&listaDeProduto);   

                                string op;

                                cout << "\nDeseja sair do estoque? se sim digita qualquer tecla!\n";   
                                cin >> op;

                                if (op == "sair"){
                                    break;
                                } 

                            }  

                            break;
                        }

                        case 2:{ // Ver Todo o Estoque

                            system("cls");
                            cout << "Os itens atuais do estoque atualmente sao: \n\n";

                            mostrarTodosProdutos(&listaDeProduto);

                            string op;

                            cout << "\nDeseja sair do estoque? se sim digite qualquer tecla!\n";   
                            cin >> op;

                            if (op == "sair")
                            {
                            break;
                            } 

                            break;     
                        }

                        case 3:{ // Mudar Preço/Desconto

                            system("cls");

                            do{
                
                            cout << "Deseja mudar o preco (1) ou desconto (2)?\n";
                            cin >> op;

                            }while (op <1 || op >2);

                            if (op == 1){

                                string nome;
                                double preco_novo;
                                cout << "\nQual produto deseja alterar o preco: ";
                                cin >> nome;

                                transformaParaMaiusculo(nome);
                                Produto* produtoEncontrado = pesquisarProdutoPorNome(&listaDeProduto, nome);

                                if (produtoEncontrado){
                                    cout << "\nProduto " << produtoEncontrado->nome << " encontrado | Valor de: " << produtoEncontrado->preco << " Reais.\n";
                                }else{
                                    cout << "Produto nao encontrado.\n";
                                }

                                cout << "\nQual vai ser o valor novo do produto: ";
                                cin >> preco_novo;

                                reajustarPreco(listaDeProduto, nome, preco_novo);

                            }

                            else{

                                string nome;
                                double desconto_novo;
                                cout << "\nQual produto deseja alterar o desconto: ";
                                cin >> nome;

                                transformaParaMaiusculo(nome);
                                Produto* produtoEncontrado = pesquisarProdutoPorNome(&listaDeProduto, nome);

                                    if (produtoEncontrado){
                                        cout << "\nProduto " << produtoEncontrado->nome << " encontrado | Desconto de: " << produtoEncontrado->desconto << "%\n";
                                    }else{
                                        cout << "Produto nao encontrado.\n";
                                    }

                                cout << "\nQual vai ser o desconto novo do produto: ";
                                cin >> desconto_novo;

                                reajustarDesconto(listaDeProduto, nome, desconto_novo);

                            }

                            Sleep(TEMPO);

                            break;
                        }
                                    
                        case 4:{ // Adicionar/Remover Produto

                            system("cls");
                            
                            do{
            
                            cout << "Deseja Adicionar um Produto (1) ou Remover um Produto (2)?\n";
                            cin >> op;

                            }while (op <1 || op >2);

                            if (op == 1){

                                system("cls");
                                string nome;
                                string categoria;
                                double desconto;
                                double preco;
                                int quantidade;
                                cout << "Insira o nome do produto: ";
                                cin >> nome;
                                transformaParaMaiusculo(nome);
                                cout << "Insira o preco do produto: ";
                                cin >>  preco;
                                cout << "Insira a categoria do produto (Exemplos: Frutas, Bebidas, Graos, etc...): ";
                                cin >>  categoria;
                                transformaParaMaiusculo(categoria);
                                cout << "Insira a quantidade do produto: ";
                                cin >> quantidade;
                                cout << "Insira o desconto do produto: ";
                                cin >> desconto;

                                inserirProduto(listaDeProduto, nome, preco, categoria, quantidade, desconto);

                                cout << "\nProduto: " << nome << " adicionado com sucesso!";

                            }

                            else{

                                system("cls");
                                string nome;
                                cout << "Insira o nome do produto que deseja remover: ";
                                cin >> nome;
                                string produto = transformaParaMaiusculo(nome);
                                removerProdutoPorNome(listaDeProduto, produto);            

                            }

                            Sleep(TEMPO);

                            break;
                        }

                        case 5:{ // Reabastecer Estoque

                            string nome;
                            int reabastecer_estoque;
                            cout << "Nome do produto para reabastecer: ";
                            cin >> nome;
                            cout << "Quantidade reabastecida: ";
                            cin >> reabastecer_estoque;
                            string produto = transformaParaMaiusculo(nome);

                            system("cls");
                            reabastecerEstoque(listaDeProduto, produto, reabastecer_estoque);

                            Sleep(TEMPO);

                            break;
                        }
                        
                        case 6:{ // Ir para o menu
                            break;
                        }
                        
                    }

                }while(op !=6);

                break;
            }

            case 2:{ // Menu cliente
                
                do{

                    menuCliente();

                    verificadorDigitacao(op);

                    switch (op){  
                        case 1:{ // Procurar Produto

                            system("cls");
                            cout << "Deseja ver um produto de qual forma?\n";
                                    
                            do{
                                cout << "\n\t 1- Por nome?\n";
                                cout << "\t 2- Por categoria?\n";
                                cout << "\t 3- Ou quer ver os produtos que tem desconto?\n\n";
                                cout << "A sua escolha vai ser: ";
                                cin >> op;

                            }while (op <1 || op >3);

                            if(op == 1){
                                    
                                string nome;
                                cout << "Qual produto deseja ver: ";
                                cin >> nome;

                                system("cls");
                                transformaParaMaiusculo(nome);
                                Produto* produtoNomeEncontrado = pesquisarProdutoPorNome(&listaDeProduto, nome); //Mostra os produtos na lista

                                    if (produtoNomeEncontrado){
                                        cout << "Produto " << produtoNomeEncontrado->nome << " encontrado | Valor de: " << produtoNomeEncontrado->preco << " Reais | Estoque: " << produtoNomeEncontrado->quantidade << "\n";
                                    }
                                    else{
                                        cout << "Produto nao encontrado.\n";
                                    }            
                                    Sleep(TEMPO);       

                                }

                            else if (op == 2){

                                    system("cls");
                                    string categoria;
                                    cout << "Qual categoria de produto deseja ver: ";
                                    cin >> categoria;
                                            
                                    system("cls");

                                    cout << "Categoria selecionada: ";

                                    transformaParaMaiusculo(categoria);
                                    pesquisarProdutoCategoria(&listaDeProduto, categoria);

                                    Sleep(TEMPO);
                                        
                            }

                            else{

                                    system("cls");
                                    cout << "Os produtos atualmente com desconto do estoque sao: ";

                                    mostrarTodosProdutosComDesconto(&listaDeProduto);  

                                    string op;

                                    cout << "\nDeseja sair do estoque? se sim digita qualquer tecla!\n";   
                                    cin >> op;

                                    if (op == "sair")
                                    {
                                        break;
                                    } 
                            
                            }

                            break;
                        }

                        case 2:{ // Adicionar Produtos no Carrinho

                            system("cls");
                                    
                            do{
                    
                                cout << "Deseja Adicionar um Produto (1) ou Remover um Produto (2) do carrinho?\n";
                                cin >> op;

                            }while (op <1 || op >2);
                            
                            if (op == 1){

                                string nome;
                                system("cls");

                                    cout << "Insira o nome do produto: ";
                                    cin >> nome;
                                    transformaParaMaiusculo(nome);

                                    Produto* produtoNomeEncontrado = pesquisarProdutoPorNome(&listaDeProduto, nome); //Mostra os produtos na lista    
                                        if (produtoNomeEncontrado) {
                                            cout << "Produto " << produtoNomeEncontrado->nome << " encontrado | Valor de: " << produtoNomeEncontrado->preco << " Reais" << " | Quantidade disponivel: " << produtoNomeEncontrado->quantidade << endl;

                                            int quantidadeCompra = 0;
                                            cout << "Insira a quantidade de produtos que deseja comprar: ";
                                            cin >> quantidadeCompra;

                                        if (verificarQuantidadeNoEstoque(listaDeProduto, nome, quantidadeCompra)) {
                                            cout << "Voce adicionou " << quantidadeCompra << " " << nome << " ao seu carrinho!\n";
                                            inserirProdutoCarrinho(listaDoCarrinho, nome, quantidadeCompra);
                                            reajustarQuantidadeColocandoNoCarrinho(listaDeProduto, nome, quantidadeCompra);
                                        }

                                        break;

                                        }else{
                                            cout << "Produto nao encontrado." << endl;
                                        }

                            }

                            else{

                                system("cls");
                                string nome;
                                int quantidade;
                                cout << "Insira o nome do produto que deseja remover: ";
                                cin >> nome;
                                cout << "quantidade para remover: ";
                                cin >> quantidade;
                                string produto = transformaParaMaiusculo(nome); // DAndo erro, não esta fufando
                                
                                //verificar se o produto esta no carrinho
                                Produto* produtoNoCarrinho = pesquisarProdutoPorNome(&listaDoCarrinho, produto);
                                if (produtoNoCarrinho != nullptr){
                                    // Verificar quantidade a ser removida
                                    if (quantidade > 0 && quantidade <= produtoNoCarrinho->quantidade){
                                        produtoNoCarrinho->quantidade -= quantidade;
                                        //cout << "Diminuiu" << endl;
                                    
                                    // Verificar se chegou a 0 | Removendo o produto do carrinho
                                    if (produtoNoCarrinho->quantidade == 0){
                                        removerProdutoPorNome(listaDoCarrinho, produto);
                                    }
                                    reajustarQuantidadeRemovendoDoCarrinho(listaDeProduto, produto, quantidade);         
                                }else{
                                    cout << "Quantidade invalida. Verifique a quantidade disponivel no carrinho." << endl;
                                }
                                }else {
                                    cout << "Produto '" << produto << "' nao encontrado no carrinho." << endl;
                                }

                                Sleep(TEMPO);

                                break;
                            }

                        }

                        case 3:{ // Mostrar Carrinho

                            system("cls");

                            mostrarCarrinho(&listaDoCarrinho);
                            double valorTotal = calcularValorTotal (listaDoCarrinho, listaDeProduto);
                            cout << "\n Valor total do carrinho R$: " << valorTotal << "\n";

                            string op;

                            cout << "\nDeseja sair do carrinho? se sim digita qualquer tecla!\n";   
                            cin >> op;

                            if (op == "sair")
                            {
                            break;
                            } 

                            break;
                        }

                        case 4:{ // Pagamento

                            system("cls");

                            double valorTotal = calcularValorTotal (listaDoCarrinho, listaDeProduto);
                            cout << "Valor total do carrinho: R$ " << valorTotal << "\n";

                            cout << "\nDeseja pagar de qual forma?\n\n";

                            double valor = 0;

                            do {
                    
                            cout << "\t 1 - Pix\n";
                            cout << "\t 2 - Cartao (Tem taxa baseado no humor do proprietario)?\n";
                            cout << "\t 3 - Dinheiro\n";
                            cout << "\nA sua escolha sera?\n";
                            cin >> op;

                            }while (op <1 || op >3);

                            switch (op)
                            {
                                case 1:{ // Sistema para pagar por Pix

                                    cout << "\nO desconto do preco total do carrinho ficou por: R$" << valorTotal << endl;
                                    
                                    cout << "\nPor favor aponta o seu celular no QR code para fazer o pagamento.\n";

                                    string op;

                                    cout << "\nConfirmar pagamento (Digite qualquer coisa):\n";   
                                    cin >> op;

                                    if (op == "qualquercoisa"){}
                                    //pagamentoPixCartao(valor, valorTotal);
                                    cout << "\nPagamento concluido, obrigado pela compra!";

                                    break;
                                }

                                case 2:{ // Sistema para pagar por Cartao

                                    valorTotal += valorTotal * CARTAOTAXA;

                                    cout << "\nA taxa do preco total do carrinho ficou por: R$" << valorTotal << endl;
                                    
                                    cout << "Por favor bota o seu cartao na maquininha para fazer o pagamento (Finge e escreva a quantidade certinha kkkk)\n";                 

                                    pagamentoPixCartao(valor, valorTotal);
                                    cout << "\nPagamento concluido, obrigado pela compra!";

                                    break;
                                }

                                case 3:{ // Sistema para pagar por Dinheiro
                                    
                                    cout << "\nQuanto que vai dar?\n";

                                    pagamentoDinheiro(valor, valorTotal);
                                    cout << "\nPagamento concluido, obrigado pela compra!";

                                    break;
    
                                }
                            }


                            Sleep(TEMPO);

                            salvarDados(listaDoCarrinho, listaDeProduto, listaDeEstatistica);
                            limparCarrinho(listaDoCarrinho);

                        break;
                        }

                        case 5:{ // Ir para o menu
                            break;
                        }
                    
                    }

                }while(op != 5);

                break;
            
            }
            
            case 3:{ // Ver as estatisticas antes de finalizar o sistema
                
                system("cls");
                mostrarTodosProdutos(&listaDeEstatistica);
                cout << "\nValor total do dia R$: " << calcularValorTotal(listaDeEstatistica, listaDeProduto) << endl;
                
                string op;

                cout << "\nDeseja sair do estoque? se sim digita qualquer tecla!\n";  
                cin >> op;

                if (op == "sair"){
                    break;
                }

            break;

            }

            case 4:{ // Sair/Salvar Sistema

                salvarArquivo(listaDeProduto);
                salvarArquivoEstatistica(listaDeEstatistica, listaDeProduto);
                cout << "\nSalvando e Saindo...";
                return 0;

            }

        };
        
    }

}