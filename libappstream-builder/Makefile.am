SUBDIRS = plugins

if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS =					\
	--add-include-path=$(srcdir)				\
	--add-include-path=$(top_builddir)/libappstream-glib
INTROSPECTION_COMPILER_ARGS =					\
	--includedir=$(srcdir)					\
	--includedir=$(top_builddir)/libappstream-glib

endif

AM_CPPFLAGS =							\
	$(GLIB_CFLAGS)						\
	$(GDKPIXBUF_CFLAGS)					\
	$(SOUP_CFLAGS)						\
	-I$(top_srcdir)/libappstream-glib			\
	-I$(top_builddir)/libappstream-glib			\
	-I.							\
	-DAS_COMPILATION					\
	-DTESTDATADIR=\""$(top_srcdir)/data/tests"\"		\
	-DASB_PLUGIN_DIR=\"$(libdir)/asb-plugins\"		\
	-DG_LOG_DOMAIN=\"Asb\"

AS_GLIB_LIBS =							\
	$(top_builddir)/libappstream-glib/libappstream-glib.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = 						\
	appstream-builder.pc

lib_LTLIBRARIES =						\
	libappstream-builder.la

libappstream_builder_includedir = $(includedir)/libappstream-builder
libappstream_builder_include_HEADERS =				\
	appstream-builder.h					\
	asb-app.h

libappstream_builder_la_SOURCES =				\
	asb-app.c						\
	asb-app.h						\
	asb-context.c						\
	asb-context.h						\
	asb-context-private.h					\
	asb-package.c						\
	asb-package-deb.c					\
	asb-package-deb.h					\
	asb-package.h						\
	asb-task.c						\
	asb-task.h						\
	asb-utils.c						\
	asb-utils.h						\
	asb-plugin.c						\
	asb-plugin.h						\
	asb-plugin-loader.c					\
	asb-plugin-loader.h

if HAVE_RPM
libappstream_builder_la_SOURCES +=				\
	asb-package-rpm.c					\
	asb-package-rpm.h
endif

libappstream_builder_la_LIBADD =				\
	$(AS_GLIB_LIBS)						\
	$(RPM_LIBS)						\
	$(GLIB_LIBS)

libappstream_builder_la_LDFLAGS =				\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)	\
	-export-dynamic						\
	-no-undefined						\
	-export-symbols-regex '^asb_.*'

libappstream_builder_la_CFLAGS =				\
	$(WARNINGFLAGS_C)

if HAVE_INTROSPECTION
introspection_sources =						\
	asb-app.c						\
	asb-app.h						\
	asb-context.c						\
	asb-context.h						\
	asb-context-private.h					\
	asb-package.c						\
	asb-package.h						\
	asb-task.c						\
	asb-task.h

AppStreamBuilder-1.0.gir: libappstream-builder.la
AppStreamBuilder_1_0_gir_INCLUDES =				\
	AppStreamGlib-1.0					\
	GdkPixbuf-2.0						\
	Gio-2.0							\
	GObject-2.0
AppStreamBuilder_1_0_gir_CFLAGS = $(AM_CPPFLAGS)
AppStreamBuilder_1_0_gir_SCANNERFLAGS = --identifier-prefix=Asb	\
				--symbol-prefix=asb_		\
				--warn-all			\
				--add-include-path=$(srcdir)
AppStreamBuilder_1_0_gir_EXPORT_PACKAGES = appstream-builder
AppStreamBuilder_1_0_gir_LIBS =					\
	$(AS_GLIB_LIBS)						\
	libappstream-builder.la					\
	archive
if HAVE_RPM
AppStreamBuilder_1_0_gir_LIBS +=				\
	rpmio 							\
	rpm
endif
AppStreamBuilder_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += AppStreamBuilder-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
endif

DISTCLEANFILES =						\
	*.log							\
	*.trs

EXTRA_DIST =							\
	appstream-builder.pc.in

clean-local:
	rm -f *~
	rm -f $(CLEANFILES)

-include $(top_srcdir)/git.mk