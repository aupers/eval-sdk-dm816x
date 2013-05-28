include $(DEVDIR)/bsp/mach/bspconfig
export RRSDK_PREPATCH_TARGETS=audio_codecs_checked
export RRSDK_POSTUNPATCH_TARGETS=cleanup_audio_codecs

ifeq ($(CONFIG_PROPRIETARY_EXTERNAL_AUDIO_CODECS_SUPPORT),y)
ifeq ($(CONFIG_PROPRIETARY_TI_CODECENGINE_DM8168),y)
DSP_FIRMWARE=ezsdk/component-sources/omx_05_02_00_48/bin/dm81xx/bin/ti816x-evm/dm81xx_c6xdsp_debug.xe674
endif

ifeq ($(CONFIG_PROPRIETARY_TI_CODECENGINE_DM8148),y)
DSP_FIRMWARE=ezsdk/component-sources/omx_05_02_00_48/bin/dm81xx/bin/ti814x-evm/dm81xx_c6xdsp_debug.xe674
endif
endif

default_rule: build
audio_codecs_checked:
	$(V) if [ -d ezsdk/component-sources/c674x_aaclcenc_01_00_01_00_elf -a -d ezsdk/component-sources/c674x_mp3dec_01_41_00_00_elf ] ; then \
	     $(ECHO) "  Detected external AAC and MP3 audio codecs, adding support for them." ; \
	     patch -p1 < patches/arch/integrate-aaclenc.patch ; \
	     patch -p1 < patches/arch/integrate-mp3dec.patch ; \
	 fi
	$(V)touch $@

cleanup_audio_codecs:
	$(V) if [ -d ezsdk/component-sources/c674x_aaclcenc_01_00_01_00_elf -a -d ezsdk/component-sources/c674x_mp3dec_01_41_00_00_elf ] ; then \
	        if [ -f audio_codecs_checked ] ; then \
	           patch -R -p1 < patches/arch/integrate-mp3dec.patch ; \
	           patch -R -p1 < patches/arch/integrate-aaclenc.patch ; \
	        fi; \
	 fi
	$(V)rm -rf audio_codecs_checked

