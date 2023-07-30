# BYD Battery-Box Premium LVS CAN Protocol

A "reverse engineering" of the BYD Battery-Box Premium LVS CAN protocol when used with Victron/Venus OS.

The following information has been discovered between a BYD Battery-Box Premium LVS B019 / v1.23 and a Victron Venus OS v3.00. Battery-Box consist of 2 batteries in 1 tower (48V, 2* 78Ah).

CAN protocol is set to 500kBit/s (no FD). All frames are sent with 8 bytes length (zero padded).

When emulating a BYD battery it seems to be sufficient to just periodically send the following frames with a `1000ms` delay:

1. 0x35E
2. 0x382
3. 0x35F
4. 0x35A
5. 0x35B
6. 0x351
7. 0x355
8. 0x356
9. 0x360
10. 0x372
11. 0x373
12. 0x374
13. 0x375
14. 0x376
15. 0x377
16. 0x378
17. 0x379

Things to note:

* Frames sent from Victron seem to be ignorable. We can just start sending the frames at any time.
* I did not check if the order of the frames is important. The above sequence seems to work.
* If frames are not sent completeley or properly, Venus OS tends to recognise the sender as "Pylontech" or "CAN bus BMS".
* If frames are not sent frequently enough, Venus OS interprets the sender as being disconnected (offering to *remove* the device).
* "Redetect battery" in Venus OS seems to send some frames to the "battery". It seems to be sufficient to just keep on sending the above frames (no other sequence needed).
* All information has been dumped on a Raspberry 4 with Venus OS v3.00 (as written above) and a RS485 CAN HAT with `candump`.
* Emulation of the battery has beend done from an Espressif ESP32 (and S2, S3) with a TJA1051 transceiver.

## Victron Communication / Identifiers

| Id  | Hex | Ascii | Description |
| --- | ----------------------- | -------- | --- |
| 305 | 00 00 00 00 00 00 00 00 | ........ | ? it seems when no battery present: 305 and 307 are sent rapdily |
| 306 | 00 00 00 00 00 00 00 00 | ........ | ? it seems when battery is present: 305, 306 and 307 are sent periodically |
| 307 | 12 34 56 78 56 49 43 00 | .4VxVIC. | ? it seems when no battery present: 305 and 307 are sent rapdily |

