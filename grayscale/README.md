# Workshop OpenMP -  Processar uma imagem

O objetivo é transformar uma imagem colorida em uma correspondente em escala de cinza. A seguir, temos um exemplo:

![](examples/colored.jpg) ![](examples/gray.jpg)

## Instalar dependências 
Para realizar esse exercício é preciso instalar a biblioteca `opencv` no Linux:

```bash
$ sudo apt-get install libopencv-dev
```

## Implementação

Para realizar o processamento da imagem é preciso implementar a função `process_image_parallel` no arquivo `student.cpp`:

```cpp
void process_image_parallel(struct rgb *input_image,
    unsigned char *output_image,
    size_t rows,
    size_t cols)
{
    // your code goes here
}
```
O parâmetro de entrada `input_image` corresponde aos três canais da imagem colorida: vermelho, verde e azul. A *struct* `rgb` é definida da seguinte forma:

```cpp
struct rgb
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
```
Enquanto `output_image` corresponde ao canal de saída com o valor em escalada de cinza. Os parâmetros `rows` e `cols` definem a quantidade de linhas e colunas da imagem, respectivamente.

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
$ ./runner input.jpg
```

## Como transformar a imagem para escala de cinza

Basicamente, é necessário misturar todos os três canais (vermelho, verde e azul) em um único canal. 

Intuitivamente, uma solução é somar os valores dos canais de cor e dividir por 3, porém não é a melhor solução (se estiver curioso, teste!).

Sendo assim, vamos utilizar a seguinte fórmula (recomendada pelo NTSC) para computar o valor do canal resultante:

```
I = .299f * R + .587f * G + .114f * B
```

## Dica

Se o seu algoritmo não passou no teste, no arquivo `difference.jpg` é possível ver a diferença entre a imagem de referência `reference.jpg` e imagem de entrada `input.jpg`.

## Paralelizando laços aninhados

A paralelização de um laço aninhado pode ser feita de duas maneiras. A primeira é pelo uso da diretiva de compilação ```collapse(level)```, sendo ```level``` a quantidade de níveis aninhados que se deseja paralelizar.

```cpp
#pragma omp parallel for collapse(2)
for(int i = 0; i < n; i++)
{
    for(int j = 0; j < n; j++)
    {
        // trabalho
    }
    // Não pode ter código aqui!
}
```

Outra opção é repetir a diretiva de compilação ```#pragma omp parallel for``` para cada laço:

```cpp
#pragma omp parallel for
for(int i = 0; i < n; i++)
{
    #pragma omp parallel for
    for(int j = 0; j < n; j++)
    {
        // trabalho
    }
}
```