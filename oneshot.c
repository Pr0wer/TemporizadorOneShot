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
        if (gpio_get(btn_a_pin) == 0 && ledDesligado)
        {      
            for (int i = 0; i < LED_COUNT; i++)
            {
                gpio_put(led_pins[i], 1);
            }
            ledDesligado = false;

            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(50);
    }
}

void inicializar_leds()
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_put(led_pins[i], 0);
    }
}

int64_t turn_off_callback(alarm_id_t id, void *user_data)
{   
    gpio_put(led_pins[cursorLed], 0);
    cursorLed++;

    if (cursorLed == LED_COUNT)
    {      
        ledDesligado = true;
        cursorLed = 0;
        return 0;
    }
    else
    {
        return 3000000;
    }
}

