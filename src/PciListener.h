/**
 * File: PciListener.h
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

#ifndef PCI_LISTENER_H
#define PCI_LISTENER_H

#include <stdint.h>

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

/**
 * PinChangeInterrupt listener abstract class. Please override this class with a custom pciHandleInterrupt() callback.
 */
class PciListener {
public:
    PciListener(uint8_t pciPin = 0);

    /**
     * This method will be called by the PciManager on pin change. The function will be fired if any of the registered pins
     * are fired within the same vector.
     *  vector - Vector can be 0, 1 or 2 depending on the changed pin. (This parameter is not very useful.)
     */
    virtual void pciHandleInterrupt(uint8_t vector)=0;

    void remove();

    /** The pin being registered by this listener */
    uint8_t pciPin;

    /** The PCI vector this pin belongs to. */
    uint8_t pciVector;

    /** For internal use. Do not modify. */
    PciListener* pciNextListener;

    /**
     * This member is for internal use only. Do not change!
     */
    PciListener** prevToThisListener;
};

#pragma GCC diagnostic pop

#endif

