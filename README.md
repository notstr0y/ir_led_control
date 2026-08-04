# IR Remote → LED Control

Fan remote buttons map to individual LEDs via an IR receiver, using Arduino Uno + PlatformIO.

## Status
4 LEDs working, mapped to buttons 1-4 on the remote.

## Hardware
- Arduino Uno R3
- VS1838B IR receiver
- 4x LED + 4x current-limiting resistor (220-330Ω)

## Wiring
| Component | Arduino pin |
|---|---|
| IR receiver OUT | D7 |
| IR receiver VCC | 5V |
| IR receiver GND | GND |
| LED 1 (+resistor) | D3 |
| LED 2 (+resistor) | D4 |
| LED 3 (+resistor) | D5 |
| LED 4 (+resistor) | D6 |
| All LED cathodes | shared GND rail → Arduino GND |

## Button → code mapping (NEC, address 0xF300)
| Button | Raw hex |
|---|---|
| 1 | 0x748BF300 |
| 2 | 0x6F90F300 |
| 3 | 0x758AF300 |
| 4 | 0x6C93F300 |
| 5 | 0x7788F300 |
| Power (clear) | 0x6E91F300 |

## Behavior
Pressing button N lights N LEDs (cumulative, not exclusive — button 3 lights LEDs 1,2,3 together). Power button clears all LEDs.

## Build / flash
```bash
pio run -t upload
pio device monitor
```

## Notes
- IR frames report as `0x0` for repeat signals (held button / spacing artifact) — intentionally ignored in code.
- Library: `z3t0/IRremote @ ^4.4.0`, added via `platformio.ini` `lib_deps`.




