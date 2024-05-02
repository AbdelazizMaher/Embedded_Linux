FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI:append = " file://0001-maintain-cmake-version-and-delete-c-compiler.patch \
                   file://hellodaemonAPP.service "
                   
                   
inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "hellodaemonAPP.service"


do_install:append() {
	install -d ${D}/${sysconfdir}/systemd/system
	install -m 0775 ${WORKDIR}/hellodaemonAPP.service ${D}/${sysconfdir}/systemd/system
}                   
