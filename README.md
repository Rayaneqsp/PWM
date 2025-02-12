Controle de Servo Motor e LED RGB com Raspberry Pi Pico

Descrição do Projeto

Este projeto utiliza uma Raspberry Pi Pico W para controlar um servo motor e um LED RGB simultaneamente. O servo motor realiza movimentos suaves entre 0° e 180°, enquanto o LED RGB muda de cor de acordo com a posição do servo.

O código faz uso da biblioteca pico/stdlib e das funções de PWM (Pulse Width Modulation) para controlar tanto o servo quanto o LED RGB.

Componentes Utilizados

Raspberry Pi Pico W

Servo motor

LED RGB comum (cátodo comum ou anodo comum, ajustável no código)

Resistores (se necessário para o LED RGB)

Fios de conexão

Fonte de alimentação compatível (5V para o servo e 3.3V para a Pico)

BitDogLab


Funcionamento

1. O código inicializa a comunicação serial e configura os pinos de PWM para o servo motor e o LED RGB.


2. Define três posições iniciais para o servo motor (0°, 90° e 180°), alternando entre elas com pausas de 5 segundos.


3. Após as posições fixas, inicia um movimento suave e contínuo entre 0° e 180°, alternando progressivamente.


4. O LED RGB muda de cor conforme o ângulo do servo:

Verde (0°)

Azul (90°)

Vermelho (180°)

Durante a movimentação suave, a cor transita entre verde e vermelho.




Pinos Utilizados

Configuração do PWM

Servo Motor: Frequência de 50 Hz (Período de 20 ms), com pulsos variando de 500 µs (0°) a 2400 µs (180°).

LED RGB: Frequência ajustada para permitir controle de brilho suave (PWM de 8 bits, valores entre 0 e 255).


Como Usar

1. Monte o circuito conforme a tabela de pinos.


2. Compile e carregue o código na Raspberry Pi Pico.


3. O servo começará a se mover entre 0° e 180° continuamente e o LED mudará de cor.



Bibliotecas Necessárias

pico/stdlib.h

pico/time.h

hardware/irq.h

hardware/pwm.h


Caso esteja usando o SDK do Raspberry Pi Pico, certifique-se de que ele está corretamente configurado.




