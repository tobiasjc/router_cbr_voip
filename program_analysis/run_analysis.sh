#!/bin/bash
#!/usr/bin/python3.7

# arguments
u_v=(0.1 0.5 0.52 0.13 0.45 0.12)
u_c=(0.3 0.1 0.28 0.77 0.5 0.87)
t=(10452 35000 22400 1220 104570 167000)
psv=(380 1200 1777 9563 299 1239)
piv=(0.02 0.01 0.1 2 5 1)
cdv=(10 50 100 30 200 150)
L=(130 162 18 200 30 188)

# program dir
dir="../cmake-build-debug/"

# program name
name="router_cbr_list"

# full path
path=${dir}${name}

# recompile program using cmake
cmake --build ${dir}

# py scripts path
u_c_path="./u_c.py"
u_v_path="./u_v.py"

# execute program using stated arguments
for ((i = 0; i < ${#u_v[@]}; i++))
do
	pic=$(python3.7 ${u_c_path} ${u_c[i]} 441 ${L[i]});
	civ=$(python3.7 ${u_v_path} ${u_v[i]} ${cdv[i]} ${psv[i]} ${piv[i]} ${L[i]});
	"./"${path} ${t[i]} ${pic} ${psv[i]} ${piv[i]} ${civ} ${cdv[i]} ${L[i]};
	echo ""
done

