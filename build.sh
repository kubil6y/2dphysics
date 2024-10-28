#!/bin/bash

# Create dist directory if it doesn't exist
if [ ! -d "dist" ]; then
    echo "Creating dist directory..."
    mkdir dist
fi

# Change to the dist directory
cd dist

# Run CMake to configure the project
echo "Configuring the project with CMake..."
cmake ..

# Build the project
echo "Building the project..."
make

# Notify user of the completed build
if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "Build failed. Check the output for errors."
fi
