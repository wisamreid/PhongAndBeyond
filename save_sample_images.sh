#!/bin/bash
./as1 -pl 200 200 200 0.6 0.6 0.6 -kd 1 1 0 -s diff_only.png
./as1 -pl 200 200 200 0.6 0.6 0.6 -ks 0.8 0.8 0.8 -sp 16 -s spec_only.png
./as1 -pl 200 200 200 0.6 0.6 0.6 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s amb_diff_spec.png
./as1 -pl 2 2 2 0.6 0.6 0.6 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s amb_diff_spec2.png
./as1 -pl 200 200 200 0.6 0.6 0.6 -dl 0 1 -1 0 0.4 0.4 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s point_dir_lights.png
./as1 -dl 1 1 -1 0.5 0.5 0.5 -dl 1 -1 -1 0.5 0.5 0.5 -ka 0 0.1 0.1 -kd 0 0.2 0.4 -ks 0 0.2 0.4 -sp 10 -s dl_diffuse.png
./as1 -dl 0 0.2 -1 1 1 1 -dl 1 -1 -1 0.5 0 0 -dl -1 -1 -1 0 1 0 -pl 10 10 30 0 0.1 0 -pl -4 -6 -10 0 1 1 -ka 0 0 0.1 -kd 0 0 0.3 -ks 0.5 0.5 0.5 -sp 36 -s lot_of_lights.png
./as1 -pl -5 -5 5 1 0 1 -pl 10 10 -10 1 1 1 -pl 3 -4 8 1 1 0 -pl 1 2 3 0 1 1 -ka 0.1 0.1 0.1 -kd 0.1 0.1 0.1 -ks 0.5 0.5 0.5 -sp 4 -s funky_lights.png
./as1 -pl 2 2 2 1 1 1 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -s metal_ball.png

./as1 -pl 200 200 200 0.6 0.6 0.6 -dl 0 1 -1 0 0.4 0.4 -kd 1 1 0 -ka 0.1 0.1 0 -q 20 -o -s cel_shading.png
#5. Pokeball ambient + diffuse + specular with 1 point light (pokeball.png) / NOTE YOU DON'T NEED TO DO THIS! IT'S FOR FUN!
#Kd specified using coordinates, Ka = 0.1*Kd, Ks = (0.5,0.5,0.5)
 