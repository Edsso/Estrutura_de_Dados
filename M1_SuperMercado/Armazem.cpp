#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Produto{
    string categoria;
    string nome;
    double desconto;
    double preco;
    int quantidade;
};

template <typename T>
struct No{
    Produto produto;
    No <T> *proximo;
};

template <typename T>
struct Lista{
    No <T> *comeco;
    No <T> *fim;
};

// Transforma a frase para maiúscula
string transformaParaMaiusculo(string &frase){
    transform(frase.begin(), frase.end(), frase.begin(), ::toupper);
    return frase;
}

// Inicia a lista dos produtos
template <typename T>
void inicializarProdutos(Lista <T> &lista){
    lista.comeco = nullptr;
    lista.fim = nullptr;
}

// Insere Produtos
template <typename T> 
bool inserirProduto(Lista <T> &lista, string nome, double preco, string categoria, int quantidade, double desconto){
    No <T> *novo = new No <T>;

    novo -> produto.categoria = categoria;
    novo -> produto.nome = nome;
    novo -> produto.preco = preco;
    novo -> produto.quantidade = quantidade;
    novo -> produto.desconto = desconto;
    novo -> proximo = nullptr;

    if(lista.comeco == nullptr){
        lista.comeco = novo;
        lista.fim = novo;
    }else{
        lista.fim -> proximo = novo;
        lista.fim = novo;
    }

    return true;
}

// Remove produto do estoque pelo nome
template <typename T>
bool removerProdutoPorNome(Lista<T>& lista, const string& nomeProduto) {
    No<T>* atual = lista.comeco;
    No<T>* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->produto.nome == nomeProduto) {
            // Encontrou o produto, vamos removê-lo
            if (anterior == nullptr) {
                // O produto é o primeiro da lista
                lista.comeco = atual->proximo;
            } else {
                // O produto não é o primeiro, ajusta os ponteiros
                anterior->proximo = atual->proximo;
            }

            // Libera a memória do nó removido
            delete atual;
            cout << "Produto '" << nomeProduto << "' removido." << endl;
            return true;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    cout << "Produto '" << nomeProduto << "' não encontrado." << endl;
    return false;
}

// Leia o arquivo
void lerAquivo(const string& estoque, Lista <Produto> &lista){
    ifstream Dados(estoque);

    if (!Dados){
        cout << "Erro";
    }

    string nome;
    double preco;
    string categoria;
    int quantidade;
    double desconto;

    while (Dados >> nome >> preco >> categoria >> quantidade >> desconto) {
        inserirProduto(lista, nome, preco, categoria, quantidade, desconto);
    }
    Dados.close();
}

// Salva o Arquivo
void salvarArquivo(const Lista <Produto>& lista, const string& estoque = "Estoque.txt"){
    ofstream Dados(estoque);

    if (!Dados){
        cout << "Erro";
    }
    No <Produto>* aux = lista.comeco;

    while (aux != nullptr){
        Dados << aux->produto.nome << " " << aux->produto.preco << " " << aux->produto.categoria << " " << aux->produto.quantidade << " " << aux ->produto.desconto << endl;
            aux = aux->proximo;
    }
    Dados.close();
}

// Pesquisa o produto pelo nome só
template <typename T> 
Produto* pesquisarProdutoPorNome(Lista<T>* lista, const string& nomeProduto) {
    No <T>* aux = lista->comeco;

    while (aux != nullptr) {
        if (aux->produto.nome == nomeProduto) {
            return &(aux->produto);
        }
        aux = aux->proximo;
    }

    return nullptr; // Produto não encontrado
}

// Pesquisa o produto pela categoria 
template <typename T> 
void pesquisarProdutoCategoria(Lista<T>* lista, const string& categoria){
    No <T>* aux = lista->comeco;
    cout << categoria;
   
        cout << "\n\n";
        while (aux != nullptr) {
        if (aux->produto.categoria == categoria){
            cout << "Produto " << aux->produto.nome << " encontrado | Valor de: " << aux->produto.preco << " Reais" << " | Estoque: " << aux->produto.quantidade << endl;
        }
        aux = aux->proximo;
    }
}

// Pesquisa o produto pela categoria 
template <typename T> 
void mostrarTodosProdutosComDesconto(Lista<T>* lista){
    No <T>* aux = lista->comeco;
   
        cout << "\n\n";
        while (aux != nullptr) {
        if (aux->produto.desconto>= 0.1){
            cout << "Produto " << aux->produto.nome  << " | Possui desconto de: " << aux->produto.desconto << "%" << endl;
        }
        aux = aux->proximo;
    }
}

