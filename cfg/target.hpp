#ifndef __TARGET_HPP__
#define __TARGET_HPP__

#include "hal/adc.hpp"
#include "hal/clock.hpp"
#include "hal/gpio.hpp"
#include "proxy/button.hpp"
#include "proxy/motor.hpp"

constexpr hal::Clock::Config clock_config = {
    .clock_scale = &rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ],
    .reload = 84000,
    .clocksource = STK_CSR_CLKSOURCE_AHB,
};

constexpr hal::Gpio::Config button_config = {
    .port = GPIOB,
    .pin = GPIO10,
    .mode = GPIO_MODE_INPUT,
    .pull_resistor = GPIO_PUPD_NONE,
    .rcc_clock = RCC_GPIOB,
};

proxy::Button::pull_resistor_t button_pull_resistor = proxy::Button::PULL_UP;

constexpr hal::Gpio::Config led_config = {
    .port = GPIOB,
    .pin = GPIO15,
    .mode = GPIO_MODE_OUTPUT,
    .pull_resistor = GPIO_PUPD_NONE,
    .rcc_clock = RCC_GPIOB,
    .otype = GPIO_OTYPE_PP,
    .speed = GPIO_OSPEED_2MHZ,
};

constexpr proxy::Motor::Config left_motor_config = {
    .forward_pwm = {
        .gpio = {
            .port = GPIOA,
            .pin = GPIO15,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .rcc_clock = RCC_GPIOA,
            .otype = GPIO_OTYPE_PP,
            .speed = GPIO_OSPEED_2MHZ,
            .alt_func_num = GPIO_AF1,
        },
        .timer = TIM2,
        .oc_id = TIM_OC1,
        .rcc_clock = RCC_TIM2,
        .period = 1000,
        .clock_div = TIM_CR1_CKD_CK_INT,
        .prescaler = 83,
        .oc_mode = TIM_OCM_PWM1,
    },
    .backward_pwm = {
        .gpio = {
            .port = GPIOB,
            .pin = GPIO3,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .rcc_clock = RCC_GPIOB,
            .otype = GPIO_OTYPE_PP,
            .speed = GPIO_OSPEED_2MHZ,
            .alt_func_num = GPIO_AF1,
        },
        .timer = TIM2,
        .oc_id = TIM_OC2,
        .rcc_clock = RCC_TIM2,
        .period = 1000,
        .clock_div = TIM_CR1_CKD_CK_INT,
        .prescaler = 83,
        .oc_mode = TIM_OCM_PWM1,
    },
};

constexpr proxy::Motor::Config right_motor_config = {
    .forward_pwm = {
        .gpio = {
            .port = GPIOA,
            .pin = GPIO8,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .rcc_clock = RCC_GPIOA,
            .otype = GPIO_OTYPE_PP,
            .speed = GPIO_OSPEED_2MHZ,
            .alt_func_num = GPIO_AF1,
        },
        .timer = TIM1,
        .oc_id = TIM_OC1,
        .rcc_clock = RCC_TIM1,
        .period = 1000,
        .clock_div = TIM_CR1_CKD_CK_INT,
        .prescaler = 83,
        .oc_mode = TIM_OCM_PWM1,
    },
    .backward_pwm = {
        .gpio = {
            .port = GPIOA,
            .pin = GPIO9,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .rcc_clock = RCC_GPIOA,
            .otype = GPIO_OTYPE_PP,
            .speed = GPIO_OSPEED_2MHZ,
            .alt_func_num = GPIO_AF1,
        },
        .timer = TIM1,
        .oc_id = TIM_OC2,
        .rcc_clock = RCC_TIM1,
        .period = 1000,
        .clock_div = TIM_CR1_CKD_CK_INT,
        .prescaler = 83,
        .oc_mode = TIM_OCM_PWM1,
    },
};

constexpr uint8_t adc_num_channels = 8;
constexpr uint16_t adc_readings_per_channel = 50;

uint8_t adc_channels[adc_num_channels] = {
    ADC_CHANNEL0,
    ADC_CHANNEL1,
    ADC_CHANNEL2,
    ADC_CHANNEL3,
    ADC_CHANNEL4,
    ADC_CHANNEL5,
    ADC_CHANNEL6,
    ADC_CHANNEL7,
};

constexpr hal::Adc<adc_num_channels>::Config line_sensors_config = {
    .gpio = {
        .port = GPIOA,
        .pin = GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7,
        .mode = GPIO_MODE_ANALOG,
        .pull_resistor = GPIO_PUPD_NONE,
        .rcc_clock = RCC_GPIOA,
    },
    .dma = {
        .dma_number = DMA2,
        .channel = DMA_SxCR_CHSEL_0,
        .stream = DMA_STREAM0,
        .rcc_clock = RCC_DMA2,
        .priority = DMA_SxCR_PL_LOW,
        .memory_size = DMA_SxCR_MSIZE_32BIT,
        .peripheral_size = DMA_SxCR_PSIZE_32BIT,
        .peripheral_address = (uint32_t) &ADC1_DR,
    },
    .adc_number = ADC1,
    .mode = ADC_CCR_MULTI_INDEPENDENT,
    .rcc_clock = RCC_ADC1,
    .rcc_reset = RST_ADC,
    .prescaler = ADC_CCR_ADCPRE_BY4,
    .resolution = ADC_CR1_RES_12BIT,
    .channels = adc_channels,
    .sample_time = ADC_SMPR_SMP_56CYC,
};

#endif // __TARGET_HPP__
