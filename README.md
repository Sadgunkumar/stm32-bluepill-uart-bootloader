# STM32 Blue Pill (STM32F103C8T6) – UART Bootloader Programming via FTDI

## 🚀 Overview

This project demonstrates how to upload code to the STM32F103C8T6 (Blue Pill) using an FTDI USB-to-Serial adapter via the built-in UART bootloader — without using an ST-Link debugger.

It also includes a bare-metal LED blink example using direct register manipulation.

---

## 🧰 Hardware Required

- STM32F103C8T6 (Blue Pill)
- FTDI USB-to-Serial Adapter
- Jumper Wires
- USB Cable

---

## 🔌 Circuit Connections

| FTDI Pin | Blue Pill Pin |
|----------|---------------|
| GND      | GND           |
| VCC      | 3.3V / 5V *(match FTDI)* |
| TX       | PA10 (RX1)    |
| RX       | PA9 (TX1)     |

> ⚠️ Ensure voltage compatibility (prefer 3.3V)

---

## 🔁 Bootloader Mode Setup

To enable UART flashing:

- Set **BOOT0 = 1**
- Set **BOOT1 = 0**
- Press **RESET**

---

## 🛠️ Build Process (STM32CubeIDE)

1. Create Empty Project for STM32F103C8
2. Enable binary output:

Project → Properties → C/C++ Build → Settings → MCU Post build outputs

3. Enable:

Convert to binary file (-O binary)


4. Build project → `.bin` file generated in `/Debug`

---

## 📥 Flashing Using STM32CubeProgrammer

1. Select **UART mode**
2. Baudrate: **115200**
3. Select correct COM port
4. Click **Connect**
5. Load `.bin` file
6. Click **Start Programming**

---

## ▶️ Run the Code

- Set **BOOT0 = 0**
- Press **RESET**

✔ LED on PC13 starts blinking

---

## 💻 Code Explanation

This project uses **bare-metal programming** (no HAL).

### Key Registers Used:

- RCC_APB2ENR → Enable GPIO clock
- GPIOC_CRH → Configure pin mode
- GPIOC_ODR → Control output

---

## 🧠 Bitmasking Concept

```
GPIOC_CRH &= ~(0xF << 20); // Clear bits
GPIOC_CRH |=  (0x2 << 20); // Set output mode
