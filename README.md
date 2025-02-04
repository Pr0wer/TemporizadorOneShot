# SISTEMA DE DESLIGAMENTO DE LEDS COM TEMPORIZADOR ONESHOT

# Visão geral do programa
O código traz um sistema em que, ao se pressionar um botão, todos os LEDs são ligados e desligados um por um, a cada intervalo de 3 segundos (intervalo de tempo pré-definido, mas pode ser alterado no código). O programa faz uma leve pausa durante as leituras do botão para garantir um tratamento no efeito bounce. Além disso, se utiliza o temporizador OneShot repetidamente até que todos os LEDs estejam desligalods, bem como um array para servir de sequência/ordem de desligamento dos LEDs, ao conter todos os pinos de LEDs em seu espaço de memória e um cursor para se locomover entre os valores da sequência durante as rotinas de temporização.

# Como usar?
Para usar o programa apresentado, deve se utilizar ou a plataforma [Wokwi](https://wokwi.com/) ou um microcontrolador Raspberry Pi Pico W, ao utilizar em ambos, com os devidos cuidados:
    
* 3 LEDs (Quaisquer 3 cores, mas é definido por padrão Azul, Verde e Vermelho)
* 3 Resistores (330 Ohm, um para cada LED)
* Botão (Push button)
  
Após a conexão nos respectivos pinos (disponíveis e alteráveis nas variáveis do código), basta:

* No [Wokwi](https://wokwi.com/), adicionar o código presente em "oneshot.c" na simulação e rodar
* No Raspberry Pi Pico W, compilar o código "oneshot.c" em um arquivo de extensão .uf2 e carregar na memória flash do dispositivo. A compilação pode ser feita através da extensão Raspberry Pi Pico, presente no [Visual Studio Code](https://code.visualstudio.com/), ou da forma que desejar

Com o programa rodando, teste apertar o botão e observe o início e desligamento por etapas dos LEDs
