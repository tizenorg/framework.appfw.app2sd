CC ?= gcc

TARGETS = utc_ApplicationFW_app2ext_init_func\
	utc_ApplicationFW_app2ext_deinit_func\
	utc_ApplicationFW_app3ext_get_app_location\
	utc_ApplicationFW_app2ext_pre_install_func\
	utc_ApplicationFW_app2ext_post_install_func\
	utc_ApplicationFW_app2ext_pre_upgrade_func\
	utc_ApplicationFW_app2ext_post_upgrade_func\
	utc_ApplicationFW_app2ext_pre_uninstall_func\
	utc_ApplicationFW_app2ext_post_uninstall_func\
	utc_ApplicationFW_app2ext_move_func

PKGS = app2sd glib-2.0

LDFLAGS = `pkg-config --libs $(PKGS)`
LDFLAGS += $(TET_ROOT)/lib/tet3/tcm_s.o
LDFLAGS += -L$(TET_ROOT)/lib/tet3 -ltcm_s
LDFLAGS += -L$(TET_ROOT)/lib/tet3 -lapi_s

CFLAGS = -I. `pkg-config --cflags $(PKGS)`
CFLAGS += -I$(TET_ROOT)/inc/tet3
CFLAGS += -Wall

all: $(TARGETS)

$(TARGETS): %: %.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGETS)
