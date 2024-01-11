import pathlib
import random


CURFILE = pathlib.Path(__file__)
CURDIR = CURFILE.parent
TEST_DATA_PATH = CURDIR / "../../data"


def rand(n: int):
    return bytearray([random.randint(0, 255) for x in range(n)])


def test_import_module():
    assert __import__("tlsh")


def test_basic_test():
    tlsh = __import__("tlsh")
    buf = rand(1024)

    hexval = tlsh.hexdigest(buf)
    assert isinstance(hexval, str)
    val = tlsh.digest(buf)
    assert isinstance(val, bytes)

    for _ in range(100):
        a = tlsh.Tlsh()
        a.update(buf)
        a.final()
        assert bool(a)
        assert isinstance(a.hexdigest(), str)
        assert isinstance(a.digest(), bytes)
        assert val == a.digest()
        assert hexval == a.hexdigest()


def test_batch_test():
    tlsh = __import__("tlsh")
    expected_values = [
        x.strip().split(maxsplit=1)
        for x in (TEST_DATA_PATH / "expected.txt").open().readlines()
    ]

    for fname, expected_value in expected_values:
        buf = (TEST_DATA_PATH / fname).open("rb").read()
        assert tlsh.hexdigest(buf).lower() == expected_value.lower()
        assert tlsh.digest(buf) == bytes.fromhex(expected_value)
