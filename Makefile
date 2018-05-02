PROJECT_NAME = ndrte

RDIRS += compdeps
RDIRS += archdeps
RDIRS += datastructs
RDIRS += drivers

RDIRS += test

include $(CURDIR)/ndr-build-env/ndr.mkroot.mk
