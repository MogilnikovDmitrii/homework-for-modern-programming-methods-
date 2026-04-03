
BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"
BUILD_DIR="build_${BUILD_SUFFIX}"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Debug -G "$BUILD_TYPE" ..
cmake --build .

./vector_tests
./list_tests
# ./new_tests