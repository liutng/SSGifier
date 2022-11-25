# SSGifier

This is a CLI SSG(Static Site Generator) that generates static website.

# Optional functions implemented

- allow the user to specify a different output directory using --output or -o. If not specified, dist will be used, but if the user specifies a different output path, use that. Print an error if the specified output path is not a valid directory.
- allow the user to optionally specify a --stylesheet or -s URL to a CSS stylesheet to be used in the <head> of your generated HTML files.

# How to use

This is a CLI software which requires to use terminal to run it.

The list below is all the different parameters you can pass to SSGifier.  
-v --version - prints out the version of SSGifier.
-o, --output - specify the output directory, the directory " dlist" is used by default.(Optional)  
-i, --input - specify the input files\directory, this is an necessary argument.  
-s, --stylesheet - specify the stylesheet for the HTML pages.(Optional)  
-h, --help - show help.
-c, --config - config command

# Updated

Markdown Support added for # Headings and \* Italics just use a file with a .md file extension

JSON Support with the config option Using the JSON parser from this Repository [nlohmann/json](https://github.com/nlohmann/json)

More Markdown support for Markdown Headers, Code blocks, links, lists, and styles(bold, itatlic, quotes, etc.) by using [maddy](https://github.com/progsource/maddy)

  # Conan Package
  You can also use SSGifier in your projectas as a library. To use it you need to do following:
  1. Downlaod & install `Conan` from [here](https://conan.io/downloads.html) and `clang` from [here](https://releases.llvm.org/download.html).
  2. Create a `conanfile.txt` inside your project and add `SSGifier/1.0.0` in the category of `[requires]` to `conanfile.txt`. Click to see [official documents](https://docs.conan.io/en/latest/using_packages/conanfile_txt.html). You can use this template:
```
[requires]
SSGifier/1.0.0

[generators]
cmake
```
  3.  Edit `conan.conf` file in the location `C:\Users\<your user name>\.conan` and add `revisions_enabled = 1` to `[general]`.
  4. Add this remote repository to conan by using this command `conan remote add tommy-conan-local https://tommyliu.jfrog.io/artifactory/api/conan/tommy-conan-local`
  5. Add credential information to this repository by using this command `conan user -p AKCp8nHPJwRCr2my24TiMaikQgQUW4e3xRbqsiGw45j9nPfPdLWEREYigcMLLW4pQtqg18n8b -r tommy-conan-local lt19930320@gmail.com`.
  6. Go to the directory of you project which you created in step 2(make sure conaninfo.txt), install SSGifier by using `conan install . -r tommy-conan-local`
  7. Go to `C:\Users\<your user name>\.conan\data\SSGifier\1.0.0\_\_\package\3fb49604f9c2f729b85ba3115852006824e72cab\src` to find the source file.
  8. Compile these code. For gcc, use `g++ -std=c++17 main.cpp Utils.cpp ArgumentQueue.cpp FileProcessor.cpp MessagePrinter.cpp`, for clang, use `clang++ -std=c++17 main.cpp Utils.cpp ArgumentQueue.cpp FileProcessor.cpp MessagePrinter.cpp`.
  9. After compilation, a binrary executatable of SSGifier will be generated with the name of `a.exe`. 
  10. Enjoy SSGifier.
  
# License

[Do What The Fuck You Want To Public License(WTFPL)](https://raw.githubusercontent.com/liutng/SSGifier/main/License.md)
