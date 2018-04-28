# SAXPY

Problema bem simples que consiste em: dado dois vetores **x** e **y**, um escalar **a**, para cada posição y<sub>i</sub> = a * x<sub>i</sub> + y<sub>i</sub>.

## Implementação

Para realizar o processamento da imagem é preciso implementar a função `saxpy_parallel` no arquivo `student.cpp`:

```cpp
void saxpy_parallel(vector<int> &y,
    vector<int> x,
    int a,
    size_t n)
{
    // your code goes here
}
```

## Como compilar

Para facilitar o desenvolvimento, existe um arquivo `Makefile` contendo os passos de compilação do programa.

- Compilar:
```bash
$ make build
```

- Limpar:

```bash
$ make clean
```

- Executar:
```bash
$ ./runner
```

## *Loop Scheduling*

 - *Static*

É o padrão do OpenMP, quando um bloco paralelo é executado, as iterações são dividas entre as *threads*.
 ```cpp
#pragma omp parallel for schedule(static)
for (i = 0; i < N; i++)
 ```

 - *Dynamic*

Um *static scheduling* pode não ser eficiente quando existem iterações mais demoradas que outras, podendo gerar um desbalanceamento de carga!

Sendo assim, existe o *dynamic scheduling* em que as iterações são alocadas para as *threads* por demanda. No entanto, existe um *overhead* implícito!

 ```cpp
#pragma omp parallel for schedule(dynamic)
for (i = 0; i < N; i++)
 ```

 - *Chunk size*

É possível definir **explicitamente** a quantidade de elementos em um laço que uma **thread** irá receber através de um segundo parâmetro ```CHUNK```. Como por exemplo: ```schedule(static, CHUNK)``` e ```schedule(dynamic, CHUNK)```. 

 - *Guided*

Similar ao *dynamic scheduling*, porém o bloco de elementos (```CHUNK```) varia ao longo do tempo.

 ```cpp
#pragma omp parallel for schedule(guided)
for (i = 0; i < N; i++)
 ```
