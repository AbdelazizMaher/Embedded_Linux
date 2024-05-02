SUMMARY = "Demon APP"
DESCRIPTION = "Recipe created by abdelaziz"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "git://github.com/FadyKhalil/EmbeddedLinux.git;protocol=https;branch=main"

S = "${WORKDIR}/git/InitApp/"

#SRCREV = "${AUTOREV}"
SRCREV = "e12715465721409b88745dd1c53571f3699e9afa"

inherit cmake


