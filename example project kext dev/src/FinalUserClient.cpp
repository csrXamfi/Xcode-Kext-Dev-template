//
//  MyfirstKextUserClient.cpp
//  MyFirstKext
//
//  Created by mikhail on 05.10.2025.
//

#include "FinalUserClient.h"
#include <IOKit/IOReturn.h>
#include <string.h>
#include <kern/task.h>
#include <libkern/copyio.h>
#include <libkern/libkern.h>
#include <mach/vm_param.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOMemoryDescriptor.h>

#define super IOUserClient
OSDefineMetaClassAndFinalStructors(FinalUserClient, IOUserClient)

bool FinalUserClient::initWithTask(task_t owningTask, void *securityID, uint32_t type) {
    if (!super::initWithTask(owningTask, securityID, type)) {
        return false;
    }

    bool allow = false;
    OSObject *entitlement = copyClientEntitlement(owningTask, "com.apple.security.example.example-krnl");
    if (entitlement) {
        allow = (entitlement == kOSBooleanTrue);
        entitlement->release();
    }
    return allow;
}

IOReturn FinalUserClient::externalMethod(uint32_t selector, IOExternalMethodArguments *args, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference) {
    static const IOExternalMethodDispatch methods[] =
    {
        /* 0 */ { (IOExternalMethodAction)&FinalUserClient::kread,  3, 0, 0, 0 },
    };

    if(selector < sizeof(methods)/sizeof(methods[0]))
    {
        dispatch = const_cast<IOExternalMethodDispatch*>(&methods[selector]);
        target = this;
    }
    return super::externalMethod(selector, args, dispatch, target, reference);
}

IOReturn FinalUserClient::kread(FinalUserClient *client, void *reference, IOExternalMethodArguments *args)
{
    int r = copyout((const void*)args->scalarInput[0], (user_addr_t)args->scalarInput[1], args->scalarInput[2]);
    return r == 0 ? kIOReturnSuccess : kIOReturnVMError;
}



