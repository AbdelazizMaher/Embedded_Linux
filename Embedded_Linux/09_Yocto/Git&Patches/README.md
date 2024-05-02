# Using Git in Yocto

`Git` is a powerful version control system used in Yocto Project for managing source code repositories. It allows `fetching source code` from remote repositories, `managing revisions`, and `applying patches`. Here's a guide on using Git effectively within Yocto:


## Write a recipe for git remote repository


- `Yocto` supports the ability to pull code from online git repositories as part of the build process.

#### Step 1: Set SRC_URI

```bash
SRC_URI = "git://<URL>;protocol=https"
```

#### Step 2: Set S environmental variable

```bash
S = ${WORKDIR}/git
```

#### Step 3: Set SRCREV environmental variable 

> :grey_exclamation: What is the use of `SRCREV`?
>> When fetching a repository, bitbake uses `SRCREV` variable to determine the `specific revision` from which to build.

**There are two options to this variable:**

1. **`AUTOREV`**:

```bash
SRCREV = "${AUTOREV}"
```

> :white_check_mark: When `SRCREV` is set to the value of this variable, it specifies to use the latest source revision in the repository

>> The build system accesses the network in an attempt to determine the latest version of software from the SCM

2. **`A specific revision (SHA1 hash when fetching from git)`**

> :white_check_mark: If you want to build a fixed revision and you want to avoid performing a query on the remote repository every time BitBake parses your recipe

```bash
SRCREV = "e12715465721409b88745dd1c53571f3699e9afa"
```


### Specifying a different branch


You can specify the branch using the following form:

```bash
SRC_URI = "git://server.name/repository;branch=branchname"
```

> :grey_exclamation: If you do not specify a branch, BitBake looks in the default "master" branch.
>> BitBake will now validate the SRCREV value against the branch.



## Patching the source for a recipe


Advantage of Yocto is that everything is build from source

It's fairly easy to make changes to anything that gets built

As part of building a recipe, OE creates a tmp/work/<architecture>/<recipe>/<version> directory, known as the "work directory". 

This is where all of the work done to build a recipe takes place.

A subdirectory contains the source of the recipe named <recipename>-<version> or "git" (depending on how the fetched source is provided)

The temptation is to simply make changes here and then recompile, but there are several reasons why that's not a good idea:

1.You can easily lose your changes if you're not careful e.g. running bitbake -c clean will wipe the directory out

2. You have to force compilation as the build system doesn't know that you've made any changes

bitbake -c compile <recipe> -f


Patches
---------------

Patches can be easily created using Git

If you download the third-party source code as a Git repository, this is definitely the easiest solution

After downloading the repository, make the required changes to the code, and add these changes to the repository as a new commit

You can then tell Git to make a patch file.

If all the changes are contained within a single additional commit, you can use the following command:

~$ git show HEAD > my-patch.patch

These generated patches should be bundled with your recipe files.

Patches should always be in a sub-directory of where the recipe lives.

Yocto will automatically apply these patches when it needs to build your recipe.



