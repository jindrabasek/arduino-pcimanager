/*
 * PciListener.cpp
 *
 *  Created on: 14. 1. 2016
 *      Author: jindra
 */

#include <pins_arduino.h>
#include <PciListener.h>
#include <stddef.h>
#include <stdint.h>

PciListener::PciListener(uint8_t pciPin) :
        pciPin(pciPin),
        pciVector(digitalPinToPCICRbit(pciPin)),
        pciNextListener(NULL),
        prevToThisListener(NULL) {
}

void PciListener::remove() {
    if (prevToThisListener != NULL) {
        *prevToThisListener = pciNextListener;
        prevToThisListener = NULL;
        pciNextListener = NULL;
    }
}

