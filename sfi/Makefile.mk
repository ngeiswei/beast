# This Source Code Form is licensed MPL-2.0: http://mozilla.org/MPL/2.0
include $(wildcard $>/sfi/*.d)
CLEANDIRS += $(wildcard $>/sfi/)


# == sfidl ==
sfi/sfidl	  ::= $>/sfi/sfidl
ALL_TARGETS	   += $(sfi/sfidl)
sfi/sfidl.sources ::= sfi/sfidl.cc
sfi/sfidl.objects ::= $(sort $(sfi/sfidl.sources:%.cc=$>/%.o))
$(sfi/sfidl.objects):	| $>/sfi/
$(sfi/sfidl.objects): EXTRA_DEFS ::= -DG_LOG_DOMAIN=\"SFI\" -DG_DISABLE_CONST_RETURNS -DPARANOID -DSFIDL_INTERNALS
$(sfi/sfidl.objects): EXTRA_INCLUDES ::= $(GLIB_CFLAGS)
sfi/sfidl.cc.FLAGS  = -O0
$(eval $(call LINKER, $(sfi/sfidl), $(sfi/sfidl.objects), , $(GLIB_LIBS)))

# == testsfidl ==
sfi/testsfidl		::= $>/sfi/testsfidl
ALL_TARGETS	   	 += $(sfi/testsfidl)
sfi/testsfidl.sources	  = sfi/testsfidl.cc
sfi/testsfidl.objects	  = $(sort $(sfi/testsfidl.sources:%.cc=$>/%.o))
$(sfi/testsfidl.objects): EXTRA_INCLUDES ::= -I$> $(GLIB_CFLAGS)
sfi/testsfidl.cc.FLAGS	  = -O0
$(eval $(call LINKER, $(sfi/testsfidl), $(sfi/testsfidl.objects), , $(GLIB_LIBS)))
sfi-check: FORCE	| $(sfi/testsfidl)
	$(QECHO) RUN $@
	$Q $(sfi/testsfidl)
check: sfi-check
