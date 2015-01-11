PhongAndBeyond
==============

Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
repository @ https://github.com/EdsterG/PhongAndBeyond

#### Platform 
    
    MacOS

#### C++
  
  ### Classes: ~/src
      
    camera.cpp
    circle.cpp
    color.cpp
    example_01.cpp
    light.cpp
    vector.cpp
    viewport.cpp

#### Files: ~/

    src // C++ source
    include // header files
    autosave // sample images
    Makefile

#### Bash Script 

    sh save_sample_images.sh // auto saves sample png files to /autosave

#### Additional Commandline Arguments

    ### -s <filename.png> // saves png to /autosave
    ### -o // Changes background to grey
    ### -q <integer> // Toon Shading: quantization step size`
    ### -a // Anisotropic Shading 
    ### -t <double> <double> <integer> // Perlin Noise Texture: zoom, decayRate, number of octaves
    ### -m // Multiple Spheres

    ### EXPLICT SAMPLE IMAGE GENERATION:

      ./as1 -pl 200 200 200 0.6 0.6 0.6 -kd 1 1 0 -s diff_only.png
      ./as1 -pl 200 200 200 0.6 0.6 0.6 -ks 0.8 0.8 0.8 -sp 16 -s spec_only.png
      ./as1 -pl 200 200 200 0.6 0.6 0.6 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s amb_diff_spec.png
      ./as1 -pl 2 2 2 0.6 0.6 0.6 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s amb_diff_spec2.png
      ./as1 -pl 200 200 200 0.6 0.6 0.6 -dl 0 1 -1 0 ls 0.4 0.4 -kd 1 1 0 -ka 0.1 0.1 0 -ks 0.8 0.8 0.8 -sp 16 -s point_dir_lights.png
      ./as1 -dl 1 1 -1 0.5 0.5 0.5 -dl 1 -1 -1 0.5 0.5 0.5 -ka 0 0.1 0.1 -kd 0 0.2 0.4 -ks 0 0.2 0.4 -sp 10 -s dl_diffuse.png
      ./as1 -dl 0 0.2 -1 1 1 1 -dl 1 -1 -1 0.5 0 0 -dl -1 -1 -1 0 1 0 -pl 10 10 30 0 0.1 0 -pl -4 -6 -10 0 1 1 -ka 0 0 0.1 -kd 0 0 0.3 -ks 0.5 0.5 0.5 -sp 36 -s lot_of_lights.png
      ./as1 -pl -5 -5 5 1 0 1 -pl 10 10 -10 1 1 1 -pl 3 -4 8 1 1 0 -pl 1 2 3 0 1 1 -ka 0.1 0.1 0.1 -kd 0.1 0.1 0.1 -ks 0.5 0.5 0.5 -sp 4 -s funky_lights.png
      ./as1 -pl 2 2 2 1 1 1 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -s metal_ball.png
      ./as1 -pl 200 200 200 0.6 0.6 0.6 -dl 0 1 -1 0 0.4 0.4 -kd 1 1 0 -ka 0.1 0.1 0 -q 20 -o -s cel_shading.png

   ### EXTRA IMAGES
      ./as1 -pl 2 2 2 0 0 1 -pl 2 2 2 1 1 1 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -t 0.75 0.5 8 -a 1 100
      ./as1 -pl 2 2 2 0 0 1 -pl 2 2 2 1 1 1 -dl 3 3 3 1 0 0 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -t 0.75 0.5 8 -a 1 10
      ./as1 -pl 2 2 2 0 0 1 -pl 2 2 2 1 1 1 -dl 3 3 3 1 0 0 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -t 0.75 0.5 8
      ./as1 -pl 2 2 2 0 0 1 -pl 2 2 2 1 1 1 -dl 3 3 3 1 0 0 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -t 0.75 0.5 8
      ./as1 -pl 0 0  2 0 0 1 -pl 2 2 2 1 1 1 -ka 0.1 0.1 0.1 -kd 0.4 0.4 0.4 -ks 0.4 0.4 0.4 -sp 10 -t 0.75 0.5 8 -a 1 100 


#### Additional implimentations 

    ### Mouse/Keyboard controlled light positions:
      #INSTRUCTIONS:
        1) press the number key corresponding to the camera to be controlled (1-9,0) -> light 1-9,10
        2) light will track mouse movements 
        3) up/down arrows to change light radius 
    
    ### Autosaved png images: 
      run with bash script above

    ### Anisotropic diffuse and specular shading:
      commandline -a

    ### Toon shading:
      commandline -q

    ### Outline:
      commandline -o 

    ### Perlin Noise Surface Texture:
      commandine - t

    ### Multiple Spheres:
      commandline -m

#### Credits

  ### http://www.cs.utah.edu/~shirley/papers/jgtbrdf.pdf
  ### loadpng library
  ### http://rosettacode.org/wiki/Linear_congruential_generator

 

