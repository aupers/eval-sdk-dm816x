# plugindir is set in configure

plugin_LTLIBRARIES = libgstrrparser.la

# sources used to compile this plug-in
libgstrrparser_la_SOURCES = gstrrparser.c gstrrparser.h

# flags used to compile this plugin
# add other _CFLAGS and _LIBS as needed
libgstrrparser_la_CFLAGS = $(GST_CFLAGS)
libgstrrparser_la_LIBADD = $(GST_LIBS) $(GST_BASE_LIBS) $(GSTCTRL_LIBS)
libgstrrparser_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstrrparser_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstrrparser.h
