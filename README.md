# cuda_deduplicator
Tool for detecting and correcting duplicate transfers in CUDA applications. This is done by wrapping the function CUDA driver API function calls to intercept the data being transfered to/from device. This project supports the following features:

**Detection of Duplicate Transfers**

Collects statistical information about the presence of duplicate data transfers within an application. 

- Counting of the number of data transfers containing duplicate data to/from the GPU
- Size of the duplicate transfers
- Amount of time spent transferring duplicate data (accuracy of this number is a work in progress)
- Supported transfer calls: cuMemcpyHtoDAsync_v2,cuMemcpyAtoD_v2,cuMemcpyAtoH_v2,cuMemcpyAtoHAsync_v2,cuMemcpyDtoA_v2,cuMemcpyDtoH_v2,cuMemcpyDtoHAsync_v2, and cuMemcpyHtoD_v2.

**Automatic Data Deduplication**

Functions by creating a temporary cache in GPU memory for data transfers. When a duplicate transfer is detected to the GPU device (detected via hashing), a device to device transfer from this cache will replace the host to device transfer.

- Supported transfer calls: cuMemcpyHtoDAsync_v2, cuMemcpyAtoD_v2, and cuMemcpyHtoD_v2

**Building and Installation**

cd build
cmake ..

*Required build parameters*

The following parameters are required at CMake configure time if not set by environment variables.

- -DCUDA_TOOLKIT_ROOT_DIR=<Location of Cuda Toolkit> (Optional on Cray Machines)
- -DLIBCUDA_SO=<Absolute path to libcuda.so, this should be the path to libcuda that applications are linked against> (Optional on Cray Machines)
- -DLIBCUDART_SO=<Absolute path to libcudart.so> (Optional on Cray Machines)
- -DLIBELF_LIBFILE=<Absolute path to Libelf.so> (Optional on ORNL Cray Titan)
- -DLIBELF_INCLUDE=<Path to libelf include directory> (Optional on ORNL Cray Titan)
- -DLIBDWARF_LIBFILE=<Absolute path to libdwarf.so, CANNOT be the static version of libdwarf> (Optional on ORNL Cray Titan)
- -DLIBDWARF_INCLUDE=<Path to libdwarf include directory> (Optional on ORNL Cray Titan)

*Optional Build Parameters*

The following parameters are not required but can reduce compilation time if set (by skipping compilation of python/dyninst)

- -DDYNINST_ROOT=<Path to the installation directory of dyninst (containing /lib and /include)
- -DPYTHON_ROOT=<Path to the installation directory of python 2.7> 





