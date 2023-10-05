#For Linux OS, compiles and links all the source files in the src directory
#creates an executable file called Risk_Game in the current directory

#!/bin/bash

# Set the compiler and flags
COMPILER="g++"
CFLAGS="-c -Wall"
LFLAGS="-o Risk_Game"

# Create an array of object files
OBJFILES=()

# Compile each .cpp file into an object file
for CPPFILE in src/*.cpp; do
    OBJFILE="obj/$(basename ${CPPFILE%.cpp}.o)"
    echo "Compiling $CPPFILE to $OBJFILE..."
    $COMPILER $CFLAGS $CPPFILE -o $OBJFILE

    # Add the object file to the list
    OBJFILES+=("$OBJFILE")
done

# Link the object files
echo "Linking object files..."
$COMPILER ${OBJFILES[@]} $LFLAGS

# Check if the linking was successful and run the executable
if [ $? -eq 0 ]; then
    # Run the executable
    echo "Running Risk_Game..."
    ./Risk_Game
else
    echo "Linking failed. Fix the compilation errors."
fi

echo "Done!"