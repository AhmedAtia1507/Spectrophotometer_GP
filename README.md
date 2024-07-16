# Design and Implementation of Electronic System for UV/Vis Spectrophotometer
## About
This repository contains the complete codebase for the UV/Vis Spectrophotometer Control System developed as a graduation project for the Electronics and Communications Engineering (ECE) Department at Ain Shams University class of 2024.
This Project is sponsored by MIAC Company and under the supervision of Dr.Diaa Khalil and Eng. Bassem Ali "Representing MIAC Company".

## Project Group
1. [Ahmed Atia Said Abdelwahed](https://www.linkedin.com/in/ahmed-atia-said-b8aa38135)
2. [Mennat Allah Lotfy Ahmed](https://www.linkedin.com/in/mennalotfy1111)
3. [Donia Saeed Kamal Saeed Ramadan](https://www.linkedin.com/in/donia-saeed-kamal-35551a233/)
4. [Mohanad Mohamed Abdelmonem](https://www.linkedin.com/in/mohanad-mohamed-7860aa203/)
5. [Nabil Youssef Basta Boules](https://www.linkedin.com/in/nabil-youssef-557884219/)
6. [Mina Isaac Sabet Isaac](https://www.linkedin.com/in/mina-isaac-6a98b427a?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app)
7. [Mennat Allah Ayman AbuKhalil](https://www.linkedin.com/in/menna-ayman-24395a247/)
8. [Amal Mohamed Mohamed Hussein](https://www.linkedin.com/in/amal-mohamed2001/)
   
![WhatsApp Image 2024-07-14 at 14 20 57_0917e774](https://github.com/user-attachments/assets/29a35b51-4273-48f2-98f3-667f21a76b22)

## Project Overview
The aim of this project was to design and implement a control system for a UV/Vis spectrophotometer using the STM32F103C8T6 microcontroller. The system ensures the proper functioning of the spectrophotometer components, allows for self-calibration, and performs spectral scans across a range of wavelengths. Additionally, the system interfaces with an ESP32 to enable Wi-Fi connectivity and remote control via a web interface.

## Features
### 1. Peripheral Drivers for STM32F103C8T6
Developed MCAL Drivers for the following peripherals: 
- **NVIC**  (Nested Vectored Interrupt Controller).
- **RCC**   (Reset & Clock Controller).
- **GPIO**  (General Purpose Input/Output).
- **SysTick Timer**.
- **ADC**   (Analog to Digital Converter).
- **UART**  (Universal Asynchronous Receiver/Transmitter).
- **SPI**   (Serial Peripheral Interface).
- **I2C**   (Inter-Integrated Circuit).
- **General Purpose Timers**.
- **RTC**  (Real-Time Clock).
- **EXTI** (External Interrupts).

### 2. Component Status Monitoring
Developed code to check the operational status of spectrophotometer components using the STM32 interface.

### 3. Main Operation Code
Enables the spectrophotometer to:
- **Self-Calibrate**: At power-up, the system calibrates itself to ensure proper scan operation.
- **Perform Scans**: Execute spectral scans within the wavelength range of 190nm to 1100nm.

### 4. ESP32 Interface
The ESP32 serves as a bridge between the spectrophotometer and external devices via Wi-Fi. It enables:
- **Command Reception**: STM32 receives commands from ESP32.
- **Remote Operations**: Execute operations based on received commands via a web interface.

### 5. MATLAB GUI Interface (Optional)
A MATLAB GUI serves as an alternative control interface, allowing direct interaction with the spectrophotometer.

**For more information, please refer to our ![project thesis]
