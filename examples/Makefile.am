SUBDIRS= adiru aocs aram ardupilot arinc653_annex asl behavior_annex	\
	  car data_modeling_annex fcs flow_analysis fms isr		\
	  line_follower mixin memory mosart multicore			\
	  pathfinder_system perseus producer_consumer ravenscar radar	\
	  rap redundancy rma robot round_robin time_triggered units	\
	  uxv voter satellite

EXTRA_DIST=$(srcdir)/Makefile.common

SAMPLE_DIR = ${shell $(CYGPATH_U) '$(OCARINA_PREFIX)/examples/ocarina/aadlib'}

install-data-local:
	$(INSTALL) -d $(DESTDIR)$(SAMPLE_DIR)

uninstall-local:
	rm -rf $(DESTDIR)$(SAMPLE_DIR)

clean-local:
	-rm -rf *~