## BYD Communication / Identifiers
| Id  | Hex | Ascii | Description |
| --- | ----------------------- | -------- | --- |
| 350 |                         |          | *not seen* |
| 351 | 48 02 00 05 00 05 AE 01 | H....... | CVL, CCL, DCL, DVL |
|     |                         |          | [00:01] "48 02" (mV/10) 58.4V CVL |
|     |                         |          | [02:03] "00 05" (A/10) 128.0A CCL |
|     |                         |          | [04:05] "00 05" (A/10) 128.0A DCL |
|     |                         |          | [06:07] "AE 01" (mV/10) 43.0V DVL |
| 352 |                         |          | *not seen* |
| 353 |                         |          | *not seen* |
| 354 |                         |          | *not seen* |
| 355 | 43 00 64 00 00 00 00 00 | C.d..... | State of Charge, State of Health |
|     |                         |          | [00:01] "43 00" (%) 67% SoC |
|     |                         |          | [02:03] "64 00" (%) 100% SoH |
|     |                         |          | [04:05] always null, *???* |
|     |                         |          | [06:07] always null, *???* |
| 356 | BE 14 F9 FF 8C 00 00 00 | ........ | Voltage, Amps, Temperature |
|     |                         |          | [00:01] "BE 14" (mV/10) 53.1V current voltage |
|     |                         |          | [02:03] "F9 FF" (A/10, signed) -0.7A consumed Amps; "-" discharge / "+" charge |
|     |                         |          | [04:05] "8C 00" (°C/10, signed) 14.0°C battery temperature |
|     |                         |          | [06:07] always found to be null, *???* definitely not Watts |
| 357 |                         |          | *not seen* |
| 358 |                         |          | *not seen* |
| 359 |                         |          | *not seen* |
| 35A | AA AA AA AA AA AA AA AA | ........ | Alarms and Warnings, bit field, 'AA' means OK |
|     | 10 .. .. .. .. .. .. .. | ........ | [00] "10" Low battery voltage: Alarm |
|     | .. .. .. .. 10 .. .. .. | ........ | [04] "10" Low battery voltage: Warning |
|     | 04 .. .. .. .. .. .. .. | ........ | [00] "04" High battery voltage : Alarm |
|     | .. .. .. .. 04 .. .. .. | ........ | [04] "04" High battery voltage : Warning |
|     | .. .. 01 .. .. .. .. .. | ........ | [02] "01" High charge current: Alarm |
|     | .. .. .. .. .. .. 01 .. | ........ | [06] "01" High charge current: Warning |
|     | .. 40 .. .. .. .. .. .. | ........ | [01] "40" High discharge current: Alarm |
|     | .. .. .. .. .. 40 .. .. | ........ | [05] "40" High discharge current: Warning |
|     | .. 01 .. .. .. .. .. .. | ........ | [01] "01" Low temperature: Alarm |
|     | .. .. .. .. .. 01 .. .. | ........ | [05] "01" Low temperature: Warning |
|     | 40 .. .. .. .. .. .. .. | ........ | [00] "40" High temperature: Alarm |
|     | .. .. .. .. 40 .. .. .. | ........ | [04] "40" High temperature: Warning |
|     | .. 10 .. .. .. .. .. .. | ........ | [01] "10" Low charge temperature: Alarm |
|     | .. .. .. .. .. 10 .. .. | ........ | [05] "10" Low charge temperature: Warning |
|     | .. 04 .. .. .. .. .. .. | ........ | [01] "04" High charge temperature: Alarm |
|     | .. .. .. .. .. 04 .. .. | ........ | [05] "04" High charge temperature: Warning |
|     | .. .. 40 .. .. .. .. .. | ........ | [02] "40" Internal failure: Alarm |
|     | .. .. .. .. .. .. 40 .. | ........ | [06] "40" Internal failure: Warning |
|     | .. .. .. 01 .. .. .. .. | ........ | [03] "01" Cell imbalance: Alarm |
|     | .. .. .. .. .. .. .. 01 | ........ | [07] "01" Cell imbalance: Warning |
| 35B | 00 00 00 00 00 00 00 00 | ........ | *???* always found to be null |
| 35C |                         |          | *not seen* |
| 35D |                         |          | *not seen* |
| 35E | 42 59 44 00 00 00 00 00 | BYD..... | Manufacturer |
|     |                         |          | [00:02] "BYD" (string) "BYD" manufacturer identification
|     |                         |          | [04:07] always found to be null
| 35F | 4C 69 01 17 69 00 00 00 | Li..i... | Firmware version, Ah available |
|     |                         |          | [00:01] "4C 69" product code, always seen that value |
|     |                         |          | [02:03] "01 17" v1.17 firmware version |
|     |                         |          | [04:05] "69 00" (Ah) 105Ah capacity available |
|     |                         |          | [06:07] *???* always found to be null |
| 360 | 00 00 00 00 00 00 00 00 | ........ | *???* always found to be null |
| 361 |                         |          | *not seen* |
| 362 |                         |          | *not seen* |
| 363 |                         |          | *not seen* |
| 364 |                         |          | *not seen* |
| 365 |                         |          | *not seen* |
| 366 |                         |          | *not seen* |
| 367 |                         |          | *not seen* |
| 368 |                         |          | *not seen* |
| 369 |                         |          | *not seen* |
| 36A |                         |          | *not seen* |
| 36B |                         |          | *not seen* |
| 36C |                         |          | *not seen* |
| 36D |                         |          | *not seen* |
| 36E |                         |          | *not seen* |
| 36F |                         |          | *not seen* |
| 370 |                         |          | *not seen* |
| 371 |                         |          | *not seen* |
| 372 | 02 00 00 00 00 00 00 00 | ........ | |
|     |                         | ........ | 2 batteries online, 0 batteries offline |
|     | 02 00                   | ........ | [00:01] "02 00" batteries online |
|     |                         | ........ | [02:03] *???*, seems to be ignored by Venus OS, see below |
|     |                         | ........ | [04:05] *???*, seems to be ignored by Venus OS, see below |
|     |                   01 00 | ........ | [06:07] "01 00" batteries offline |
|     |                         | ........ | BYD system sent these frames upon first power up: |
|     | 02 00 02 00 01 00 00 00 | ........ | Frame 01 |
|     | 02 00 00 00 00 00 00 00 | ........ | Frame 02 + consecutive frames |
| 373 | EA 0C 01 0D 1F 01 22 01 | ......". | Cell Voltage and Temperature |
|     |                         |          | [00:01] "EA 0C" (mV) 3.306V Lowest Cell Voltage, see 374 |
|     |                         |          | [02:03] "01 0D" (mV) 3.329V Highest Cell Voltage, see 375 |
|     |                         |          | [04:05] "1F 01" (K +1K) 15°C Minimum Cell Temperature, see 376 |
|     |                         |          | [06:07] "22 01" (K +1K) 18°C Maximum Cell Temperature, see 377 |
| 374 | 32 00 00 00 00 00 00 00 | 2....... | Cell name (string) with "Lowest Cell Voltage", see 373 |
| 375 | 32 00 00 00 00 00 00 00 | 2....... | Cell name (string) with "Highest Cell Voltage", see 373 |
| 376 | 32 00 00 00 00 00 00 00 | 2....... | Cell name (string) with "Minimum Cell Temperature", see 373 |
| 377 | 31 00 00 00 00 00 00 00 | 1....... | Cell name (string) with "Maximum Cell Temperature", see 373 |
| 378 | 40 08 00 00 2B 07 00 00 | @...+... | History Charged / Discharged Energy |
|     |                         |          | [00:03] "40 08 00 00" (kWh/10) 211.2kWh Charged Energy |
|     |                         |          | [04:07] "2B 07 00 00" (kWh/10) 183.5kWh Discharged Energy |
| 379 | 9C 00 00 00 00 00 00 00 | ........ | Installed Ah |
|     |                         |          | [00:01] "9C 00" (Ah) 156Ah |
|     |                         |          | [02:07] *???* always found to be null |
| 37A |                         |          | *not seen* |
| 37B |                         |          | *not seen* |
| 37C |                         |          | *not seen* |
| 37D |                         |          | *not seen* |
| 37E |                         |          | *not seen* |
| 37F |                         |          | *not seen* |
| 380 |                         |          | *not seen* |
| 381 |                         |          | *not seen* |
| 382 | 50 52 45 4D 49 55 4D 00 | PREMIUM. | Product identification |
|     |                         |          | [00:06] "PREMIUM" (string) product identification |
|     |                         |          | [07] always found to be null
| 383 |                         |          | *not seen* |
| 384 |                         |          | *not seen* |
| 385 |                         |          | *not seen* |
| 386 |                         |          | *not seen* |
| 387 |                         |          | *not seen* |
| 388 |                         |          | *not seen* |
| 389 |                         |          | *not seen* |
| 38A |                         |          | *not seen* |
| 38B |                         |          | *not seen* |
| 38C |                         |          | *not seen* |
| 38D |                         |          | *not seen* |
| 38E |                         |          | *not seen* |
| 38F |                         |          | *not seen* |

### What is missing?

* Nr of modules blocking charge/discharge (not clear if supported)
* Alarms
* Events
* Consumed Watts
 
### Unclear

* Product ID (maybe 0x35F [00:01])

### How it looks like in Venus OS

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/fd1df1f5-c802-41c7-9ff3-1f68f695cdf0)

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/5eaee6eb-bb81-44ef-a22e-62d69963242a)

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/213ceb5c-c057-4ed3-9657-6a9f8539e8a1)

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/f4354565-231f-448a-81c7-6941101ef4ee)

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/fba35b97-368c-433b-9b05-abe23abda00a)

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/9f149474-2156-4844-aeab-aa28d0c17530)

## Similarities with the SMA protocol

After I finished documenting the protocol, I stumbled across a document about the SMA CAN protocol "Technical Information:
Connecting Batteries with external Battery Management System to SUNNY ISLAND 6.0H-11" ("SMA CAN protocol.pdf"). Here is a table with some of their CAN ids - which seem to be similar to BYD.

*HiResSOC* 0x355 [04:07] and *Events* 0x35B do not seem to be supported on BYD.

![image](https://github.com/dfch/BydCanProtocol/assets/8310360/83f8146b-ed54-4deb-baa8-ca7557dd9377)


