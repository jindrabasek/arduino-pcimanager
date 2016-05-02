/**
 * File: PciManager.cpp
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

#include <Arduino.h>
#include <pins_arduino.h>
#include <PciListener.h>
#include <PciManager.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

inline PciManager::PciManager() :
        firstListener(NULL),
        lastListener(NULL),
        enabled(false) { // disable manager by default
}

PciManager& PciManager::instance() {
    static PciManager instance;
    return instance;
}

void PciManager::registerListener(PciListener* listener) {

    volatile uint8_t* pcicr = digitalPinToPCICR(listener->pciPin);
    *pcicr |= (1 << listener->pciVector);

    volatile uint8_t* pcmsk = digitalPinToPCMSK(listener->pciPin);
    *pcmsk |= (1 << digitalPinToPCMSKbit(listener->pciPin));

    // -- A listener should be registered only once.
    listener->remove();

    if (this->firstListener == NULL) {

        // -- This is the first listener being registered.
        this->firstListener = listener;
        this->lastListener = listener;
    } else {
        this->lastListener->pciNextListener = listener;
        this->lastListener = listener;
    }
    listener->pciNextListener = NULL;
}

void PciManager::removeListener(PciListener* listenerToRemove) {
    listenerToRemove->remove();
    boolean hasMoreListenersOnSamePin = false;
    boolean hasMoreListenersOnSameVector = false;

    PciListener* listener = firstListener;
    while (listener != NULL) {
        if (listener->pciPin == listenerToRemove->pciPin) {
            hasMoreListenersOnSamePin = true;
            hasMoreListenersOnSameVector = true;
            break;
        }
        if (listener->pciVector == listenerToRemove->pciVector) {
            hasMoreListenersOnSameVector = true;
        }
        listener = listener->pciNextListener;
    }

    if (!hasMoreListenersOnSamePin) {
        // -- Remove mask if no other uses this pin.
        volatile uint8_t* pcmsk = digitalPinToPCMSK(listenerToRemove->pciPin);
        *pcmsk &= ~(1 << digitalPinToPCMSKbit(listenerToRemove->pciPin));

        if (!hasMoreListenersOnSameVector) {
            // -- Remove vector registration if no listeners for this vector.
            volatile uint8_t* pcicr = digitalPinToPCICR(
                    listenerToRemove->pciPin);
            *pcicr &= ~(1 << listenerToRemove->pciVector);
        }
    }
}

/**
 * Walk through the chain and call all listener.
 */
void PciManager::callListeners(uint8_t pciVectorId) {
    if (!enabled) {
        return;
    }

    // -- (If first is NULL, than nothing is registered.)
    PciListener* listener = firstListener;
    while (listener != NULL) {
        if (listener->pciVector == pciVectorId) {
            listener->pciHandleInterrupt(pciVectorId);
        }
        listener = listener->pciNextListener;
    }
}

/**
 * Global interrupt handling implementations.
 */
// Jindra: do it manually
/*
 ISR(PCINT0_vect){
 PciManager.callListeners(0);
 }
 ISR(PCINT1_vect){
 PciManager.callListeners(1);
 }
 ISR(PCINT2_vect){
 PciManager.callListeners(2);
 }
 */

