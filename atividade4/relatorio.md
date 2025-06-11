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

Por fim, foi executado o comando ```time ./teste``` em um segundo terminal do container para medir o tempo total de execução do programa. O comando time exibe três métricas importantes: real (tempo decorrido total), user (tempo gasto em modo usuário) e sys (tempo gasto em chamadas do sistema). Essa medição permite comparar o impacto das threads CPU-bound e I/O-bound no desempenho geral do programa.

![Resultado da execução do comando time](/Imagens/comando_time.png)

## 3. Conclusão

A atividade foi importante para entender na prática como funciona o escalonamento de threads CPU-bound e I/O-bound. Apesar de algumas dificuldades, como a falha na instalação do comando top e a necessidade de lidar com múltiplos terminais no Docker, foi possível executar o programa corretamente e observar seu comportamento. A experiência ajudou a consolidar os conceitos estudados em sala de aula de forma prática e objetiva.