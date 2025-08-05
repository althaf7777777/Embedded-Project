#REAL TIME VEHICLE STATUS MONITORING USING CAN CONTROLLER(PROTOCOL)

DESCRIPTION:

    ## Project Overview
    This embedded systems project implements a Controller Area Network (CAN)-based automotive monitoring system using the LPC2129 microcontroller. It consists of three nodes—Main Node, Fuel Node, and           Indicator Node—communicating via CAN protocol to monitor and control essential automotive functions like airbag deployment, fuel level, and indicator lights.


  ## Key Features

  ### Main Node (Master)
- Reads airbag status using an MMA7660 3-axis accelerometer.
- Receives fuel percentage from the Fuel Node via CAN.
- Sends control commands to Indicator Node based on input switches (left/right).
- Displays system status on 16x2 LCD.
- Includes CAN1 reset logic to recover from bus-off state.

### Fuel Node
- Uses ADC to read analog fuel level sensor.
- Converts ADC value to fuel percentage.
- Transmits fuel data periodically over CAN bus.

### Indicator Node
- Receives direction commands via CAN.
- Controls Left/Right indicator LEDs based on received messages.
  

## Technologies Used
- Microcontroller: LPC2129 (ARM7TDMI-S)
- Communication Protocol: CAN (Polling method)
- Sensors & Modules:
  - MMA7660 Accelerometer (I2C)
  - 16x2 LCD Display
  - ADC for Fuel Sensor
- Development Tools: Flash Magic


## CAN Communication Logic
- Polling-based communication using CAN SFRs.
- Efficient use of CAN1GSR, CAN1MOD, CAN1SR, CAN1CMR, and message objects.
- Message framing complies with standard 11-bit CAN ID format.


## Testing
- Real-time LCD updates: Airbag status, fuel level.
- Indicator LEDs respond to external interrupt-driven input.
- CAN bus debugged using status bits and reset logic for error handling.




## Future Improvements
- Add buzzer for airbag alert.
- RTOS-based version for better scheduling.
