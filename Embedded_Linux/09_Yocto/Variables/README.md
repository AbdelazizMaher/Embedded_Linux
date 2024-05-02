OpenEmbedded Variables
----------------------

S : Contains the unpacked source files for a given recipe

D : The destination directory (root directory of where the files are installed, before creating the image)

WORKDIR: The location where the OpenEmbedded build system builds a recipe (i.e. does the work to create the package).

PN : The name of the recipe used to build the package

PV : The version of the recipe used to build the package

PR : The revision of the recipe used to build the package.


WORKDIR
--------------

The location of the work directory in which the OpenEmbedded build system builds a recipe.

This directory is located within the TMPDIR directory structure and is specific to the recipe being built and the system for which it is being built.

The WORKDIR directory is defined as follows:

${TMPDIR}/work/${MULTIMACH_TARGET_SYS}/${PN}/${EXTENDPE}${PV}-${PR}

TMPDIR: The top-level build output directory
MULTIMACH_TARGET_SYS: The target system identifier
PN: The recipe name
EXTENDPE: Mostly blank
PV: The recipe version
PR: The recipe revision