// Mostra todos os produtos
template <typename T> 
void mostrarTodosProdutos(Lista<T>* lista){
    No <T>* aux = lista->comeco;

    while (aux != nullptr) {
        cout << "Produto: " << aux->produto.nome << " | Valor: " << aux->produto.preco << " Reais" << " | Categoria: " << aux->produto.categoria << " | Estoque: " << aux->produto.quantidade << "| Tem Desconto de: " << aux->produto.desconto << "%" << endl;
        aux = aux->proximo;
    }
}

template <typename T> 
void mostrarCarrinho(Lista<T>* lista){
    No <T>* aux = lista->comeco;

    while (aux != nullptr) {
        cout << "Produto: " << aux->produto.nome << " | Estoque: " << aux->produto.quantidade << endl;
        aux = aux->proximo;
    }
}

// Reajusta os valores dos produtos
template <typename T> 
void reajustarPreco(Lista<T>& lista, const string& nomeProduto, double novoPreco) {
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        produto->preco = novoPreco;
        cout << "\nPreco do produto '" << nomeProduto << "' ajustado para R$ " << novoPreco << endl;
    } else {
        cout << "Produto '" << nomeProduto << "' não encontrado." << endl;
    }
}

// Reajusta os descontos dos produtos
template <typename T> 
void reajustarDesconto(Lista<T>& lista, const string& nomeProduto, double novoDesconto) {
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        produto->desconto = novoDesconto;
        cout << "\nDesconto do produto '" << nomeProduto << "' ajustado para " << novoDesconto << "%" << endl;
    } else {
        cout << "Produto '" << nomeProduto << "' não encontrado." << endl;
    }
}

// Verifica se há quantidade suficiente do produto no estoque
template <typename T> 
bool verificarQuantidadeNoEstoque(Lista<T>& lista, const string& nomeProduto, int quantidadeDesejada) {
    if (quantidadeDesejada <= 0){
        cout << "Quantidade invalida." << endl;
        return false; // Se o cliente comprar 0 produto
    }
    
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        if (produto->quantidade >= quantidadeDesejada) {
            return true; // Há quantidade suficiente no estoque
        } else {
            cout << "Quantidade insuficiente no estoque para o produto '" << nomeProduto << "'. Disponivel: " << produto->quantidade << endl;
        }
    } else {
        cout << "Produto '" << nomeProduto << "' nao encontrado no estoque." << endl;
    }
    return false; // Não há quantidade suficiente ou produto não encontrado
}

// Adiciona produto no estoque
template <typename T> 
void reabastecerEstoque(Lista<T> &lista, string nomeProduto, int QuantidadeCompranda){
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        produto->quantidade = produto->quantidade + QuantidadeCompranda;
        cout << "\nProduto '" << nomeProduto << "' reabastecido" << endl;
    } else {
        cout << "Produto '" << nomeProduto << "' nao encontrado." << endl;
    }
}



// ======================== Cliente ======================== //

// Insere produtos no carrinho
template <typename T> 
bool inserirProdutoCarrinho(Lista <T> &lista, string nome, int quantidade){
    No <T> *novo = new No <T>;

    novo -> produto.nome = nome;
    novo -> produto.quantidade = quantidade;
    novo -> proximo = nullptr;

    cout << "\n";
    
    if(lista.comeco == nullptr){
        lista.comeco = novo;
        lista.fim = novo;
    }else{
        lista.fim -> proximo = novo;
        lista.fim = novo;
    }

    return true;
}


template <typename T> 
void reajustarQuantidadeColocandoNoCarrinho(Lista<T> &lista, string nomeProduto, int QuantidadeCompranda){
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr && produto->quantidade >= QuantidadeCompranda) {
        produto->quantidade = produto->quantidade - QuantidadeCompranda;
        //cout << "\nProduto '" << nomeProduto << "' ajustado a quantidade: " << QuantidadeCompranda << endl;
    } else {
        cout << "Produto '" << nomeProduto << "' não encontrado." << endl;
    }
}

// Reacoloca a quantidade de produto que o cliente ia comprar, mas desistiu
template <typename T> 
void reajustarQuantidadeRemovendoDoCarrinho(Lista<T> &lista, string nomeProduto, int novaQuantidade){
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        produto->quantidade = produto->quantidade + novaQuantidade;
        cout << "\nProduto '" << nomeProduto << "' | quantidade removida: " << novaQuantidade << endl;
    } else {
        cout << "Produto '" << nomeProduto << "' não encontrado." << endl;
    }
}

