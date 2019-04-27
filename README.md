# Workshop de Introdução ao OpenMP

Todos os exemplos foram escritos em C++. Mas é possível adaptá-los para C sem muito esforço! Use a linguagem que você tiver mais afinidade.

## O que é OpenMP

**O**pen**MP** = *Open Multi-Processing*

Basicamente é uma API que permite o desenvolvimento de programas *multi-thread* em memória compartilhada. E tem suporte para C/C++ e Fortran. OpenMP é **fácil** de usar e tem ênfase na paralelização de laços.

Contém três principais componentes:
- Diretivas de compilação
- Biblioteca de funções
- Variáveis de ambiente

## Primeiro programa: Hello World!

Crie o arquivo `main.cpp` contendo o seguinte código:

```cpp
#include <iostream>

int main()
{
    #pragma omp parallel
    {
        std::cout << "Hello World!\n";
    }
}
```

Para compilar e executar o programa:

```bash
$ g++ -fopenmp main.cpp -o output
$ ./output
```

Qual é a saída da execução? Exatamente **p** vezes o texto "Hello World!", sendo **p** o número de *threads* do processador.

> Alguns processadores possuem uma diferença entre o número de processadores e *threads* lógicas. Para saber mais sobre o processador use o comando `cat /proc/cpuinfo`.

`#pragma omp parallel` é uma **diretiva de compilação** do OpenMP que indica que o bloco de código será executado em paralelo.

## Paralelizando um laço

Como dito anteriormente, o foco do OpenMP é a paralelização de laços. Normalmente em um algoritmo, as estruturas de *loop* representam a porção de código com maior custo computacional.

Sendo assim, existe a diretiva de compilação `#pragma omp for` em OpenMP. A seguir, são apresentadas duas formas de paralelizar um laço:

```cpp
#pragma omp parallel
{
    #pragma omp for
    for(int i = 0; i < n; i++)
    {
        std::cout << i << std::endl;
    }
}
```

Forma reduzida:

```cpp
#pragma omp parallel for
for(int i = 0; i < n; i++)
{
    std::cout << i << std::endl;
}
```
> A execução do laço não é determinística, ou seja, pode não seguir a ordenação do vetor percorrido.

## Usando funções da API do OpenMP

O OpenMP fornece diversas funções que permitem definir a quantidade de *threads*, descobrir o identificador (*thread ID*) da *thread* em execução, criar e utilizar mecanismos de sincronização, e várias outras funcionalides.

Para usar as funções da API é preciso incluir o *header file* `omp.h` no programa. No exemplo a seguir, são utilizadas duas funções da API:

```cpp
#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(2);

    #pragma omp parallel for
    for(int i = 0; i < 10; i++)
    {
        printf("Thread ID: %d -- index: %d\n",
            omp_get_thread_num(), i);
    }
}
```

A função `omp_set_num_threads` define o número de *threads* que serão utilizadas durante a execução em paralelo. Já a função `omp_get_thread_num` retorna o identificador único da *thread* que está em execução no momento.

## Problema 1 - SAXPY

[Para ver a descrição do problema clique aqui](./saxpy)

## Problema 2 - Processar uma imagem

[Para ver a descrição do problema clique aqui](./grayscale)

## Sincronização com OpenMP

Um problema muito comum em algoritmos paralelos é o acesso concorrente à um mesmo recurso, o que gera uma **condição de corrida**. Um exemplo é a redução de um vetor de inteiros.

> Uma condição de corrida ocorre quando duas *threads* tentam obter um mesmo recurso, por exemplo: adicionar um valor em uma variável de soma.

Código sequencial:

```cpp
#include <iostream>

int main()
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }

    std::cout << sum << std::endl;
}
```

Usando funções ```omp_init_lock```, ```omp_set_lock```, ```omp_unset_lock``` e ```omp_destroy_lock``` da API do OpenMP:

```cpp
#include <iostream>
#include <omp.h>

int main()
{
    omp_lock_t writelock;
    omp_init_lock(&writelock);

    int sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        omp_set_lock(&writelock);
        sum += array[i];
        omp_unset_lock(&writelock);
    }

    std::cout << sum << std::endl;

    omp_destroy_lock(&writelock);
}
```

Usando a diretiva `#critical`:

```cpp
#include <iostream>

int main()
{
    int sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        #pragma omp critical
        sum += array[i];
    }
    std::cout << sum << std::endl;
} 
```

Por fim, ainda existe outra forma! Por meio de uma diretiva de compilação:

```cpp
#include <iostream>

int main()
{
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }

    std::cout << sum << std::endl;
}
```
[Para ver um comparativo entre as abordagens clique aqui](./examples)