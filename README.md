
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
│   ├── output_graham2.ch
│   ├── output_graham3.ch
│   ├── output_jarvis.ch
│   └── output_kps.ch
├── PythonVisualiser.py
├── README.md
├── reference_kps.py
├── src
│   ├── centralcode.cpp
│   ├── compute
│   ├── convex_hull_structs.cpp
│   ├── graham_scan.cpp
│   ├── jmarch.cpp
│   └── kirkpatrickseidel.cpp
├── test
│   ├── testcase1.txt
│   ├── testcase2.txt
│   └── testcase3.txt
└── ValgrindReport.md
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
> ./run_daa a
    where a =   g, for Graham Scan
                j, for Jarvis March
                k, for KirkPatrick Seidel
> /path/to/file/containing/input/points
/* Example  - Enter input file path: /home/user/test/testcase2.txt */
```

## Visualisation
```python
python3 PythonSimpleVisualiser.py "path/to/outputfile/"
```

References -
* http://graphics.stanford.edu/courses/cs268-16-fall/Notes/KirkSeidel.pdf
* https://gist.github.com/neizod/9a367847c03fc47d7f267004de5c05ec