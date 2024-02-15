# kernel-modules

This repo contains a bunch of kernel modules that don't do much.

## Instructions

These might not work with linux kernel version < 5.6.0.

### To Build
```make```

### To Use
Insert the built module into the kernel
```sudo insmod <module>.ko```

Remove the module from the kernel
```sudo rmmod <module>```

