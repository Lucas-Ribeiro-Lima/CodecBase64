<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=rect&color=0:1e3c72,100:2a5298&height=120&section=header&text=Codex&fontSize=50&fontColor=ffffff&fontAlignY=55&animation=fadeIn" />
</p>

<p align="center">
  <a href="#"><img src="https://img.shields.io/badge/build-passing-brightgreen?style=for-the-badge&logo=cmake" alt="build" /></a>
  <a href="#"><img src="https://img.shields.io/badge/C++-17%2B-blue?style=for-the-badge&logo=c%2B%2B" alt="C++" /></a>
  <a href="#"><img src="https://img.shields.io/badge/platform-cross--platform-lightgrey?style=for-the-badge&logo=linux" alt="platform" /></a>
  <a href="#"><img src="https://img.shields.io/badge/license-MIT-blueviolet?style=for-the-badge" alt="license" /></a>
</p>

<p align="center">
  <b>A modern C++ Base64 and HEX codec library — simple, fast, and clean with.</b>
</p>

## 🚀 Features  
- 🔡 Encode and decode Base64 strings  
- ⚡ Optimized for performance and readability  
- 🧩 Modular project structure with CMake  
- 🛠️ Easy to integrate into existing C++ projects  

## 🧱 Project Structure

```
Codex
├─ assets/
├─ include/        # Header files
├─ src/            # Source code
├─ CMakeLists.txt
├─ .gitignore
└─ app.rc
```

## 🧪 Build & Run  
```
git clone https://github.com/Lucas-Ribeiro-Lima/Codex.git
cd Codex
mkdir build && cd build
cmake . .
cmake --build .
````

## 💡 Usage Examples

```
Usage: [mode] [options] [encoder/decoder] [input file] [output file] 
e.g. codex --decode base64 input_file.txt output_file.jpg 
Modes:  
    -e/--encode   Codify the bytes with the specified encoding algorithm 
    -d/--decode Decodify the file with the specified encoding algorithm.  
                    Not every encoder permits a decoding, like the hash function sha256! 
"Input: "  "\n" \
    -r  Recursive mode.  
                On encode the output file will concatenate the data with. 
                On decode recursive mode output files will be incremented named. 
                Type auto-detected obrigatory on recursive. 
    -s  String input mode. The string passed as input will be parsed as the data.
Output:  
    -t  Terminal output mode. The content will be redirect to stdout. 
    -x  Disable the file type auto-detect mode 
                If none magic signature found, the fallback type is .txt. 
Input: Path to the file with the string 
Output: Path where the output file will be created 
TO DO 
Encoders:  
     * base64 
     * hex 
```

## 🧰 Tech Stack

* 🧠 C++
* 🧩 CMake
* 🖥️ Cross-platform


## 👤 Author

**Lucas Ribeiro Lima**
Software Engineer | Systems & Network Administrator
[GitHub Profile](https://github.com/Lucas-Ribeiro-Lima)
