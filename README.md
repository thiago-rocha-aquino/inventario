# Inventory Management System in C

Sistema de gerenciamento de estoque desenvolvido em **C puro**, demonstrando domínio de programação de sistemas, estruturas de dados e manipulação de arquivos.

## Tecnologias Utilizadas

- **C** - Linguagem de programação
- **GCC** - Compilador GNU C
- **Make** - Build automation
- **File I/O** - Persistência de dados binários
- **Structs** - Estruturas de dados personalizadas
- **Pointers** - Manipulação de memória

## Funcionalidades

### Gerenciamento de Produtos
-  Adicionar produtos ao estoque
-  Listar todos os produtos
-  Listar apenas produtos ativos
-  Buscar por nome (substring)
-  Buscar por categoria
-  Atualizar informações do produto
-  Deletar produtos
-  Ativar/desativar produtos

### Controle de Estoque
-  Atualizar quantidade (adicionar/remover)
-  Verificar produtos com estoque baixo
-  Validação de estoque suficiente
-  Cálculo de valor total do estoque

### Persistência de Dados
-  Salvar inventário em arquivo binário
-  Carregar inventário do arquivo
-  Auto-incremento de IDs
-  Recuperação de dados entre sessões

### Interface e Validações
-  Menu interativo de linha de comando
-  Validação de entrada do usuário
-  Tratamento de erros
-  Confirmação para operações destrutivas
-  Estatísticas do inventário

## Estrutura do Projeto

```
inventory-system-c/
├── src/
│   ├── main.c          # Programa principal e menu interativo
│   ├── product.h       # Header da estrutura Product
│   ├── product.c       # Implementação de Product
│   ├── inventory.h     # Header do sistema de inventário
│   └── inventory.c     # Implementação do inventário
├── build/              # Arquivos compilados (.o)
├── data/               # Arquivos de dados (.dat)
├── Makefile            # Build configuration
└── README.md
```

### Arquitetura

O projeto segue uma **arquitetura modular** em C:

- **product.h/c** - Estrutura de dados do produto e funções básicas
- **inventory.h/c** - Lógica de negócio e operações CRUD
- **main.c** - Interface de usuário e controle de fluxo

## Como Compilar e Executar

### Pré-requisitos
- GCC (GNU Compiler Collection)
- Make
- Sistema Unix-like (Linux/Mac) ou WSL no Windows

### Compilação

```bash
cd inventory-system-c

# Compilar o projeto
make

# Ou rebuild completo
make rebuild
```

### Execução

```bash
# Executar o programa
./inventory

# Ou compilar e executar
make run
```

### Limpeza

```bash
# Limpar arquivos compilados
make clean

# Limpar tudo incluindo dados
make clean-all
```

## Uso do Sistema

### Menu Principal

```
========================================
  INVENTORY MANAGEMENT SYSTEM
========================================
 1. Add Product
 2. List All Products
 3. List Active Products
 4. Search Product by Name
 5. Search by Category
 6. Update Product
 7. Update Stock
 8. Delete Product
 9. Check Low Stock
10. Show Statistics
11. Save Inventory
12. Load Inventory
 0. Exit
========================================
```

### Exemplo de Uso

1. **Adicionar Produto**:
```
Name: Notebook Dell
Category: Electronics
Price: $3500.00
Quantity: 10
```

2. **Atualizar Estoque**:
```
Product ID: 1
Quantity change: -3  (vende 3 unidades)
```

3. **Verificar Estoque Baixo**:
```
Enter threshold: 5
(mostra produtos com quantidade <= 5)
```

## Estrutura de Dados

### Product

```c
typedef struct {
    int id;                      // ID único do produto
    char name[100];              // Nome do produto
    char category[50];           // Categoria
    float price;                 // Preço unitário
    int quantity;                // Quantidade em estoque
    int active;                  // Status (1=ativo, 0=inativo)
} Product;
```

### Inventory

```c
typedef struct {
    Product products[1000];      // Array de produtos
    int count;                   // Quantidade de produtos
    int next_id;                 // Próximo ID disponível
} Inventory;
```

## Persistência de Dados

### Formato do Arquivo

O sistema salva dados em formato **binário** (`data/inventory.dat`):

- **Metadata**: count, next_id
- **Products**: Array de estruturas Product

### Vantagens do Formato Binário

-  Leitura/escrita rápida
-  Tamanho compacto
-  Mantém tipos de dados originais
-  Eficiente para grandes volumes

## Boas Práticas Implementadas

### C Programming
-  **Modularização** - Separação em headers e implementation files
-  **Encapsulamento** - Funções bem definidas
-  **Memory Management** - Malloc/free correto
-  **Error Handling** - Validações e retornos de erro
-  **Const Correctness** - Uso de const para parâmetros read-only
-  **Buffer Safety** - strncpy para evitar buffer overflow
-  **Input Validation** - Verificação de entrada do usuário

### Organização
-  **Makefile** - Build automation profissional
-  **Headers Guards** - Prevenção de inclusão múltipla
-  **Naming Conventions** - snake_case para funções e variáveis
-  **Documentation** - Comentários em headers
-  **Separation of Concerns** - UI separada da lógica

## Demonstração de Conhecimentos em C

Este projeto demonstra:

-  **C Programming** - Sintaxe, compilação, linking
-  **Structs** - Definição e manipulação
-  **Arrays** - Manipulação e iteração
-  **Pointers** - Alocação dinâmica e passagem por referência
-  **File I/O** - fread/fwrite binário
-  **String Manipulation** - strcmp, strncpy, strstr
-  **Input Validation** - scanf, fgets, validações
-  **Modular Design** - Headers e implementation files
-  **Build Systems** - Makefile com targets
-  **Debugging** - Tratamento de erros e edge cases

## Diferencial

Este projeto **complementa o portfólio** demonstrando:

1. **C Puro** - Linguagem de baixo nível
2. **Memory Management** - Manual malloc/free
3. **System Programming** - File I/O, estruturas de dados
4. **No Libraries** - Implementação from scratch
5. **Performance** - Código eficiente e otimizado
6. **Portability** - Funciona em Linux, Mac, Windows (WSL)




## Compilação Detalhada

### Flags Utilizadas

```makefile
-Wall          # Todos os warnings
-Wextra        # Warnings extras
-std=c11       # Padrão C11
-g             # Símbolos de debug
```

### Processo de Build

1. **Preprocessor** - Expande #includes e #defines
2. **Compiler** - Gera arquivos objeto (.o)
3. **Linker** - Liga objetos em executável

## Autor

Desenvolvido como projeto de portfólio demonstrando expertise em C  e estruturas de dados.

