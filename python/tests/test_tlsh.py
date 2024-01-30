import pathlib
import random


CURFILE = pathlib.Path(__file__)
CURDIR = CURFILE.parent
TEST_DATA_PATH = CURDIR / "../../tests/datasets"


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

        b = tlsh.Tlsh()
        b.update(buf)
        b.final()

        assert bool(a)
        assert isinstance(a.hexdigest(), str)
        assert isinstance(a.digest(), bytes)
        assert val == a.digest()
        assert hexval == a.hexdigest()
        assert a.diff(b) == 0


def test_batch_test_base():
    tlsh = __import__("tlsh")
    expected_values = [
        x.strip().split(maxsplit=1)
        for x in (TEST_DATA_PATH / "base.txt").open().readlines()
    ]

    for fname, expected_value in expected_values:
        buf = (TEST_DATA_PATH / fname).open("rb").read()
        tlsh_hex = tlsh.hexdigest(buf).upper()
        tlsh_raw = tlsh.digest(buf)
        assert (
            tlsh_hex == expected_value.upper()
        ), f"Mismatch on {fname}: expected={expected_value.upper()}  got={tlsh_hex}"

        assert tlsh_raw == bytes.fromhex(
            expected_value
        ), f"Mismatch on {fname}: expected={tlsh_raw}  got={bytes.fromhex(expected_value)}"
