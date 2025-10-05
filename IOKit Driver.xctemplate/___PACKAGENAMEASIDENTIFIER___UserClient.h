//
//  MyFirstKextUserClient.h
//  MyFirstKext
//
//  Created by mikhail on 05.10.2025.
//

#ifndef ___PACKAGENAME____h
#define ___PACKAGENAME____h

#include <IOKit/IOUserClient.h>

class ___PACKAGENAME___UserClient: public IOUserClient {
    OSDeclareFinalStructors(___PACKAGENAME___UserClient);
public:
    virtual bool initWithTask(task_t owningTask, void *securityID, uint32_t type) override;
    virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments *args, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference) override;
private:
    static IOReturn kread(___PACKAGENAME___UserClient *client, void *reference, IOExternalMethodArguments *args);
    
};

#endif /* MyFirstKextUserClient_h */
