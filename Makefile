cuda_path = /pgsdev/com/nvidia/cuda-8.0
nvcc = ${cuda_path}/bin/nvcc
includes = -I${cuda_path}/include
flags = -g -lineinfo -O3

all: psfTest

psfTest: psfTest.cu
	${nvcc} ${flags} ${includes} $< -o $@

