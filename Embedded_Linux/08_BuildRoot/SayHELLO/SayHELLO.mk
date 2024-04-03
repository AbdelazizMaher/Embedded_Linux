################################################################################
#
# Say-Hello-APP package
#
################################################################################

SAYHELLO_VERSION := 1.0.0
SAYHELLO_SITE := package/SayHELLO/APP
SAYHELLO_SITE_METHOD := local
SAYHELLO_INSTALL_TARGET := YES

define SAYHELLO_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define SAYHELLO_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/SayHelloAPP $(TARGET_DIR)/usr/bin/SayHelloAPP
endef

define SAYHELLO_PERMISSIONS
	/usr/bin/SayHelloAPP f 4755 0 0 - - - - -
endef

$(eval $(generic-package))
