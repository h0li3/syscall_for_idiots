#include <stdio.h>

int main()
{
    char* ksd = (char*)0x7ffe0000;

    int major = *(int*)(ksd + 0x026C);
    int minor = *(int*)(ksd + 0x0270);
    int build = 0;
    int addend = 0;

    printf("major: %u\n", major);
    printf("minor: %u\n", minor);

    if (major >= 10) {
        build = *(int*)(ksd + 0x0260);
        printf("build: %u\n", build);
        printf("version: %u.%u.%u\n", major, minor, build);
    }
    else {
        printf("version: %u.%u\n", major, minor);
    }

    if (major <= 6 && minor <= 1) {      // Windows 2008 and others
        addend = 0;
    }
    else if (major == 6 && minor == 2) { // Windows 2012 and Windows 8.0
        addend = 1;
    }
    else if (major == 6 && minor == 3) { // Windows 2012 R2 and Windows 8.1
        addend = 2;
    }
    else {                               // Windows 10 and Windows 11
        addend = 3;
    }

    int syscall_NtAVM = 0x15 + addend;
    int syscall_NtPVM = 0x4d + addend;
    int syscall_NtFVM = 0x1b + addend;
    int syscall_NtClose = 0x0c + addend;

    printf("syscall NtAllocateVirtualMemory is 0x%04x\n", syscall_NtAVM);
    printf("syscall NtProtectVirtualMemory  is 0x%04x\n", syscall_NtPVM);
    printf("syscall NtFreeVirtualMemory     is 0x%04x\n", syscall_NtFVM);
    printf("syscall NtClose                 is 0x%04x\n", syscall_NtClose);
}