// Verifica se há quantidade suficiente do produto no estoque
template <typename T> 
bool verificarQuantidadeNoCarrinho(Lista<T>& lista, const string& nomeProduto, int quantidadeDesejada) {
    if (quantidadeDesejada <= 0){
        cout << "Quantidade invalida." << endl;
        return false; // Se o cliente comprar 0 produto
    }
    
    Produto* produto = pesquisarProdutoPorNome(&lista, nomeProduto);
    if (produto != nullptr) {
        if (produto->quantidade >= quantidadeDesejada) {
            return true; // Há quantidade suficiente no estoque
        } else {
            cout << "Quantidade insuficiente no estoque para o produto '" << nomeProduto << "'. Disponivel: " << produto->quantidade << endl;
        }
    } else {
        cout << "Produto '" << nomeProduto << "' nao encontrado no estoque." << endl;
    }
    return false; // Não há quantidade suficiente ou produto não encontrado
}


// Calcula todas os precos dos produtos e a quantidade do carrinho
template <typename T>
double calcularValorTotal(Lista<T>& lista, Lista<T>& estoque){
    No <T>* aux = lista.comeco;
    double valorTotal = 0;

    while (aux != nullptr){
        Produto* produto = pesquisarProdutoPorNome(&estoque, aux->produto.nome);
        if (produto != nullptr){
            double valorDesconto = produto->preco *(produto->desconto/100);
            double DescontoAplicado = produto->preco - valorDesconto;
            double valorProduto = DescontoAplicado * aux->produto.quantidade;
            valorTotal += valorProduto;
        }
        aux = aux->proximo;
    }
    return valorTotal;
}



// ======================== Pagamento ======================== //


template <typename T> 
void limparCarrinho(Lista<T>& carrinho){
    No <T>* atual = carrinho.comeco;
    while (atual != nullptr){
        No <T>* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    carrinho.comeco = nullptr;
    carrinho.fim = nullptr;
}

// Salva os itens do carrinho em outra struct para ver as estatisticas
template <typename T> 
void salvarDados(Lista<T>& carrinho, Lista<T>& estoque, Lista<T>& compras) {

    No<T>* aux = carrinho.comeco; // vai salvar as compras já feita em um "armazem de compras"
    while (aux != nullptr) {
        Produto* produto = pesquisarProdutoPorNome(&estoque, aux->produto.nome);
        if (produto != nullptr) {
            Produto pagamento;
            pagamento.categoria = produto->categoria;
            pagamento.nome = produto->nome;
            pagamento.preco = produto->preco;
            pagamento.quantidade = aux->produto.quantidade;
            pagamento.desconto = produto->desconto;

            No<T>* novo = new No<T>;
            novo->produto = pagamento;
            novo->proximo = nullptr;

            if (compras.comeco == nullptr) {
                compras.comeco = novo;
                compras.fim = novo;
            } else {
                compras.fim->proximo = novo;
                compras.fim = novo;
            }
        }
        aux = aux->proximo;


    }
}

// Cria o arquivo do dia a cada vez finalizado o sistema
template <typename T> 
void salvarArquivoEstatistica(Lista<T>& lista, Lista<T>& estoque, const string& pagamento = "Estatistica.txt"){
    No <T>* aux = lista.comeco;
    double valorTotal = 0;

    while (aux != nullptr){
        Produto* produto = pesquisarProdutoPorNome(&estoque, aux->produto.nome);
        if (produto != nullptr){
            double valorDesconto = produto->preco *(produto->desconto/100);
            double DescontoAplicado = produto->preco - valorDesconto;
            double valorProduto = DescontoAplicado * aux->produto.quantidade;
            valorTotal += valorProduto;
        }
        aux = aux->proximo;
    }
    //valorTotal;
    
    ofstream Dados(pagamento);

    if (!Dados){
        cout << "Erro";
    }
    No <T>* aux2 = lista.comeco;

    while (aux2 != nullptr){
        Dados << aux2->produto.nome << " | " << aux2->produto.preco << " | " << aux2->produto.categoria << " | " << aux2->produto.quantidade << " | Desconto: " << aux2->produto.desconto << endl;
            aux2 = aux2->proximo;
    }
    
    Dados << "Valor Total da Compra: " << valorTotal << endl;
    Dados.close();
}

// Verificador caso o dinheiro esteja de acordo
bool pagamentoPixCartao (double valor, double valorTotal)
{

    do {
        cin >> valor;
        if (valor == valorTotal){
            cout << "\nPagamento aceito!\n";
        } else {
            cout << "Valor incorreto, por favor digite novamente o valor: ";
        }
    } while (valor != valorTotal);

    return true;
}

// Verificador caso o dinheiro esteja de acordo
bool pagamentoDinheiro(double valor, double valorTotal)
{

    do {
        cin >> valor;
        if (valor < valorTotal){
            cout << "\nValor insuficiente, por favor digite novamente o valor: ";
        }
    } while (valor < valorTotal);

    double troco = valor - valorTotal;
    cout << "E seu troco sera de: " << troco;

    return true;
}

