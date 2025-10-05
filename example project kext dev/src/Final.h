//
//  Final.h
//  Final
//
//  Created by mikhail on 05.10.2025.
//

#ifndef Final_h
#define Final_h

// IOKit Libs Header
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

/*! @class Final
    @abstract Add your own class abstract here.
    @discussion Add your own class discussion here. */

class Final : public IOService {
    OSDeclareFinalStructors(Final)

public:
    /* IOKit Based Functions */
#pragma mark IOKit Based Functions

/*! @function start
    @abstract During Final object's instantiation, starts the Final object that has been selected to run on the provider.
    @discussion Add your own discussion here.
    @result <code>true</code> if the start was successful; <code>false</code> otherwise (which will cause the instance to be detached and usually freed). */

    virtual bool start(IOService* provider) APPLE_KEXT_OVERRIDE;

/*! @function stop
    @abstract During Final termination, the stop method is called in its clients before they are detached & it is destroyed.
    @discussion Add your own discussion here. */

    virtual void stop(IOService* provider) APPLE_KEXT_OVERRIDE;
 
    /* Final Functions */
#pragma mark Final Functions
    /* Define your own functions here. It's strongly recommanded that you classify your own functions by using #pragma mark */
    
};

#endif /* Final_h */
