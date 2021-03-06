/**
 * File: PciListenerImp.h
 * Description:
 * PciManager library is an easy to use Pin Change Interrupt manager for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2012 Balazs Kelemen
 * Copying permission statement:
 This file is part of PciManager.

 PciManager is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef PCI_LISTENERIMP_H
#define PCI_LISTENERIMP_H

#include <PciListener.h>
#include <stdbool.h>
#include <stdint.h>

#define CHANGEKIND_HIGH_TO_LOW LOW
#define CHANGEKIND_LOW_TO_HIGH HIGH

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

/**
 * A basic PinChangeInterrupt listener implementation.
 */
class PciListenerImp : public PciListener {
public:
    /**
     * For the constructor add a function callback, that will be called either with CHANGEKIND_HIGH_TO_LOW or CHANGEKIND_LOW_TO_HIGH.
     */
    PciListenerImp(uint8_t pin, void (*callback)(uint8_t changeKind), bool pullUp = false);
    virtual void pciHandleInterrupt(uint8_t vector);
private:
    void (*_callback)(uint8_t changeKind);
    uint8_t _lastVal;
};

#pragma GCC diagnostic pop

#endif

