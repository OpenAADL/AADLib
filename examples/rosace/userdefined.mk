USER_CFLAGS=-I$(srcdir)./../../common/
USER_LDFLAGS=-lm -g

ifeq ($(RTEMS_API),4.11)
USER_CFLAGS += -msoft-float
endif
