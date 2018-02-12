TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    source \
    Tests

Tests.depends = source
