#!/bin/bash

# Set the build directory
BUILD_DIR="build"

# Remove old build directory
echo "🔄 Cleaning old build directory..."
rm -rf "$BUILD_DIR"

# Run CMake
echo "🔧 Configuring project with CMake..."
cmake -G Ninja -B "$BUILD_DIR"

# Build the project
echo "🚀 Building project..."
if cmake --build "$BUILD_DIR"; then
    echo "✅ Build successful!"

    # Run the executable
    EXECUTABLE="$BUILD_DIR/OpenGLWSL"
    if [[ -f "$EXECUTABLE" ]]; then
        echo "🎮 Running the application..."
        "$EXECUTABLE"
    else
        echo "❌ Error: Executable not found!"
    fi
else
    echo "❌ Build failed!"
    exit 1
fi