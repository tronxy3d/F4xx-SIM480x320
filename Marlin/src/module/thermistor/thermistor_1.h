/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

// R25 = 100 kOhm, beta25 = 4092 K, 4.7 kOhm pull-up, bed thermistor
constexpr temp_entry_t temptable_1[] PROGMEM = {
  { OV(  19), 300 },
  { OV(  20), 295 },
  { OV(  22), 290 },
  { OV(  24), 285 },
  { OV(  26), 280 },
  { OV(  28), 275 },
  { OV(  30), 270 },
  { OV(  33), 265 },
  { OV(  36), 260 },
  { OV(  40), 255 },
  { OV(  43), 250 },
  { OV(  47), 245 },
  { OV(  51), 240 },
  { OV(  56), 235 },
  { OV(  61), 230 },
  { OV(  66), 225 },
  { OV(  73), 220 },
  { OV(  78), 215 },
  { OV(  86), 210 },
  { OV(  94), 205 },
  { OV( 104), 200 },
  { OV( 115), 195 },
  { OV( 127), 190 },
  { OV( 139), 185 },
  { OV( 153), 180 },
  { OV( 168), 175 },
  { OV( 185), 170 },
  { OV( 203), 165 },
  { OV( 222), 160 },
  { OV( 244), 155 },
  { OV( 267), 150 },
  { OV( 292), 145 },
  { OV( 320), 140 },
  { OV( 348), 135 },
  { OV( 379), 130 },
  { OV( 411), 125 },
  { OV( 445), 120 },
  { OV( 480), 115 },
  { OV( 516), 110 },
  { OV( 553), 105 },
  { OV( 591), 100 },
  { OV( 628),  95 },
  { OV( 665),  90 },
  { OV( 702),  85 },
  { OV( 737),  80 },
  { OV( 770),  75 },
  { OV( 801),  70 },
  { OV( 830),  65 },
  { OV( 857),  60 },
  { OV( 881),  55 },
  { OV( 903),  50 },
  { OV( 922),  45 },
  { OV( 939),  40 },
  { OV( 954),  35 },
  { OV( 966),  30 },
  { OV( 977),  25 },
  { OV( 985),  20 },
  { OV( 993),  15 },
  { OV( 999),  10 },
  { OV(1004),   5 },
  { OV(1008),   0 },
  { OV(1012),  -5 },
  { OV(1016), -10 },
  { OV(1020), -15 }
};
