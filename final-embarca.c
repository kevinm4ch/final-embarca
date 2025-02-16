#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "inc/ssd1306_i2c.h"
#include "inc/ssd1306.h"

#define BOTAO_A 5
#define BOTAO_B 6

int contador = 0;

void init_botoes() {

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A); 

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B); 

}

void botao_clicou() {

    if (!gpio_get(BOTAO_A) && contador > 0) {
        contador--; 
        sleep_ms(200); 
    }

    if (!gpio_get(BOTAO_B)) { 
        contador++; 
        sleep_ms(200); 
    }

}


void atualiza_tela() {

    uint8_t buffer[SSD1306_BUF_LEN] = {0}; 

    char contador_str[16];
    sprintf(contador_str, "Contador: %d", contador);
    WriteString(buffer, 0, 0, contador_str); 

    struct render_area area = {0, 127, 0, 3, SSD1306_BUF_LEN};
    render(buffer, &area); 

}

int main() {

    stdio_init_all();

    i2c_init(i2c1, 400 * 1000); 
    gpio_set_function(14, GPIO_FUNC_I2C); 
    gpio_set_function(15, GPIO_FUNC_I2C); 
    gpio_pull_up(14); 
    gpio_pull_up(15); 

    SSD1306_init(); 
    init_botoes(); 

    while (true) {
        botao_clicou(); 
        atualiza_tela(); 
        sleep_ms(100); 
    }

    return 0;
}