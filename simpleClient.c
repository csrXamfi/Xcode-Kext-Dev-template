#include <mach/kern_return.h>
#include <stdio.h>
#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <mach-o/loader.h>

io_connect_t gClient = MACH_PORT_NULL;

io_connect_t kextrw_open(void)
{
    io_service_t service = IOServiceGetMatchingService(kIOMainPortDefault, IOServiceMatching("Final"));
    if(!MACH_PORT_VALID(service))
    {
        return MACH_PORT_NULL;
    }

    io_connect_t client = MACH_PORT_NULL;
    kern_return_t ret = IOServiceOpen(service, mach_task_self(), 0, &client);
    IOObjectRelease(service);
    if(ret != KERN_SUCCESS)
    {
        return MACH_PORT_NULL;
    }
    return client;
}

kern_return_t kextrw_kread(io_connect_t client, uint64_t from, void *to, uint64_t len)
{
    uint64_t in[] = { from, (uint64_t)to, len };
    return IOConnectCallScalarMethod(client, 0, in, 3, NULL, NULL);
}

uint32_t kread32(uint64_t addr)
{
    uint32_t val = 0;
    kextrw_kread(gClient, addr, &val, sizeof(val));
    return val;
}

int kextrw_init(void)
{
    gClient = kextrw_open();
    return MACH_PORT_VALID(gClient) ? 0 : -1;
}

void kextrw_close(io_connect_t client)
{
    IOServiceClose(client);
}



int main(void) {
    if (kextrw_init() == -1) {
        printf("Failed to initialize Final\n");
        return 1;
    }
    printf("Success to initialize Final\n");
    kextrw_close(gClient);
    return 0;
}
