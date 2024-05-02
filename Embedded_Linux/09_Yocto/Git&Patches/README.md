# Using Git in Yocto

`Git` is a powerful version control system used in Yocto Project for managing source code repositories. It allows `fetching source code` from remote repositories, `managing revisions`, and `applying patches`. Here's a guide on using Git effectively within Yocto:


## 1. Write a recipe for git remote repository


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

## 2. Patching the Source for a Recipe

In `Yocto`, everything is built from source, which provides flexibility in making changes to recipes. However, it's crucial to understand the proper way to apply changes to the source code. Let's discuss why directly modifying the source in the `"work directory"` is not recommended and how to `patch the source` effectively.

### The Work Directory

`Yocto` creates a directory known as the `"work directory"` where all the build processes occur. It's located at `tmp/work/<architecture>/<recipe>/<version>`. Within this directory, the source code resides in a subdirectory named `<recipename>-<version>` or `"git"` depending on the source fetch method.

### Why Direct Modification is Not Recommended

#### 1. Risk of Losing Changes
Making changes directly in the work directory poses a risk of losing modifications. For example, running `bitbake -c clean` can wipe out the directory, erasing your changes.

#### 2. Need for Forced Compilation
The build system doesn't automatically recognize changes made directly in the work directory. You have to force compilation using:
```bash
bitbake -c compile <recipe> -f
```

### Creating and Applying Patches in Yocto

Patches play a crucial role in customizing third-party source code within Yocto. They allow you to make modifications to the codebase while maintaining the original source intact. Here's a guide on creating and applying patches using Git:

> If you download the third-party source code as a Git repository, this is definitely the easiest solution

>> After downloading the repository, make the required changes to the code, and add these changes to the repository as a new commit

>>> You can then tell Git to make a patch file.

### Creating Patches

1 .**Make Changes and Commit**:

Navigate to the cloned repository and make the required changes to the code. Once done, add and commit your changes:

```bash
git add .
git commit -m "Description of changes"
```

2. **Generate the Patch File**:

If all changes are contained within a single additional commit, you can generate a patch file using:

```bash
git show HEAD > my-patch.patch
```
This command creates a patch file named my-patch.patch containing the changes introduced in the latest commit.


