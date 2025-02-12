#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

//Definição dos pinos
#define SERVO_PIN 22 // Pino GPIO conectado ao servomotor
#define LED_VERMELHO 13 // Pino GPIO para o LED vermelho
#define LED_VERDE 11 // Pino GPIO para o LED verde
#define LED_AZUL 12 // Pino GPIO para o LED azul

// Função para configurar o PWM para o servomotor
void configurar_pwm_servo(uint gpio_pin) {
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM); // Configura o pino GPIO como PWM
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin); // Obtém o slice do PWM

    // Configura o PWM para 50Hz (período de 20ms)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.f); // Divisor de clock para 125 (125MHz / 125 = 1MHz)
    pwm_config_set_wrap(&config, 20000); // Wrap value para 20ms 
    pwm_init(slice_num, &config, true); // Inicializa o PWM com as configurações
}

// Função para configurar o PWM para o LED RGB
void configurar_pwm_rgb(uint pino_vermelho, uint pino_verde, uint pino_azul) {
    // Configura os pinos do LED RGB como PWM
    gpio_set_function(pino_vermelho, GPIO_FUNC_PWM);
    gpio_set_function(pino_verde, GPIO_FUNC_PWM);
    gpio_set_function(pino_azul, GPIO_FUNC_PWM);

    // Configurando os slices e canais para cada pino
    uint slice_vermelho = pwm_gpio_to_slice_num(pino_vermelho);
    uint slice_verde = pwm_gpio_to_slice_num(pino_verde);
    uint slice_azul = pwm_gpio_to_slice_num(pino_azul);

    // Configura o PWM para os LEDs RGB
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.f); // Divisor de clock para 125 
    pwm_config_set_wrap(&config, 255); // Wrap value para 255 

    // Inicializa o PWM para cada cor
    pwm_init(slice_vermelho, &config, true);
    pwm_init(slice_verde, &config, true);
    pwm_init(slice_azul, &config, true);

    // Habilita o PWM para cada canal
    pwm_set_enabled(slice_vermelho, true);
    pwm_set_enabled(slice_verde, true);
    pwm_set_enabled(slice_azul, true);
}

// Função para definir o ciclo ativo do PWM em microssegundos
void definir_largura_pulso(uint gpio_pin, uint largura_pulso_us) {
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
    uint chan = pwm_gpio_to_channel(gpio_pin);

    // Converte microssegundos para o valor de nível do PWM
    pwm_set_chan_level(slice_num, chan, largura_pulso_us);
}

// Função para definir a cor do LED RGB
void definir_cor_rgb(uint vermelho, uint verde, uint azul) {
    pwm_set_gpio_level(LED_VERMELHO, vermelho);   
    pwm_set_gpio_level(LED_VERDE, verde);         
    pwm_set_gpio_level(LED_AZUL, azul);           
}

// Função para movimentação suave entre dois ângulos
void mover_suavemente(uint gpio_pin, uint largura_inicial, uint largura_final, int passo, uint atraso_ms) {
    if (largura_inicial < largura_final) {
        for (uint largura_pulso = largura_inicial; largura_pulso <= largura_final; largura_pulso += passo) {
            definir_largura_pulso(gpio_pin, largura_pulso);

            // Ciclo ativo para uma cor do LED RGB
            uint valor_cor = (largura_pulso - 500) * 255 / (2400 - 500); 
            definir_cor_rgb(valor_cor, 255 - valor_cor, 0); // Transição de vermelha para verde
            sleep_ms(atraso_ms);
        }
    } else {
        for (uint largura_pulso = largura_inicial; largura_pulso >= largura_final; largura_pulso -= passo) {
            definir_largura_pulso(gpio_pin, largura_pulso);

            // Ciclo ativo para uma cor do LED RGB
            uint valor_cor = (largura_pulso - 500) * 255 / (2400 - 500); 
            definir_cor_rgb(valor_cor, 255 - valor_cor, 0); // Transição de verde para vermelho
            sleep_ms(atraso_ms);
        }
    }
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial

    configurar_pwm_servo(SERVO_PIN); // Configura o PWM para o servomotor
    configurar_pwm_rgb(LED_VERMELHO, LED_VERDE, LED_AZUL); // Configura o PWM para o LED RGB

    // Frequência de PWM para 50Hz (período de 20ms)
    // Já configurado na função configurar_pwm_servo.

    // Ciclo ativo para 2400µs (Duty Cycle de 0,12%)
    definir_largura_pulso(SERVO_PIN, 2400); // 180° corresponde a 2400µs
    definir_cor_rgb(0, 255, 0); // LED verde
    printf("Servo em 180 graus (2400µs)\n");
    sleep_ms(5000); // Aguarda 5 segundos

    // Ciclo ativo para 1470µs (Duty Cycle de 0,0735%)
    definir_largura_pulso(SERVO_PIN, 1470); // 90° corresponde a 1470µs
    definir_cor_rgb(0, 0, 255); // LED azul
    printf("Servo em 90 graus (1470µs)\n");
    sleep_ms(5000); // Aguarda 5 segundos

    //Ciclo ativo para 500µs (Duty Cycle de 0,025%)
    definir_largura_pulso(SERVO_PIN, 500); // 0° corresponde a 500µs
    definir_cor_rgb(255, 0, 0); // LED vermelho
    printf("Servo em 0 graus (500µs)\n");
    sleep_ms(5000); // Aguarda 5 segundos

    // Movimentação periódica suave entre 0° e 180°
    while (1) {
        // Movimentação suave de 0° (500µs) para 180° (2400µs)
        mover_suavemente(SERVO_PIN, 500, 2400, 5, 10); // Incremento de 5µs, atraso de 10ms
        printf("Servo movendo de 0° para 180°\n");

        // Movimentação suave de 180° (2400µs) para 0° (500µs)
        mover_suavemente(SERVO_PIN, 2400, 500, 5, 10); // Incremento de 5µs, atraso de 10ms
        printf("Servo movendo de 180° para 0°\n");
    }

    return 0;
}