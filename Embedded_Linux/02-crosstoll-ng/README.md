# CrossTool-NG Configuration

## Introduction

This README provides a brief overview and instructions for configuring CrossTool-NG, a powerful cross-compilation toolchain generator. CrossTool-NG allows you to build a custom toolchain for your embedded system development needs.

## Installation

To install CrossTool-NG, follow these steps:

### 1. Clone the CrossTool-NG repository from GitHub:
    git clone https://github.com/crosstool-ng/crosstool-ng	
    
### 2. Navigate to the CrossTool-NG directory:
    cd crosstool-ng

### 3. Install Dependencies:
    sudo apt install -y gcc g++ gperf bison flex texinfo help2man make libncurses5-dev python3-dev autoconf automake libtool-bin gawk wget bzip2 xz-utils unzip patch libstdc++6 rsync
    
### 3. Configure and compile CrossTool-NG:
    ./bootstrap                          ===>> To setup the environment
    ./configure --enable-local           ===>> To check all dependency
    make                                 ===>> To generate the Makefile for croostool-ng

## Configuration

Follow these steps to configure CrossTool-NG:

### 1. List default configured Toolchains for supproted architecture:
    /ct-ng list-samples                   ===>> To list all microcontrollers supported


### 2. Choose toolchain for required architecture:
    ./ct-ng [microcontroller]             ===>> To configure the microcontroller used    

### 2. Initialize the CrossTool-NG configuration to change in the default configuration:
    ct-ng menuconfig                      ===>> To configure toolchain

## Building the Toolchain

### Once you've configured CrossTool-NG, you can build the toolchain by running:
    ct-ng build

## Usage

After the build process completes successfully, you can find your custom toolchain in the directory specified during configuration (usually ~/x-tools by default). Use this toolchain with your embedded development projects to cross-compile your code for your target platform.

## Test the generated toolchain for avr

## 1. write source code: 
    vim main.c
    
## 2. add toolchain to PATH environment variable:     
    export PATH=${PATH}:~/x-tools/avr/bin

## 3. add toolchain to PATH environment variable: 
  **Note:** Specify the hardware using -mmcu= 
  
    avr-gcc main.c -mmcu=atmega32a -O1 -o main





    


    
