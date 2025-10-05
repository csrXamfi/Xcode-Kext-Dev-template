//
//  Final.cpp
//  Final
//
//  Created by mikhail on 05.10.2025.
//

#include "Final.h"

#define super IOService

OSDefineMetaClassAndFinalStructors(Final, IOService)

bool Final::start(IOService* provider) {
    IOLog("%s::starting...\n", getName());

    if (!super::start(provider)) {
        IOLog("%s::super start failed!\n", getName());
        return false;
    }

    // Implement your start code here.
    registerService();
    return true;
}

void Final::stop(IOService* provider) {
    IOLog("%s::stopping...\n", getName());

    // Implement your stop code here.

    super::stop(provider);
}
