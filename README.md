# Projeto - MeuPedaço 

Um programa feito em **C** para cadastrar e encontrar locais úteis para o público 60+, como parques, hospitais e centros de cuidado. Simples e direto.

> Projeto desenvolvido para a disciplina de **Algoritmos**.

---

##  Funcionalidades

| Opção | O que faz |
|:-----:|-----------|
|  **Login / Cadastro** | Cria seu perfil com nome e idade (com boas-vindas especiais para quem tem 60+) |
|  **Cadastrar Local** | Adiciona um novo local com nome, categoria e endereço |
|  **Listar Locais** | Mostra todos os locais cadastrados, numerados |
|  **Buscar Local** | Busca por nome ou categoria, sem diferenciar maiúsculas de minúsculas |
|  **Editar Local** | Escolhe um local da lista e atualiza os dados dele |
|  **Excluir Local** | Remove um local da lista (com confirmação antes de apagar) |

As categorias disponíveis são: **Lazer**, **Cuidado** e **Saúde**.

---

##  Como rodar

Você só precisa do **GCC** instalado (no Windows, vem com o [MinGW](https://www.mingw-w64.org/)).

```bash
# Compilar
gcc main.c -o main.exe -Wall

# Executar
./main.exe
```

---

##  Como os dados são salvos

O programa usa dois arquivos de texto criados automaticamente na mesma pasta:

- **`cadastro.txt`** — guarda o nome e a idade do usuário logado.
- **`locais.txt`** — guarda os locais, um por linha, com os campos separados por `|`:

```
Parque Vaca Brava|Lazer|Av. T-10, Setor Bueno
Hospital Santa Helena|Saude|Rua 95, Setor Oeste
```

Assim os dados **não se perdem** quando o programa fecha. 

---

##  Conceitos de C usados

- `struct` para organizar os dados de cada local
- Vetores de structs para carregar os locais na memória
- Arquivos (`fopen`, `fscanf`, `fprintf`, `fclose`) para persistência
- Funções para modularizar o código (cada opção do menu é uma função)
- Validação de entrada (`scanf` com limite de tamanho + limpeza de buffer)
- Manipulação de strings (`strcpy`, `strstr`, `tolower`)

---
