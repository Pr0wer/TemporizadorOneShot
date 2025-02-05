#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_COUNT 3

// Pinos
const uint btn_a_pin = 5;
const uint led_blue_pin = 12;
const uint led_green_pin = 11;
const uint led_red_pin = 13;

// Array contendo pinos dos LEDs, em ordem de desligamento
const uint led_pins[] = {led_blue_pin, led_green_pin, led_red_pin};

// Armazena indíce do array led_pins do LED a ser desligado
static volatile uint8_t cursorLed = 0;

bool ledDesligado = true;

// Headers de função
void inicializar_leds();
int64_t turn_off_callback(alarm_id_t id, void *user_data);

int main()
{   
    inicializar_leds();

    gpio_init(btn_a_pin);
    gpio_set_dir(btn_a_pin, GPIO_IN);
    gpio_pull_up(btn_a_pin);

    stdio_init_all();

    while (true) 
    {    
        // Tratar botão apenas quando os LEDs estiverem desligados
        if (gpio_get(btn_a_pin) == 0 && ledDesligado)
        {   
            // Liga e atualiza estado do LED
            for (int i = 0; i < LED_COUNT; i++)
            {
                gpio_put(led_pins[i], 1);
            }
            ledDesligado = false;

            // Inicia temporizador oneshot
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(50);
    }
}

// Inicializa todos os pinos de LEDs
void inicializar_leds()
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_put(led_pins[i], 0);
    }
}

// Rotina de alarme
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{   
    // Desliga o LED atual e move cursor para o próximo
    gpio_put(led_pins[cursorLed], 0);
    cursorLed++;

    // Terminar rotina de temporizador caso não haja mais LEDs
    if (cursorLed == LED_COUNT)
    {    
        // Resetar variáveis de estado
        ledDesligado = true;
        cursorLed = 0;
        return 0;
    }
    else
    {
        return 3000000; // 3000ms para o desligamento do próximo LED
    }
}

