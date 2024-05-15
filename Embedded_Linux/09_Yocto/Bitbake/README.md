# Bitbake

## Introduction

**Bitbake** is a core component of the Yocto Project.It is a build tool used in the Yocto Project to `build embedded Linux distributions`. It's a powerful and flexible tool that `automates` the process of building software packages and images for embedded systems.


- [x] It basically performs the same functionality as of make.

- [x] It's a task scheduler that parses python and shell script mixed code

- [x] The code parsed generates and runs tasks, which are basically a set of steps ordered according to code's dependencies.

- [x] It reads recipes and follows them by fetching packages, building them and incorporating the results into bootable images.

- [x] It keeps track of all tasks being processed in order to ensure completion, maximizing the use of processing resources to reduce build time and being predictable.

### BitBake Command

- **BitBake** is invoked using the `bitbake` command.
- Common usage: `bitbake <recipe>` to build a specific recipe or `bitbake <image>` to build an image.
- BitBake manages `dependencies`, `fetches` source code, `executes` tasks, and `produces` build artifacts.

### BitBake-specific Variables

- **BBFILES**: List of recipe files.
- **BBPATH**: Path to search for recipe files.
- **DL_DIR**: Directory to store downloaded sources.
- **SSTATE_DIR**: Directory for the Shared State Cache.
- **TMPDIR**: Directory for temporary files.

