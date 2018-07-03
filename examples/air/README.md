AIR examples
============

These examples demonstrate support of the AIR hypervisor by GMV ( https://www.gmv.com/en/Products/air/ )

The following examples are available:

* hello: basic example with one partition

* ping: example of two partitions with inter-partition communication

To compile these examples, run

make air_conf c build_air

to
- generate the AIR XML configuration file (air_conf target)
- generate C code using PolyORB-HI/C (c target)
- generate AIR-specific code and compile the generated code (build_air target)