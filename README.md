# Projeto de Controle de Servo Motor e LED RGB com Raspberry Pi Pico W

Este projeto utiliza uma **Raspberry Pi Pico W** para controlar um **servo motor** e um **LED RGB** simultaneamente. O servo motor realiza movimentos entre 0° e 180°, enquanto o LED RGB muda de cor de acordo com a posição do servo.

O código faz uso da biblioteca pico/stdlib e das funções de PWM para controlar tanto o servo quanto o LED RGB.

### Componentes Utilizados

- **BiDogLab (RP4020)** - Placa de desenvolvimento.
- **Simulador Wokwi**
- **Servo motor**
- **LED RGB** 
- **Resistores** (se necessário para o LED RGB)

## Como Usar

1. ### : Clonando o Repositório

   - No GitHub, acesse o repositório e clique em **Code** (Código) para copiar o link de clonagem.
   - No terminal do seu VSCode, execute o comando para clonar o repositório:

  Adicione este comando:
  
   git clone https://github.com/Rayaneqsp/PWM.git

   **Abrindo o projeto no VSCode**:
   - Abra o VSCode e carregue a pasta do projeto clonada
     
2.  ### Rodando a Simulação do Wokwi

    **Configuração do Circuito no Simulador**:
   - No editor Wokwi, adicione o **Servo motor** e o **LED RGB** conecte-os aos seguintes pinos do Raspberry Pi Pico W:

| Componente  | Pino GPIO no Pico W |
|-------------|---------------------|
| Cor Azul    | GPIO 12             |
| Cor Vermelho| GPIO 13             |
| Cor Verde   | GPIO 11             |
| Servo motor | GPIO 22             |

## Observações:

- **Resistores** estão conectados com o LED RGB para limitar a corrente para a cor Verde e Azul 15Ω e para a cor vermelha 68Ω , menos na conexão com a porta COM.

3. ### Compile e carregue o código na Raspberry Pi Pico.
Caso esteja usando o SDK do Raspberry Pi Pico, certifique-se de que ele está corretamente configurado.

### Funcionamento:

- O código inicializa configurando os pinos de **PWM** para o **servo motor** e o **LED RGB**.
- Define três posições iniciais para o **servo motor** (0°, 90° e 180°), alternando entre elas com pausas de **5 segundos**.
-  Após as posições fixas, inicia um **movimento suave** e contínuo entre 0° e 180°, alternando progressivamente.
-   O **LED RGB** muda de cor conforme o ângulo do servo:
     - **Verde (0°)**
     - **Azul (90°)**
     - **Vermelho (180°)**
     - Durante a movimentação suave, a cor transita entre **verde** e **vermelho**.

## Licença

Este projeto está licenciado para estudo e conhecimento.

## Autora:

**RAYANE QUEIROZ DOS SANTOS PASSOS**

## Link do vídeo:
https://www.dropbox.com/scl/fi/e6kr1bac0vyj9tb3cyolt/pwm.mp4?rlkey=bvd81xhw3xq9xi12pof3uptde&st=xzinut4z&dl=0




