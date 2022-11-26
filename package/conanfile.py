from conans import ConanFile, CMake, tools


class SSGifierConan(ConanFile):
    name = "SSGifier"
    version = "1.0.0"
    license = "DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE Version 2"
    author = "Tong Liu"
    url = "https://github.com/liutng/SSGifier"
    description = "This is a CLI SSG(Static Site Generator) that generates static website."
    topics = ("Website", "generator", "static web page")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC


    def imports(self):
        self.copy("*.cpp", dst="src", src="src")
        self.copy("*.h", dst="src", src="src")
        self.copy("*.hpp", dst="src", src="src")
        self.copy("*.c", dst="src", src="src")
        self.copy("CMAkeLists.txt", dst="", src="")
        
    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="src", src="src")
        self.copy("*.cpp", dst="src", src="src")
        self.copy("*.hpp", dst="src", src="src")
        self.copy("*hello.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("CMakeList.txt",st="", src="")

    def package_info(self):
        self.cpp_info.libs = ["SSGifier"]

