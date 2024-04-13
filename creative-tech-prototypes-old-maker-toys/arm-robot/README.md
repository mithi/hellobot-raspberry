# [☕](https://ko-fi.com/minimithi) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE) [![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black) [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/mithi/arm-robot-simulator/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22) [![HitCount](https://hits.dwyl.com/mithi/arm-robot-simulator.svg)](https://hits.dwyl.com/mithi/arm-robot-simulator)

# arm-robot-simulator

# Notes

```bash
virtualenv venv
source venv/bin/activate
pip install dash
pip install plotly
pip install gunicorn
pip freeze > requirements.txt
```

- https://www.geogebra.org/m/E9g4q7F5
- https://www.toptal.com/robotics/programming-a-robot-an-introductory-tutorial
- IK Discussion: https://appliedgo.net/roboticarm/
- callback to hover_data: https://community.plotly.com/t/capturing-mouse-events-position/4616/2
- lerp : https://www.gamedev.net/articles/programming/general-and-gameplay-programming/a-brief-introduction-to-lerp-r4954/
- python serial to arduino https://towardsdatascience.com/how-to-drive-your-arduino-propulsed-robot-arm-with-python-4e428873237b

python

```python
import serial

arduino = serial.Serial(port = "/dev/ttyACM2", baudrate = 9600, timeout=1)

arduino.write(struct.pack('>B', (90 - teta1)))
arduino.write(struct.pack('>B', (90 - teta2 - teta1)))
arduino.write(struct.pack('>B', (teta3 + 50)))

arduino.close()
```

c++

```c++
void setup() {
  Serial.begin(9600) ;
}

void loop() {
  if(Serial.available()) {
    teta1 = Serial.read();
    teta2 = Serial.read();
    teta3 = Serial.read();
  }
}
```