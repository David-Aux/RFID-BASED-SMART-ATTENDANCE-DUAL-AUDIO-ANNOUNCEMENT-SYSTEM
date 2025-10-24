# RFID-BASED-SMART-ATTENDANCE-DUAL-AUDIO-ANNOUNCEMENT-SYSTEMNDANCE & DUAL AUDIO ANNOUNCEMENT SYSTEM 

1. Project Overview
This project integrates RFID technology with dual DFPlayer Mini audio modules and an ESP32 microcontroller to create a system for automatic student attendance and real-time class announcements.The system works as follows:
When a student scans their RFID card, the system:
Recognizes their name (instead of just UID).
Records attendance in the serial log.
At fixed time intervals (e.g., every 15 seconds for demo/testing):
Speaker 1 plays one announcement (e.g., "JSS1 has Maths").
Speaker 2 plays another announcement simultaneously (e.g., "SS3 has Chemistry").
This system can be deployed in schools, universities, offices, and factories for smart attendance and automated announcements.

2. System Components
Hardware
ESP32 Development Board – microcontroller for RFID and audio control.
RC522 RFID Reader Module – detects RFID cards/tags.
DFPlayer Mini (x2) – audio playback modules with microSD cards.
Speakers (x2) – for audio output.
RFID Cards/Tags – assigned to students/staff.
MicroSD Cards (x2) – store MP3 files for each DFPlayer.


Software
Arduino IDE (programming environment).
Libraries used:
SPI.h – SPI communication for RFID.
MFRC522.h – for RFID module.
DFRobotDFPlayerMini.h – for DFPlayer Mini.


3. Wiring Connections

RFID RC522 → ESP32
RC522 Pin	ESP32 Pin
SDA (SS)	21
RST	22
SCK	18
MOSI	23
MISO	19
VCC	3.3V
GND	GND


DFPlayer 1 (Speaker 1) → ESP32

DFPlayer 1 Pin	ESP32 Pin

TX	16 (RX2)
RX	17 (TX2)
VCC	5V
GND	GND
SPK1/SPK2	Speaker 1

DFPlayer 2 (Speaker 2) → ESP32

DFPlayer 2 Pin	ESP32 Pin

TX	26 (RX1)
RX	27 (TX1)
VCC	5V
GND	GND
SPK1/SPK2	Speaker 2


4. File Naming on SD Cards
0002.mp3 → "JSS1 has Maths"
Speaker 2 SD Card:
0003.mp3 → "SS3 has Chemistry"

Important: DFPlayer Mini only recognizes audio files named as 0001.mp3, 0002.mp3, etc., in the root directory.

5. RFID Attendance
When a card is scanned, the UID is read.
UID is matched against the students[] array.

If found:
Student name is displayed on Serial Monitor.
If not found:
Shows Unknown user on Serial Monitor.

6. Periodic Announcements
Every 15 seconds (for demo), system triggers:
Speaker 1 → plays 0002.mp3 (JSS1 class).
Speaker 2 → plays 0003.mp3 (SS3 class).

7. Sample Serial Monitor Output
RFID + Dual DFPlayer Test Started...
DFPlayer 1 ready!
DFPlayer 2 ready!

Attendance recorded: User's name
Playing greeting: Track 1

Playing announcements...
Speaker 1 → 0002.mp3: JSS1 has Maths
Speaker 2 → 0003.mp3: SS3 has Chemistry

3. Applications
Schools/Universities: Automated roll call + daily announcements.
Factories: Worker attendance + shift/break alerts.
Offices: Employee check-in + meeting reminders.
Events/Exams: Identity verification + session announcements.
