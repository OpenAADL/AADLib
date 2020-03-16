AIR examples
============

These examples demonstrate support of the AIR hypervisor by GMV ( https://www.gmv.com/en/Products/air/ )

The following examples are available:

* hello: basic example with one partition
* ping: example of two partitions with inter-partition communication
* smp01: example of a system with multiple cores

To compile these examples, run `make air_conf c build_air` from the terminal

to
* generate the AIR XML configuration file (`air_conf` target)
* generate C code using PolyORB-HI/C (`c` target)
* generate AIR-specific code and compile the generated code (`build_air` target)

NOTE:
-----

The following environment variables must be defined

* AIR : AIR base source directory
* RTEMS_MAKEFILE_PATH=$AIR/install/pos/rtems5/rtems5-install/sparc-rtems5/leon3