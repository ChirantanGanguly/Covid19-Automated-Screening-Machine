# Covid19-Automated-Screening-Machine

This repository is dedicated to an ongoing project on making an Automated Covid19 Screening Machine, regular project reports and codes would be uploaded, as any progress is made.

## Aim
To automate the temperature based screening task for COVID'19 screening.

## Currently added working features:
- Detect and alert whenever a person is in between the range of 10cm to 20cm in front of the machine.
- Measures his/her temperature
- It should measure temperature only when someone is detected not all the time.
- If the temperature is high, then a buzzer & RED LED should be turned on, to alert Gatekeeper.
- If the temperature is normal, then it should turn on the GREEN LED.
- It should spray sanitizer whenever hands are placed below a knob/a fixed point
- Display all relevant things over the LCD & Serial Monitor simultaneously.
- Count of the number of person currently inside should be maintained and displayed properly.

## Scope of Improvement:
- [TMP36], the only temperature sensor available in TinkerCAD measures the temperature of the ambient, so it will not be an accurate/appropriate sensor to use for measuring body temperatures.
- Door locking mechanism could be incorporated with the arduino for increased functionality.
- With the help of a camera, and a bit of Machine Learning application, a mask detection algorithm night be set up to stop entry of anyone without a mask
- IR sensor / PIR sensor maybe used instead of Ultrasonic distance sensor at the sanitation unit
