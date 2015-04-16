
This project shows how to create an executable of a smaller size than usually.

The source file Tiny.cpp includes <winapi.h>, but before it it defines the
PURE_WRAPPER macro, in order to get rid of the additional virtual methods.
Therefore all message handling must occur in HandleMessage().

The debug configuration is normal, and the executable size is big is as usual.

In the release configuration, /nodefaultlibs are used and the additional
project files include required but missing C++ functionality.

Additionally, the C++ exceptions are turned off and all size-optimisations
are turned on. The final executable size is 4KB.
