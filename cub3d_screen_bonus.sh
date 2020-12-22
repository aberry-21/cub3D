echo "================== CUB3D MAKE ================="
make bonus
echo "================== CUB3D WORK ================="
./cub3D map/map.cub --save
echo ""
echo "================== CUB3D FINISH ==============="
make clean
echo "Screenshot create!"