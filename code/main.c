#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PB4
#define DEVICE_PORT PORTB
#define DEVICE_DDR DDRB
#define DEVICE_MASK ((1 << PB1) | (1 << PB2) | (1 << PB3))

volatile uint8_t device_state = 0;

void init_io(void) {
    DEVICE_DDR |= DEVICE_MASK;
    DDRB &= ~(1 << BUTTON_PIN);
    PORTB |= (1 << BUTTON_PIN);
}

void debounce(void) {
    _delay_ms(50);
}

void toggle_device(void) {
    DEVICE_PORT &= ~DEVICE_MASK;
    device_state = (device_state + 1) % 3;
    switch (device_state) {
        case 0:
            DEVICE_PORT |= (1 << PB1); //NRF24
            break;
        case 1:
            DEVICE_PORT |= (1 << PB2); //SD
            break;
        case 2:
            DEVICE_PORT |= (1 << PB3); //CC1101
            break;
    }
}

int main(void) {
    init_io();
    uint8_t last_button_state = 1;

    while (1) {
        uint8_t current_button_state = PINB & (1 << BUTTON_PIN);
        if (last_button_state == 1 && current_button_state == 0) {
            debounce();
            toggle_device();
        }
        last_button_state = current_button_state;
    }

    return 0;
}
