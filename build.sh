#!/bin/bash

# Variables
SRC_DIR="./src"
INCLUDE_DIR="./include"
LIB_DIR="./lib"
OUT_DIR="./bin"
CC="gcc"
CFLAGS="-Wall -Wextra -pedantic -I$INCLUDE_DIR -L$LIB_DIR -l:libraylib.a -lm"  # -Wall for warnings, -g for debugging
TARGET="$OUT_DIR/udrebmg"

# Create output directory if it doesn't exist
mkdir -p $OUT_DIR

# Compile each .c file in the src directory
echo "Compiling source files..."
FILES="$SRC_DIR/main.c"
for h_file in $SRC_DIR/*.h; do
    c_file="${h_file%.h}.c"
    obj_file="${h_file%.h}.o"
    echo "Compiling $h_file -> $obj_file"
    $CC -c $h_file $c_file $CFLAGS
    FILES="$FILES $obj_file"
done

mv *.o $SRC_DIR

# Link object files into the final executable
echo "Linking object files..."
$CC $FILES -o $TARGET $CFLAGS

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Executable created: $TARGET"
else
    echo "Build failed."
    exit 1
fi

# Run the program if the build succeeded
echo "Running the program..."
./$TARGET
