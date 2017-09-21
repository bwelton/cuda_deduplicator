from spack import *
import os.path
class Cudadedup(Package):
    version('master', git='https://github.com/bwelton/cuda_deduplicator.git', branch='master', preferred=True)
    version('develop', git='https://github.com/bwelton/cuda_deduplicator.git', branch='develop')
    version('v0.1', git='https://github.com/bwelton/cuda_deduplicator.git', branch='master', tag="v0.1")
    # depends_on('libelf')
    depends_on("elf@1", type="link")
    depends_on('libdwarf')
    depends_on('dyninst')
    depends_on('python@2.7.13+shared')
    depends_on('cuda')
    depends_on('cmake', type="build")

    ## Variants 
    variant('stacktrace', default=False, description="Enable Stacktracing for found duplicates.")
    variant('timeline', default=False, description="Enable Transfer Timeline.")

    def install(self, spec, prefix):
        ## Find the location of libcuda.so.... 
        libcuda_path = ""
        if os.path.exists("/opt/cray/nvidia/default/lib64/libcuda.so.1"):
            ## We are on a cray machine which hosts libcuda in a special location....
            libcuda_path = "/opt/cray/nvidia/default/lib64/libcuda.so.1"
        elif os.path.exists("/usr/lib64/libcuda.so.1"):
            ## Standard location for libcuda.so
            libcuda_path = "/usr/lib64/libcuda.so.1"
        elif os.path.exists("/usr/lib64/libcuda.so"):
            ## Standard location for libcuda.so
            libcuda_path = "/usr/lib64/libcuda.so"            
        elif os.path.exists("/lib64/libcuda.so.1"):
            ## Less common but somtimes appears here...
            libcuda_path = "/lib64/libcuda.so.1"
        elif os.path.exists("/lib64/libcuda.so"):
            ## Less common but somtimes appears here...
            libcuda_path = "/lib64/libcuda.so"
        else:
            raise InstallError("Could not find libcuda.so in any of the standard places...")
        libcuda_art = join_path(spec["cuda"].prefix, "lib64/libcudart.so")
        timeline = "no"
        strace = "no"
        if "+timeline" in spec:
            timeline = "yes"

        if "+stacktrace" in spec:
            strace = "yes"

        with working_dir("spack-build", create=True):
            cmake("..", 
                "-DPYTHON_EXECUTABLE=%s" % join_path(spec["python"].prefix.bin,"python"),
                "-DPYTHON_INCLUDE_DIR=%s" % spec["python"].prefix.include,
                "-DPYTHON_LIBRARY=%s" % join_path(spec["python"].prefix.lib,"libpython2.7.so"),
                "-DLIBELF_LIBFILE=%s" % join_path(spec["elf"].prefix.lib,"libelf.so"),
                "-DLIBELF_INCLUDE=%s" % spec["elf"].prefix.include,
                "-DLIBDWARF_LIB=%s" % join_path(spec["libdwarf"].prefix.lib,"libdwarf.so"),
                "-DLIBDWARF_INCLUDE=%s" % spec["libdwarf"].prefix.include,
                "-DDYNINST_ROOT=%s" % spec["dyninst"].prefix,
                "-DCUDA_TOOLKIT_ROOT_DIR=%s" % spec["cuda"].prefix,
                "-DLIBCUDA_SO=%s" % libcuda_path,
                "-DLIBCUDART_SO=%s" % libcuda_art,
                "-DENABLE_STRACE=%s" % strace,
                "-DENABLE_TIMELINE=%s" % timeline,
                "-DSPACK_INSTALL=yes", *std_cmake_args)
            make()
            make('install')


