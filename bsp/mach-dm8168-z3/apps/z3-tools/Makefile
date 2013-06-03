include $(DEVDIR)/bsp/classes/rrsdk.class

DEVMEM2=devmem2
EDID=edid
Z3_TARGETS=init_video_capture

ifeq ($(CONFIG_USER_APPS_DEVMEM2),y)
Z3_TARGETS+=devmem2
endif

ifeq ($(CONFIG_USER_APPS_EDID),y)
Z3_TARGETS+=edid
endif

build:
ifneq ($(Z3_TARGETS),)
	$(V) $(MAKE) $(Z3_TARGETS:=_built) $(QOUT) $(ERRQOUT)
endif

install:
	$(V) $(MAKE) $(Z3_TARGETS:=_install)

clean:
	$(V) $(MAKE) $(Z3_TARGETS:=_clean)
#========================================================================================
# DEVMEM2
#========================================================================================
devmem2_built:
	$(V) $(MAKE) -C $(DEVMEM2)

devmem2_install:
	$(V) $(MAKE) -C $(DEVMEM2) install

devmem2_clean:
	$(V) $(MAKE) -C $(DEVMEM2) clean
	$(V) rm -rf devmem2_built

#========================================================================================
# EDID
#========================================================================================
edid_built:
	$(V) $(MAKE) -C $(EDID)

edid_install:
	$(V) $(MAKE) -C $(EDID) install

edid_clean:
	$(V) $(MAKE) -C $(EDID) clean
	$(V) rm -rf edid_built

#========================================================================================
# INIT VIDEO CAPTURE
#========================================================================================
init_video_capture_built:

init_video_capture_install:
	$(V) install -m 777 init_7611_edid.sh $(FSROOT)

init_video_capture_clean:
