# This Source Code Form is licensed MPL-2.0: http://mozilla.org/MPL/2.0
include $(wildcard $>/drivers/*.d)
CLEANDIRS += $(wildcard $>/drivers/)
drivers/rpath..libbse ::= ../lib
