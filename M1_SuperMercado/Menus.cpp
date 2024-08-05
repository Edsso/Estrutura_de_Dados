#include <iostream>
#include <limits> // Include que foi só usado na função verificadorDigitacao

using namespace std;

void menuPrincipal ()
{

    system("cls");
    cout << "Bem vindo ai menu, oq deseja fazer?\n";

    cout << "\n\t 1- Menu Funcionario\n"; 
    cout << "\t 2- Menu Cliente\n";
    cout << "\t 3- Ver Estatistica\n";
    cout << "\t 4- Sair/Salvar Sistema\n"; 
    cout << "\nO que vai querer fazer?\n";

}   

void menuFuncionario()
{

    system("cls");
    cout << "Menu Funcionario:\n";

    cout << "\n\t 1- Pesquisar Produto\n"; 
    cout << "\t 2- Ver Todo o Estoque\n";
    cout << "\t 3- Reajuste de Preco de um Produto\n"; 
    cout << "\t 4- Adicionar/Remover Produtos\n"; 
    cout << "\t 5- Reabastecer Estoque\n";
    cout << "\t 6- Retorno Menu\n";
    cout << "\nO que vai querer fazer?\n";

}

void menuCliente()
{

    system("cls");
    cout << "Menu Cliente:\n"; 

    cout << "\n\t 1- Procurar um Produto\n";
    cout << "\t 2- Adicionar/Remover um Produto do Carrinho\n";
    cout << "\t 3- Mostrar Carrinho\n";
    cout << "\t 4- Pagar\n";
    cout << "\t 5- Retorno Menu\n"; 
    cout << "\nO que vai querer fazer?\n";

}

bool verificadorDigitacao(int &op) {
    while (!(cin >> op)) {
        cout << "Entrada invalida, digite novamente: ";
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return true;

}