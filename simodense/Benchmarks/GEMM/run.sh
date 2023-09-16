
clear
echo "N=$1, TILE_SIZE=$2, TILED=$3"

bash build.sh $1 $2 $3
cd ..
cd ..
cd RTL_and_simulation/
bash run.sh