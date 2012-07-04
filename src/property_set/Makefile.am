AADL_SOURCES= $(srcdir)/arinc653.aadl					\
	$(srcdir)/behavior_properties.aadl				\
	$(srcdir)/bus_properties.aadl					\
	$(srcdir)/cheddar_properties.aadl $(srcdir)/data_sheet.aadl	\
	$(srcdir)/deployment.aadl					\
	$(srcdir)/electricity_properties.aadl				\
	$(srcdir)/os_properties.aadl					\
	$(srcdir)/physical_properties.aadl $(srcdir)/pok.aadl		\
	$(srcdir)/processor_properties.aadl

EXTRA_DIST= $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/property_set $${FILE};\
	done

clean-local:
	-rm *~
