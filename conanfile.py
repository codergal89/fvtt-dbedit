from conans import ConanFile, CMake


class FvttDbEdit(ConanFile):
    name = "fvtt-dbedit"
    version = "1.0.0"
    license = "BSD-3-clause"
    description = "A database file editing suite for Foundry VTT"
    url = "https://github.com/codergal89/fvtt-dbedit"
    settings = "os", "compiler", "build_type", "arch"
    export_sources = "source/*"
    generators = "cmake"
    build_requires = [
        "nlohmann_json/[~=3.9]",
        "catch2/[~=2.13]",
    ]

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        cmake.configure(source_folder="source")
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*", src="bin", dst="bin", keep_path=False)
        self.copy("LICENSE", dst="licenses", keep_path=False)
