clean="make clean"
if [ -f my_program ]; then
    eval $clean
fi 

make 

./my_program