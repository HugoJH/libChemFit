TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    Tests \
    source

Tests.depends = source
