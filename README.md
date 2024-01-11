# TLSH

## Build

### Build & Install the C++ library

Requires cmake (>= 3.20), and a C++20-compatible compiler.

```
cmake -S . -B ./build
cmake --build ./build --config RelWithDebInfo
cmake --install ./build --config RelWithDebInfo
```

### Build & Install the Python bindings

Install requirements, then the package (also requires cmake and a C++ compiler)

```
python -m pip install -r python/requirements.txt --user --upgrade
python -m pip install . --user --upgrade
```

## Usage

### Python

Example

```python
import tlsh
import random

def rand(n):
  return bytearray([ random.randint(0, 255) for x in range(n) ])

a = tlsh.Tlsh()
for i in range( 10 ) :
    a.update(bytes(rand(256)))
a.final()

print(f"{bool(a)=}")
if a:
  print(f"Result is: {a.hexdigest()}")

print(f"{tlsh.hexdigest(rand(1024))=}")
print(f"{tlsh.digest(rand(1024))=}")
```
