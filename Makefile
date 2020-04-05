#################################################
# Top level makefile
#
# The macros defined by modsource harness:
#   o PUBLISH_DIR: All the files copied here will be published as deliverables
#   o BUILD_TYPE: The objtype (obj, release, beta, or opt). Defaults to release.
#   o CHANGE_NUMBER: the source tree changenumber
#   o BUILD_NUMBER: the build number.
#################################################

##########################
ARCHES  := i386
NAME    := syslinux
VERSION := 3
##########################

ifeq ($(OS), Windows_NT)
$(error building on $(OS) is not supported.)
endif

BUILD_NUMBER ?= 0
CHANGE_NUMBER ?= 0
BUILD_TYPE ?= release
RELEASE := $(CHANGE_NUMBER).vmw
DELIVERABLE_PREFIX := $(NAME)-$(VERSION)-$(RELEASE)

SRCROOT := $(shell pwd)
VMWAREROOT := $(SRCROOT)/src/vmware

BUILDROOT := $(SRCROOT)/buildroot
TMPROOT := $(BUILDROOT)/tmproot
INSTALLROOT := $(BUILDROOT)/install

PUBLISH_DIR ?= $(BUILDROOT)/stage_dir


CC := /build/toolchain/lin32/gcc-4.1.2-7/bin/i686-linux-gcc
NASM := /build/toolchain/lin32/nasm-0.98.39/bin/nasm

modsource: $(PHONY) all

all: $(PHONY) prep source build

prep: $(PHONY) clean
	mkdir -p $(BUILDROOT)
	mkdir -p $(PUBLISH_DIR)
	mkdir -p $(TMPROOT)

source: $(PHONY) prep
	@echo "******* Packaging oss.tgz file *******"
	mkdir -p $(TMPROOT)/$(NAME)-$(VERSION)
	cd $(VMWAREROOT) && tar -czvf $(TMPROOT)/$(NAME)-$(VERSION)/$(DELIVERABLE_PREFIX).src.tgz *
	cd $(TMPROOT) && tar -czvf $(PUBLISH_DIR)/$(DELIVERABLE_PREFIX).oss.tgz \
	   $(NAME)-$(VERSION)

build: $(PHONY) prep $(foreach ARCH,$(ARCHES),build-$(ARCH))

build-%: $(PHONY)
	@echo "******* Building $* *******"
	mkdir -p $(INSTALLROOT)/$*
	cd $(VMWAREROOT) && $(MAKE) NASM=$(NASM) CC=$(CC) INSTALLROOT=$(INSTALLROOT)/$* VMWARE=1
	cd $(VMWAREROOT) && $(MAKE) NASM=$(NASM) CC=$(CC) INSTALLROOT=$(INSTALLROOT)/$* VMWARE=1 install
	cd $(INSTALLROOT)/$* && tar -czvf $(PUBLISH_DIR)/$(DELIVERABLE_PREFIX).$*.tgz *

clean: $(PHONY)
	rm -rf  $(BUILDROOT)
