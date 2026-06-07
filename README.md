# smart-power-manager.

Objective
An ESP32 monitors a simulated battery level using a potentiometer and automatically prioritizes loads based on available power.
Hardware
•	ESP32 
•	Potentiometer (simulated battery) 
•	LED (lamp) 
•	Servo motor (fan) 
•	Active buzzer (alarm){ fun --(passive with actual sound )}
State 1 — Healthy Battery
Battery: 70–100%
All systems active.
Device	Status
Lamp (LED)	ON
Fan (Servo)	ON
Alarm (Buzzer)	ARMED

Behavior
•	LED stays ON. 
•	Servo sweeps left-right continuously to simulate a running fan. 
•	Buzzer remains silent but ready.
State 2 — Medium Battery
Battery: 40–69%
Non-essential load removed.
Device	Status
Lamp (LED)	ON
Fan (Servo)	OFF
Alarm (Buzzer)	ARMED

State 3 — Critical Battery
Battery: 0–39%
Emergency mode.
Device	Status
Lamp (LED)	OFF
Fan (Servo)	OFF
Alarm (Buzzer)	ACTIVE
Behavior
•	LED turns OFF. 
•	Servo stops. 
•	Buzzer beeps periodically to warn of low battery. 
What Students Learn
•	Analog input (potentiometer) 
•	PWM control (servo) 
•	Digital outputs (LED and buzzer) 
•	Threshold-based decision making 
•	State machines 
•	Power management and load shedding


Guiding steps
	Connect and reads values from the potentiometer (value range  0-4095)
	Assign each value to therespective percentage 
eg
0 - 1638      → Critical (0-39%)
1639 - 2866   → Medium (40-69%)
2867 - 4095   → Healthy (70-100%)

	Add the loads
Lamp
Fan
Buzzer


