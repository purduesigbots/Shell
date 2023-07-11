################################################################################
######################### User configurable parameters #########################
# filename extensions
CEXTS:=c
ASMEXTS:=s S
CXXEXTS:=cpp c++ cc

# probably shouldn't modify these, but you may need them below
ROOT=.
FWDIR:=$(ROOT)/firmware
BINDIR=$(ROOT)/bin
SRCDIR=$(ROOT)/src
INCDIR=$(ROOT)/include

WARNFLAGS+=
EXTRA_CFLAGS= -I./tools/parser
EXTRA_CXXFLAGS= -I./tools/parser

# Set to 1 to enable hot/cold linking
USE_PACKAGE:=1

# Add libraries you do not wish to include in the cold image here
# EXCLUDE_COLD_LIBRARIES:= $(FWDIR)/your_library.a
EXCLUDE_COLD_LIBRARIES:= 

# Set this to 1 to add additional rules to compile your project as a PROS library template
IS_LIBRARY:=1
# TODO: CHANGE THIS! 
# Be sure that your header files are in the include directory inside of a folder with the
# same name as what you set LIBNAME to below.
LIBNAME:=libshell
VERSION:=0.0.1
# EXCLUDE_SRC_FROM_LIB= $(SRCDIR)/unpublishedfile.c
# this line excludes opcontrol.c and similar files
EXCLUDE_SRC_FROM_LIB+=$(foreach file, $(SRCDIR)/main,$(foreach cext,$(CEXTS),$(file).$(cext)) $(foreach cxxext,$(CXXEXTS),$(file).$(cxxext)))

# files that get distributed to every user (beyond your source archive) - add
# whatever files you want here. This line is configured to add all header files
# that are in the directory include/LIBNAME
TEMPLATE_FILES=$(INCDIR)/$(LIBNAME)/*.h $(INCDIR)/$(LIBNAME)/*.hpp

.DEFAULT_GOAL=quick  

# PROS on windows does not include bison or flex, so we need to provide our own in that case. 
FLEX := ./tools/parser/win_flex.exe
BISON := ./tools/parser/win_bison.exe

FLEX_FLAGS := 
BISON_FLAGS := 

# Define the d
PARSER_SRC_DIR=$(SRCDIR)/shell/parser
PARSER_INC_DIR=$(INCDIR)/shell/parser

CXXSRC:=$(PARSER_SRC_DIR)/parser.y.cpp
CXXSRC+=$(PARSER_SRC_DIR)/scanner.l.cpp

$(PARSER_SRC_DIR)/scanner.l.cpp: $(PARSER_SRC_DIR)/scanner.l $(PARSER_SRC_DIR)/parser.y.cpp
	$(FLEX) -o $@  $(FLEX_FLAGS) $<

$(PARSER_SRC_DIR)/parser.y.cpp: $(PARSER_SRC_DIR)/parser.y
	$(BISON) -o $@ --header=$(PARSER_INC_DIR)/parser.y.hpp $(BISON_FLAGS) $<

# Override PROS's clean rule so that we can remove the stale bison/flex files
clean:
	rm -f $(PARSER_SRC_DIR)/parser.y.cpp
	rm -f $(PARSER_SRC_DIR)/scanner.l.cpp
	rm -f $(PARSER_INC_DIR)/parser.y.hpp
	rm -f $(PARSER_INC_DIR)/scanner.l.hpp

	

################################################################################
################################################################################
########## Nothing below this line should be edited by typical users ###########
-include ./common.mk
