//
// Created by Thilras Irfana on 9/3/23.
//
#include "pico/stdlib.h"
#include "hardware/gpio.h" // add this header file
#include "FreeRTOS.h"
#include "task.h"
#include "aes.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


/*function declaration*/
void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
void AES_ECB_encrypt(const struct AES_ctx* ctx, uint8_t* buf);


/* Task to perform AES encryption */
void vAESTask(void *pvParameters) {
    uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    uint8_t PT[16];

    while (1) {
        size_t bytes_read = fread(PT, 1, sizeof(PT), stdin);
        if (bytes_read == 16) {
            gpio_put(16, 1);
            AES_ECB_encrypt(&ctx, PT);
            gpio_put(16, 0);
            PT[17]='\0';
            printf("%s",PT);
            

        }
    }
}

int main() {
    stdio_usb_init();
    sleep_ms(1000);
    stdio_init_all(); //Initialise I/O
    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);


    // Create the AES task
    xTaskCreate(vAESTask, "AESTask", 256,NULL, 1, NULL);

    vTaskStartScheduler();
}
