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

<<<<<<< HEAD
print(f"{tlsh.hexdigest(rand(1024))=}")
print(f"{tlsh.digest(rand(1024))=}")
```
=======
```python
tlsh.hash(open(file, 'rb').read())
```

Note: the open statement has opened the file in binary mode.

#### Python Example
```python
import tlsh

h1 = tlsh.hash(data)
h2 = tlsh.hash(similar_data)
score = tlsh.diff(h1, h2)

h3 = tlsh.Tlsh()
with open('file', 'rb') as f:
    for buf in iter(lambda: f.read(512), b''):
        h3.update(buf)
    h3.final()
# this assertion is stating that the distance between a TLSH and itself must be zero
assert h3.diff(h3) == 0
score = h3.diff(h1)
```

#### Python Extra Options

The `diffxlen` function removes the file length component of the tlsh header from the comparison.

```python
tlsh.diffxlen(h1, h2)
```

If a file with a repeating pattern is compared to a file with only a single instance of the pattern,
then the difference will be increased if the file lenght is included.
But by using the `diffxlen` function, the file length will be removed from consideration.

#### Python Backwards Compatibility Options

If you use the "conservative" option, then the data must contain at least 256 characters.
For example,

```python
import os
tlsh.conservativehash(os.urandom(256))
```

should generate a hash, but

```python
tlsh.conservativehash(os.urandom(100))
```

will generate TNULL as it is less than 256 bytes.

If you need to generate old style hashes (without the "T1" prefix) then use

```python
tlsh.oldhash(os.urandom(100))
```


The old and conservative options may be combined:

```python
tlsh.oldconservativehash(os.urandom(500))
```

# Design Choices

- To improve comparison accuracy, TLSH tracks counting bucket height
  distribution in quartiles. Bigger quartile difference results in higher
  difference score.
- Use specially 6 trigrams to give equal representation of the bytes in the 5
  byte sliding window which produces improved results.
- Pearson hash is used to distribute the trigram counts to the counting buckets.
- The global similarity score distances objects with significant size
  difference. Global similarity can be disabled. It also distances objects with
  different quartile distributions.
- TLSH can be compiled to generate 70 or 134 characters hash strings.
  The longer version has been created to use of the 70 char hash strings is not working
  for your application.

TLSH similarity is expressed as a difference score:

- A score of 0 means the objects are almost identical.
- For the 72 characters hash, there is a detailed table of experimental Detection rates and False Positive rates
  based on the threshhold. see [Table II on page 5](https://github.com/trendmicro/tlsh/blob/master/TLSH_CTC_final.pdf)

# Clustering
- See the Python code and Jupyter notebooks in tlshCluster.
- We provide Python code for the HAC-T method.
  We also provide code so that users can use DBSCAN.
- We show users how to create dendograms for files, which are a useful diagram showing relationships between files and groups.
- We provide tools for clustering the Malware Bazaar dataset, which contains a few hundred thousand samples.
- The HAC-T method is described in [HAC-T and fast search for similarity in security](https://tlsh.org/papersDir/COINS_2020_camera_ready.pdf)

# Publications

- Jonathan Oliver, Chun Cheng, and Yanggui Chen,
	[TLSH - A Locality Sensitive Hash](https://github.com/trendmicro/tlsh/blob/master/TLSH_CTC_final.pdf).
	4th Cybercrime and Trustworthy Computing Workshop, Sydney, November 2013
- Jonathan Oliver, Scott Forman, and Chun Cheng,
	[Using Randomization to Attack Similarity Digests](https://github.com/trendmicro/tlsh/blob/master/Attacking_LSH_and_Sim_Dig.pdf).
	ATIS 2014, November, 2014, pages 199-210
- Jonathan Oliver, Muqeet Ali, and Josiah Hagen.
	[HAC-T and fast search for similarity in security](https://tlsh.org/papersDir/COINS_2020_camera_ready.pdf)
	2020 International Conference on Omni-layer Intelligent Systems (COINS). IEEE, 2020.

# Current Version

**4.11.1**
<PRE>
22/10/2021
	resolve issue #115
	CREATE_LINK does not work on CENTOS 7
</PRE>

# Change History

see [Change_History.md](Change_History.md)
>>>>>>> parent of 74efd09 (**4.11.2**)
