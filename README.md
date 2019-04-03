
# Implementation of multiple convex hull algorithms done in  C++.

## Directory Reference
```bash
.
├── benchmark
├── include
│   ├── convex_hull_structs.h
│   ├── graham_scan.h
│   ├── jmarch.h
│   └── kirkpatrickseidel.h
├── Makefile
├── output
├── PythonComplexVisualiser.py
├── PythonSimpleVisualiser.py
├── README.md
├── reference_kps.py
├── src
│   ├── centralcode.cpp
│   ├── convex_hull_structs.cpp
│   ├── graham_scan.cpp
│   ├── jmarch.cpp
│   └── kirkpatrickseidel.cpp
├── test
│   ├── specialcase.txt
│   ├── testcase1.txt
│   ├── testcase2.txt
│   └── testcase3.txt
├── ValgrindReport.md
└── visuals
    ├── outputGraham.gif
    ├── outputJarvis.gif
    └── outputKirkPatrickSeidel.gif
```

## Compiling
```bash
make
```
## Remove Build Files
```bash
make clean
```
## Using Convex Hull Algorithm
```c++
> ./run_daa a [1]
    where a =   g, for Graham Scan
                j, for Jarvis March
                k, for KirkPatrick Seidel
    where [1] is an optional argument which creates necessary files required for complex visuliasation output.
> /path/to/file/containing/input/points
/* Example  - Enter input file path: /home/user/test/testcase2.txt */
```

## Visualisation
```python
python3 PythonSimpleVisualiser.py "path/to/outputfile/" # Simple
python3 PythonComplexVisualiser.py "path/to/outputfile/" # Step-by-Step
```

## Documentation
```
Can be accessed by opening "html/index.html" file. Made with doxygen.
```

References -
* http://graphics.stanford.edu/courses/cs268-16-fall/Notes/KirkSeidel.pdf
* https://gist.github.com/neizod/9a367847c03fc47d7f267004de5c05ec