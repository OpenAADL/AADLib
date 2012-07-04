AADL_SOURCES=					\
	$(srcdir)/boards-arduino.aadl		\
	$(srcdir)/boards-ardupilot.aadl		\
	$(srcdir)/boards-arduimu.aadl		\
	$(srcdir)/boards-cpiom.aadl		\
	$(srcdir)/boards-gr_cpci_x4cv.aadl	\
	$(srcdir)/boards-gr_xc3s_1500.aadl	\
	$(srcdir)/boards-sbc8349e.aadl		\
	$(srcdir)/boards-verdex_xm4.aadl	\
	$(srcdir)/buses.aadl			\
	$(srcdir)/buses-afdx.aadl		\
	$(srcdir)/buses-arinc_429.aadl		\
	$(srcdir)/buses-can.aadl		\
	$(srcdir)/buses-ethernet.aadl		\
	$(srcdir)/buses-i2c.aadl		\
	$(srcdir)/buses-mil1553.aadl		\
	$(srcdir)/buses-pci.aadl		\
	$(srcdir)/buses-spacewire.aadl		\
	$(srcdir)/buses-spi.aadl		\
	$(srcdir)/buses-uart.aadl		\
	$(srcdir)/buses-usb.aadl		\
	$(srcdir)/buses-vme.aadl		\
	$(srcdir)/devices-adxl.aadl		\
	$(srcdir)/devices-afdx.aadl		\
	$(srcdir)/devices-em406a.aadl   	\
	$(srcdir)/devices-lpr530al.aadl		\
	$(srcdir)/devices-ly530alh.aadl		\
	$(srcdir)/devices-hmc5843.aadl		\
	$(srcdir)/devices-mpxv7002dp.aadl	\
	$(srcdir)/devices-qre1113.aadl		\
	$(srcdir)/devices-resistances.aadl 	\
	$(srcdir)/devices-sn74ls157d.aadl 	\
	$(srcdir)/devices-spi.aadl 		\
	$(srcdir)/devices-thermistors.aadl 	\
	$(srcdir)/devices-thermopiles.aadl 	\
	$(srcdir)/devices-xyz_ir.aadl		\
	$(srcdir)/memories.aadl			\
	$(srcdir)/memories_vxworks.aadl		\
	$(srcdir)/os.aadl			\
	$(srcdir)/processors.aadl		\
	$(srcdir)/processors-arm.aadl		\
	$(srcdir)/processors-atmega.aadl	\
	$(srcdir)/processors-attiny.aadl	\
	$(srcdir)/processors-ppc.aadl		\
	$(srcdir)/processors-sparc.aadl		\
	$(srcdir)/processors-x86.aadl		\
	$(srcdir)/protocols.aadl		\
	$(srcdir)/shields.aadl			\
	$(srcdir)/shields-ardumoto.aadl		\
	$(srcdir)/shields-ardupilot.aadl	\
	$(srcdir)/shields-xbee.aadl		\
	$(srcdir)/systems.aadl			\
	$(srcdir)/unit.aadl

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/aadl -I$(top_srcdir)/src/property_set $${FILE};\
	done

clean-local:
	-rm *~

EXTRA_DIST= $(AADL_SOURCES)
