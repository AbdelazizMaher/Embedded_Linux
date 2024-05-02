SUMMARY = "Simple print hello recipe"
DESCRIPTION = "Recipe created by abdelaziz"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://hello.c"

S = "${WORKDIR}"


do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} hello.c -o hello
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${S}/hello  ${D}${bindir}/
}

