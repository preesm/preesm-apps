#!/bin/sh

# Replace keyword argument 2 by keyword argument 3 for all pointers of the file argument 1

sed -i -e "s/^$2double \*/$3double \*/g" $1
sed -i -e "s/^$2float \*/$3float \*/g" $1
sed -i -e "s/^$2int \*/$3int \*/g" $1
sed -i -e "s/^$2char \*/$3char \*/g" $1

echo Replaced keyword \"$2\" with keyword \"$3\" in file $1