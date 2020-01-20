# Simulador Memoria Cache

Projeto de implementação para a disciplina Arquitetura e organização de computadores - **UEM**.

# Descrição

A implementação consiste em realizar uma simulação de uma memória cache. O programa deve conter dois espaços de endereçamento, um para simular a memória principal e outro para simular a memória cache, e solicitar ao usuário acessos aos dados contidos na memória. O espaço da memória principal deve ter mais de mil posições, e o espaço da memória cache pode ter qualquer tamanho. Para isso deve ser utilizado os algoritmos de substituição, política de escrita e mapeamento. Para cada solicitação do usuário deve-se mostrar se o acesso resultou em HIT ou MISS, indicando o total destes dados na tela. 

# Mapeamento

O programa deve usar a função de mapeamento associativo (um bloco da memória principal pode ser mapeado em qualquer linha da memória cache) para armazenar o dado na memória cache.

# Algoritmos de substituição

Deve ser utilizado os algoritmos de substituição FIFO e LRU, permitindo alterar entre um algoritmo de substituição, reiniciando assim a simulação com o outro algoritmo. 

# Política de escrita

O programa deve ainda utilizar a política de escrita write-back, ou seja, ao gerar um acesso de leitura e modificação à um dado, este deve ser modificado apenas na memória cache, e quando a linha da cache onde este dado está armazenado for selecionada pelo algoritmo de substituição para ser descartado, somente neste momento deve ser atualizado o valor da memória principal. 

# Informações sobre a implementação

Tamanho do bloco (2)
Numero de linhas da cache (2)
Mapeamento (Associativo)
Política de substituição (FIFO e LRU)

<br> <br>

© Filipe Moreno
