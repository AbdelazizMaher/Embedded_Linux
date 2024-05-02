## Extending a Recipe

In Yocto, it's considered good practice not to modify recipes directly from the Poky layer. However, there are situations where modifying an existing recipe is necessary. Two common approaches for this are:

### Copy Approach
- Copy the recipe into your own layer.
- Make modifications directly in the copied recipe.

### Extend Approach
- Utilize BitBake's capability to modify a recipe by extending it.

## What is BitBake Append?

A recipe that appends metadata to another recipe is known as a BitBake append file. These files have the extension `.bbappend`. The `.bbappend` file resides in your layer and is used to make additions or changes to the content of another layer's recipe, without needing to copy the original recipe.

### Advantages of Using .bbappend Files:
- Avoids the need to copy entire recipes into your layer.
- Simplifies maintenance and updates.
- Allows for better organization and modularity.

## How to Use .bbappend Files

1. **Create a .bbappend File**:
   - Create a `.bbappend` file in your layer with the same name as the recipe you want to extend, but with the `.bbappend` extension.

2. **Specify Modifications**:
   - Within the `.bbappend` file, specify the changes or additions you want to make to the original recipe.

3. **File Structure**:
   - Your `.bbappend` file resides in your layer.
   - The `.bb` recipe file you are extending resides in a different layer.

### Example .bbappend File

Let's say you want to modify the recipe `example_recipe` from the `poky` layer. Your `.bbappend` file, named `example_recipe_%.bbappend`, would look like this:
```plaintext
meta-yourlayer/
└── recipes-custom
└── example-recipe
└── example_recipe_%.bbappend
```

## Benefits of .bbappend

When working with Yocto recipes, using `.bbappend` files has several benefits:

- **Avoids Manual Merging**: If you were copying recipes, you would have to manually merge changes as they occur.

- **Avoids Duplication**: Using `.bbappend` files avoids duplication of recipes.

- **Automatically Applies Changes**: `.bbappend` files automatically apply recipe changes from a different layer into your layer.

## Points to Consider while Working with .bbappend

1. **Matching Root Names**:
   - Appended files must have the same root name as the recipe they extend.
     - *Example*: `example_0.1.bbappend` applies to `example_0.1.bb`.
   - This means the original recipe and append file names are version number-specific.
   - If the corresponding recipe is renamed to update to a newer version, you must also rename and possibly update the corresponding `.bbappend` as well.
   - During the build process, BitBake displays an error on starting if it detects a `.bbappend` file that does not have a corresponding recipe with a matching name.

2. **Prepending FILESEXTRAPATHS**:
   - If adding new files, you must prepend the `FILESEXTRAPATHS` variable with the path to the files’ directory.


## Prioritizing Your Layer

In Yocto, each layer is assigned a priority value, which controls the precedence of recipes and `.bbappend` files from different layers. Here's how it works:

- **Priority for Recipes**:
  - When multiple layers contain recipe files with the same name, the recipe from the layer with a higher priority number takes precedence.
  - Priority values determine which layer's recipes are used during the build process.

- **Priority for .bbappend Files**:
  - Priority values also affect the order in which multiple `.bbappend` files for the same recipe are applied.
  - `.bbappend` files from layers with higher priority are applied before those from layers with lower priority.

### Setting Layer Priority

To specify the priority of your layer manually, use the `BBFILE_PRIORITY` variable followed by the root name of your layer:

```bash
BBFILE_PRIORITY_mylayer = "1"
```
> the layer priority does not currently affect the precedence order of .conf or .bbclass files.



## Understanding File Searching Paths

In Yocto, when a file (such as a patch or a generic file) is included in `SRC_URI`, BitBake searches for the file using the `FILESPATH` and `FILESEXTRAPATHS` variables. Here's how it works:

### FILESPATH

The `FILESPATH` variable defines the search path for files. The default value is defined in the `base.bbclass` class found in `meta/classes`.

```bash
FILESPATH = "${@base_set_filespath(["${FILE_DIRNAME}/${BP}", "${FILE_DIRNAME}/${BPN}", "${FILE_DIRNAME}/files"], d)}"
```

. It is a colon-separated list of directories searched left-to-right in order.
. Default locations include:
	- `<recipe>-<version>`
	- `<recipe>`
	- `<files>`

```bash
bitbake -e myhello | grep ^FILESPATH=
```

>  Avoid hand-editing the `FILESPATH` variable.


## FILESEXTRAPATHS

`FILESEXTRAPATHS` extends the search path used by the OpenEmbedded build system when looking for files and patches as it processes recipes and append files.

### Description

- It extends the search path to include additional directories.
- This allows BitBake to find necessary files and patches.

### Usage

```bash
FILESEXTRAPATHS_prepend := "${THISDIR}:"
```

`THISDIR`: The directory where the file BitBake is currently parsing is located.
> Best practices suggest using FILESEXTRAPATHS from within a .bbappend file.
    
Prepend paths as follows:

```bash
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
```
> Here, ${PN} represents the recipe name.



                    

