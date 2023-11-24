# 给笨蛋用的syscall及NTDLL获取方法

## 谁在用这个方法？

自己在用

## 哪些syscall可以这样计算？

只测试了纯64位Windows系统的个别syscall，详情见 https://j00ru.vexillium.org/syscalls/nt/64/

## 如何定位NTDLL？

Windows有个系统调用`NtQueryVirtualMemory`，给定一个地址可以查询其所在虚拟内存的状态，用法见 https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryvirtualmemory

由于NTDLL在进程的第一个线程执行之前已经被加载到进程虚拟空间，所以任何情况下我们都能通过遍历虚拟内存找到NTDLL直接使用。首先用仓库里的方法获取`NtQueryVirtualMemory`的调用号，之后从`0x7FFFFFFFF000`往低地址查询所有大小为4KB、属性为IMAGE且只有读权限（注意不能有奇怪的权限，可能是检测探针）的虚拟内存，以MZ开头的即为DLL文件。通常找到的第一个就是NTDLL，如果不放心的话也可以在解析PE文件时判断是否是NTDLL。

## 获取PEB的方法？

Windows还有个系统调用`NtQueryInformationProcess`，能够获取进程的一些信息，最基础的用法就能查询PEB的地址，用法见 https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess
