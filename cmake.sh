# folder for organized build output
mkdir bin

# build with cmake
cmake . -B build
cd build
make

# move the build products into the bin directory
cp src/LogicGates ../bin/LogicGates
cd ..
cp src/example.txt bin/example.txt

# create the release tarball
tar -cjf linux.tar.bz bin


# test the app
cd bin
./LogicGates