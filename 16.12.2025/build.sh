BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_DIR="build_${BUILD_SUFFIX}"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -G "$BUILD_TYPE" ..
cmake --build .
