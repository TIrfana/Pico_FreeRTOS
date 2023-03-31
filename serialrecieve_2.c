//
// Created by Thilras Irfana on 9/3/23.
//
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "aes.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

static QueueHandle_t xQueue = NULL;
//static QueueHandle_t xQueue2 = NULL;
/*function declaration*/
void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
void AES_ECB_encrypt(const struct AES_ctx* ctx, uint8_t* buf);

/* Task to serial recieve */

void recieve(void *pvParameters) {
    while (1){
        uint8_t rand_bytes[16];
        size_t bytes_read = fread(rand_bytes, 1, sizeof(rand_bytes), stdin);
        if (bytes_read == 16) {
            xQueueSend(xQueue,&rand_bytes,0U);
        }
    }
}


/* Task to perform AES encryption */
void vAESTask(void *pvParameters) {
    uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    uint8_t PT[16];

    while (1) {
        // Wait for data to be available on the input queue
        xQueueReceive(xQueue, &PT, portMAX_DELAY);
        gpio_put(16, 1);
        AES_ECB_encrypt(&ctx, PT);
        gpio_put(16, 0);
        printf(PT);

    }
}

#if 0
void send(void *pvParameters){
    uint8_t CT[16];
    while (1) {
        xQueueReceive(xQueue2, &CT, portMAX_DELAY);
        printf(CT);
    }
}
#endif

int main() {
    stdio_usb_init();
    sleep_ms(1000);
    stdio_init_all(); //Initialise I/O
    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);

    //uint8_t array[16];
    xQueue= xQueueCreate(1,16);



    // Create the AES task
    xTaskCreate(vAESTask, "AESTask", 256,NULL, 1, NULL);
    xTaskCreate(recieve, "recieve", 256,NULL, 1, NULL);
    vTaskStartScheduler();
        }

