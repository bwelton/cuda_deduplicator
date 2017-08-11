## 
# Find the specific CUDA libraries that we are interested in
if (NOT DEFINED LIBCUDA_SO)
	message(ERROR " Set -DLIBCUDA_SO= to the libcuda.so file in use by the system")
endif(NOT DEFINED LIBCUDA_SO)

if (NOT DEFINED LIBCUDART_SO)
	message(ERROR " Set -DLIBCUDART_SO= to the libcudart.so file in use by the system")
endif(NOT DEFINED LIBCUDART_SO)