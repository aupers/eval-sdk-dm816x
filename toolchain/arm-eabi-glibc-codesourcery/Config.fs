#
# Ridgerun BSP Configuration file for toolchain
# all definitions on this subtree must prefix with TOOLCHAIN_
#

comment "Toolchain file system components"

config TOOLCHAIN_INSTALL_CPP_SUPPORT
	bool "Install C++ (libstdc++) support on target file system"
	default n
	help
	    Enable this option will make the toolchain to install the
	    standard C++ library into the file system adding around 
	    3.6MB to your target.

config TOOLCHAIN_INSTALL_GCONV_MODULES
	bool "Install GCONV Conversion modules on target file system"
	default n
	help
	    Enable if using toolchain's iconv conversion support.
	    
comment "Toolchain provided applications"
config TOOLCHAIN_INSTALL_GDBSERVER
	bool "Install GDB server on target file system"
	default n
	help
	    Enable this option will make the toolchain to install the
	    gdbserver on the target file system. This allow to remotely
	    debug applications on the board

config TOOLCHAIN_INSTALL_LDD
	bool "Install ldd on target file system"
	default n
	help
	    Enable this option will make the toolchain to install ldd
	    on the target file system.


