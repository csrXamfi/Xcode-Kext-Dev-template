//
//  MyFirstKextUserClient.h
//  MyFirstKext
//
//  Created by mikhail on 05.10.2025.
//

#ifndef Final_h
#define Final_h

#include <IOKit/IOUserClient.h>

class FinalUserClient: public IOUserClient {
    OSDeclareFinalStructors(FinalUserClient);
public:
    virtual bool initWithTask(task_t owningTask, void *securityID, uint32_t type) override;
    virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments *args, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference) override;
private:
    static IOReturn kread(FinalUserClient *client, void *reference, IOExternalMethodArguments *args);
    
};

#endif /* MyFirstKextUserClient_h */
