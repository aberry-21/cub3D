echo "================== CUB3D MAKE ================="
make
echo "================== CUB3D TEST ================="
./cub3D map/txt.cub
# valgrind --leak-check=full 
echo ""
echo "================== CUB3D CLEAN ================"
# make fclean