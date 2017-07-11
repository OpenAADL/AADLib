AADL_SOURCES = $(srcdir)/rap.aadl
AADL_ROOT    = rap.native

OTHER_FILES = $(srcdir)/ac_flight_data.adb				\
	$(srcdir)/mpd_tactical_display.ads				\
	$(srcdir)/ac_flight_data.ads $(srcdir)/radar_controller.adb	\
	$(srcdir)/builtin_test.adb $(srcdir)/radar_controller.ads	\
	$(srcdir)/builtin_test.ads $(srcdir)/rwr_control.adb		\
	$(srcdir)/computations.adb $(srcdir)/rwr_control.ads		\
	$(srcdir)/computations.ads $(srcdir)/rwr_threat_response.adb	\
	$(srcdir)/hotas.adb $(srcdir)/rwr_threat_response.ads		\
	$(srcdir)/hotas.ads $(srcdir)/steering.adb			\
	$(srcdir)/hud_display.adb $(srcdir)/steering.ads		\
	$(srcdir)/hud_display.ads $(srcdir)/target_designation.adb	\
	$(srcdir)/hw.adb $(srcdir)/target_designation.ads		\
	$(srcdir)/hw.ads $(srcdir)/target_tracking.adb			\
	$(srcdir)/keyset.adb $(srcdir)/target_tracking.ads		\
	$(srcdir)/keyset.ads $(srcdir)/weapon_release.adb		\
	$(srcdir)/mpd_status_display.adb $(srcdir)/weapon_release.ads	\
	$(srcdir)/mpd_status_display.ads				\
	$(srcdir)/weapon_selection.adb					\
	$(srcdir)/mpd_stores_display.adb				\
	$(srcdir)/weapon_selection.ads					\
	$(srcdir)/mpd_stores_display.ads				\
	$(srcdir)/weapon_trajectory.adb					\
	$(srcdir)/mpd_tactical_display.adb				\
	$(srcdir)/weapon_trajectory.ads


CLEANDIRS = rap_native
CLEANFILES =

include $(srcdir)//../Makefile.common

AVAILABLE_TARGETS= parse-aadl cheddar ada
