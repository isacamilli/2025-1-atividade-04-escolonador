# S.O. 2025.1 - Atividade 04 - Prática de escalonamento de tarefas

## 1. Objetivo

Esta atividade teve como foco a exploração prática dos conceitos de escalonamento de tarefas em sistemas operacionais, por meio da criação de threads do tipo CPU-bound e I/O-bound em linguagem C. Utilizando um contêiner Fedora com Docker, foi possível observar, monitorar e comparar o comportamento dessas threads durante a execução, reforçando o entendimento sobre como o sistema gerencia diferentes tipos de carga de trabalho.

## 2. Passos executados

#### 2.1. Execução do arquivo

No primeiro momento da prática, realizamos a preparação do ambiente dentro do contêiner Fedora, utilizado via Docker. Foi necessário garantir que o compilador gcc estivesse instalado para permitir a compilação do código-fonte em C. Após a instalação do compilador, compilamos o arquivo threads_cpu_io.c com as bibliotecas necessárias (**-lpthread** para suporte a threads e **-lm** para operações matemáticas). Em seguida, executamos o programa gerado (./teste), iniciando o processo de criação das threads CPU-bound e I/O-bound.

![ execução do programa threads_cpu_io](/Imagens/img1.png)

#### 2.2. Observação de desempenho

A execução do programa threads_cpu_io ocorreu com sucesso, mostrando a criação e finalização das threads CPU-bound e I/O-bound. Porém, ao tentar instalar o comando top para monitoramento, ocorreu um erro 503 no servidor de repositórios do Fedora, impedindo sua instalação.

O comando **top** é uma ferramenta comum para visualizar em tempo real o uso de CPU e memória pelos processos e suas threads. A opção -H permite mostrar as threads individualmente, facilitando a análise do consumo de recursos por cada thread, o que é importante para entender o escalonamento de tarefas.

![Mensagem de erro 503 durante tentativa de instalação](/Imagens/erro_503.png)

Essa dificuldade reforça a necessidade de ter as ferramentas de monitoramento instaladas antes da execução para evitar problemas durante a análise.

![Erro compilação código](/Imagens/erro2.png)

Foi utilizado o comando **watch** em conjunto com **ps** para acompanhar, em tempo real, as threads criadas durante a execução do programa.

O ps (process status) é responsável por exibir os processos ativos no sistema. Com as opções -eLf, ele mostra todos os processos (-e), em formato detalhado (-f), incluindo todas as threads (-L) associadas a cada processo. Já o watch executa esse comando periodicamente — neste caso, a cada 1 segundo (-n 1) — permitindo visualizar dinamicamente o surgimento e término das threads durante a execução do programa.

Essa combinação de comandos foi útil para observar o comportamento do sistema e entender melhor como o escalonador do Linux gerencia múltiplas threads em tempo real.

![Saída do comando watch com ps](/Imagens/comando_watch.png)

#### 2.3. Desempenho do programa

Foi executado o comando ```time ./teste``` em um segundo terminal do container para medir o tempo total de execução do programa. O comando time exibe três métricas importantes: real (tempo decorrido total), user (tempo gasto em modo usuário) e sys (tempo gasto em chamadas do sistema). Essa medição permite comparar o impacto das threads CPU-bound e I/O-bound no desempenho geral do programa.

![Resultado da execução do comando time](/Imagens/comando_time.png)

Após instalar o comando perf no ambiente, foi utilizada essa ferramenta para monitorar o desempenho do programa desenvolvido no arquivo threads_cpu_io.c. O comando perf stat foi aplicado durante a execução do programa para coletar estatísticas detalhadas sobre o uso da CPU, como o tempo de execução, número de context switches, falhas de página e outras métricas relevantes. Essa análise permitiu avaliar de forma prática o comportamento das threads CPU-bound e I/O-bound, confirmando os impactos distintos de cada tipo de carga de trabalho no sistema.

![Performance arquivo threads_cpu_io](/Imagens/perf1.png)

Em seguida, o mesmo comando perf stat foi aplicado em uma versão atualizada do programa, adaptada conforme as indicações da atividade. 
Abaixo está o trecho principal do código atualizado, que ilustra essas mudanças:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

void* cpu_thread(void* arg) {
    long id = (long)arg;
    printf("Thread CPU-bound %ld iniciada (PID: %d)\n", id, getpid());

    double pi = 0.0;
    long iterations = 100000000; // 100 milhões

    for (long k = 0; k < iterations; k++) {
        pi += (k % 2 == 0 ? 1.0 : -1.0) / (2.0 * k + 1.0);
    }
    pi *= 4;

    printf("Thread CPU-bound %ld terminou (π ≈ %.15f)\n", id, pi);
    return NULL;
}

void* io_thread(void* arg) {
    long id = (long)arg;
    printf("Thread I/O-bound %ld iniciada (PID: %d)\n", id, getpid());
    sleep(2);  // Simula operação I/O
    printf("Thread I/O-bound %ld terminou\n", id);
    return NULL;
}
```
Essa nova versão incluía a criação de uma thread adicional de cada tipo (CPU-bound e I/O-bound) e modificava o cálculo realizado pelas threads CPU-bound para o cálculo de π usando a série de Leibniz. A aplicação do perf nesse arquivo atualizado possibilitou uma análise comparativa mais aprofundada do desempenho e do escalonamento das threads, evidenciando as diferenças de comportamento e uso de recursos do sistema para as cargas de trabalho simuladas.

![Performance arquivo threads2](/Imagens/perf2.png)

Na comparação entre as duas execuções, nota-se que a versão atualizada do programa, que inclui três threads CPU-bound e três I/O-bound, além do cálculo de π pela série de Leibniz, demandou mais recursos do sistema. Esse programa usou mais CPU (aproximadamente 1,2 segundos em modo usuário) e apresentou um número maior de trocas de contexto (515), indicando maior atividade do escalonador para lidar com as seis threads simultâneas e a carga computacional mais intensa.

Por outro lado, a versão original, com duas threads de cada tipo e um cálculo mais simples (aproximadamente o valor de e), teve um uso de CPU menor (cerca de 0,45 segundos) e menos trocas de contexto (105), refletindo uma carga de trabalho menor.

Esses resultados confirmam que o aumento no número de threads e a complexidade dos cálculos impactam diretamente o desempenho do sistema, exigindo mais do escalonador e dos recursos computacionais.

## 3. Conclusão

A atividade foi importante para entender na prática como funciona o escalonamento de threads CPU-bound e I/O-bound. Apesar de algumas dificuldades, como a falha na instalação do comando top e a necessidade de lidar com múltiplos terminais no Docker, foi possível executar o programa corretamente e observar seu comportamento, o que ajudou a consolidar os conceitos estudados em sala de aula de forma prática e objetiva.

Durante a execução, a comparação entre as duas versões do programa revelou claramente como o número de threads e a complexidade dos cálculos influenciam o desempenho do sistema. A versão com mais threads e um cálculo mais intenso — o cálculo de π pela série de Leibniz — exigiu maior uso da CPU e resultou em um número maior de trocas de contexto, mostrando uma carga maior para o escalonador e para os recursos computacionais. Já a versão original, com menos threads e cálculo mais simples, apresentou um impacto menor no desempenho. Esses resultados reforçam a importância do escalonamento eficiente para otimizar o uso dos recursos em sistemas multitarefa.