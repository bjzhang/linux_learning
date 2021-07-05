################################################################################
#
# cmake test
#
################################################################################

CMAKE_TEST_VERSION = devel
CMAKE_TEST_SITE = ${BR2_EXTERNAL_CMAKE_TEST_PATH}/..
CMAKE_TEST_SITE_METHOD = local
CMAKE_TEST_LICENSE = GPL-2.0+
CMAKE_TEST_LICENSE_FILES = Copyright COPYING

$(eval $(cmake-package))

