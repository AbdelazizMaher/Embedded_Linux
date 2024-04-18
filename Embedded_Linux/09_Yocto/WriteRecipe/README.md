# Writing a Recipe



### Step 1: Create a file `hello.c` with the your content:

```c
#include <stdio.h>

int main()
{
	printf(" Hello , my first layer\n");
	printf(" Hello , my first layer\n"); 
	printf(" Hello , my first layer\n"); 

	return 0;
}	
```

### Step 2: Create a folder in the layer recipes-example 'hello'

```bash
mkdir -p recipes-examples/hello
```

### Step 3: Create 'files' folder inside the 'hello' folder and copy hello.c inside this folder

```bash
# Copy the hello.c into the below location
mkdir -p recipes-examples/hello/files
```

### Step 4: Create a file called 'hello_0.1.bb' with the following content:

```bash
SUMMARY = "Simple print hello recipe"
DESCRIPTION = "Recipe created by abdelaziz"

# Your recipe needs to have both the LICENSE and LIC_FILES_CHKSUM variables
# This variable specifies the license for the software.
LICENSE = "MIT"
# The OpenEmbedded build system uses this variable to make sure the license text has not changed
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
```

> **`Notes`** 

>> `Recipe File Format: `<base_name>_<version>.bb`
>>> Use lower-cased characters and do not include the reserved suffixes `-native`, `-cross`, `-initial`, or `-dev`

> `For standard licenses`, use the names of the files in meta/files/common-licenses/

>> `install keyword` not only copies files but also changes its ownership and permissions and optionally removes debugging symbols from executables.It combines cp with chown, chmod and strip


### Step 5: Execute the recipe

```bash 
bitbake myhello
```

### Recipe Explanation

The most relevant tasks that will be executed when calling bitbake hello are the following:

#### 1. do_fetch: 

In this case, since the specified `SRC_URI` variable points to a `local file`, BitBake will simply copy the file in the recipe `WORKDIR`. 
This is why the `S` environment variable `(which represents the source code location)` is set to `WORKDIR`.

	
#### 2. do_compile: 

when executing this task, BB will invoke the `C cross-compiler` for compiling the `hello.c` source file. 
> :white_check_mark: The results of the compilation will be in the folder pointed by the `B` environment variable `(that, in most of the cases, is the same as the S folder)`.

#### 3. do_install: 

This task specifies where the hello binary should be installed into the `rootfs`. 
It must be noticed that this installation will only happen within a `temporary rootfs folder within the recipe WORKDIR` (pointed by the variable `D`)

#### 4. do_package: 

In this phase the file installed in the directory `D` will be packaged in a package named `hello`. 
This package will be used later from BitBake when eventually `building a rootfs image containing the hello recipe` package

> `packages`: The extracted contents of packages are stored here
 
>`packages-split`: The contents of packages, extracted and split, are stored here. This has a sub-directory for each package
	

### Tasks

Yocto/OpenEmbedded's build tool `bitbake` parses a recipe and generates list of tasks that it can execute to perform the build steps

**The most important tasks are:**

| Task                 | Description                                                                     |
|----------------------|---------------------------------------------------------------------------------|
| do_fetch             | Fetches the source code.                                                        |
| do_unpack            | Unpacks the source code into a working directory.                                |
| do_patch             | Locates patch files and applies them to the source code.                         |
| do_configure         | Configures the source by enabling and disabling build-time and configuration options. |
| do_compile           | Compiles the source in the compilation directory.                                |
| do_install           | Copies files from the compilation directory to a holding area.                   |
| do_package           | Analyzes the content of the holding area and splits it into subsets based on available packages and files. |
| do_package_write_rpm | Creates the actual RPM packages and places them in the Package Feed area.        |


> Generally, the only tasks that the user needs to specify in a recipe are `do_configure` , `do_compile` and `do_install` 
 
>> The remaining tasks are automatically defined by the YP build system

>> The above task list is in the correct `dependency order`. They are executed from `top to bottom`.


#### You can use the `-c` argument to execute the `specific task` of a recipe.

```bash
bitbake -c compile <recipe>
```

#### To list all tasks of a particular recipe:

```bash
bitbake <recipe name> -c listtasks
```

### Tasks Explanation

> :exclamation: **`Note`** classes/base.bbclass contains definitions for standard basic tasks such as `fetching`, `unpacking`, `configuring` (empty by default), `compiling` (runs any Makefile present), `installing` (empty by default) and `packaging` (empty by default)

#### Stage 1: Fetching Code (do_fetch)

- The first thing your recipe must do is specify how to fetch the source files.

> :grey_exclamation: `Fetching` is controlled mainly through the `SRC_URI` variable

- Your recipe must have a `SRC_URI` variable that points to where the source is located.

- The `SRC_URI` variable in your recipe must define each `unique location` for your source files.

- Bitbake supports fetching source code from `git`, `svn`, `https`, `ftp`, etc

> URI scheme syntax: scheme://url;param1;param2

- Scheme can describe a local file using `file://` or remote locations with `https://, git://, svn://, hg://, ftp://`

> By default, sources are fetched in $BUILDDIR/downloads



#### Stage 2: Unpacking (do_unpack)

- All local files found in `SRC_URI` are copied into the recipe’s working directory, in `$BUILDDIR/tmp/work/`

> :exclamation: If the directory has another name, you must explicitly define S

- If you are fetching from SCM like `git or SVN`, or your file is local to your machine, you need to define `S`

- If the scheme is `git`, `S = ${WORKDIR}/git`
  

#### Stage 3: Patching Code (do_patch)

- Sometimes it is necessary to patch code after it has been fetched.

- Any files mentioned in `SRC_URI` whose names end in `.patch or .diff` or compressed versions of these suffixes (e.g. diff.gz) are treated as `patches`

> :white_check_mark: The do_patch task automatically applies these patches.

- The build system should be able to apply patches with the "-p1" option (i.e. one directory level in the path will be stripped off).
 

####  Stage 4: Configuration (do_configure)

- Most software provides some means of `setting build-time configuration` options before compilation

> :grey_exclamation: Typically, setting these options is accomplished by `running a configure script` with options, or by modifying a build configuration file


####  Stage 5: Compilation (do_compile)

- do_compile task happens after `source is fetched, unpacked, and configured`.
  

#### Stage 6: Installation (do_install)

- After compilation completes, BitBake executes the do_install task

- During do_install, the task copies the `built files along with their hierarchy` to locations that would `mirror their locations on the target` device.
  

#### Stage 7: Packaging (do_package)

- The do_package task splits the files produced by the recipe into logical components.

> :grey_exclamation: The do_package task ensures that files are split up and packaged correctly.



