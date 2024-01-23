from typing import Optional, Union
from ._tlsh import Tlsh as _Tlsh


class Tlsh:
    """Wrapper for the native class _tlsh.Tlsh"""

    def __init__(self, buffer: Optional[bytes] = None) -> None:
        self._tlsh_obj = _Tlsh()
        if buffer:
            self.update(buffer)

    def __bool__(self) -> bool:
        return self._tlsh_obj.isValid()

    def update(self, buffer: Union[bytes, bytearray]) -> None:
        assert isinstance(buffer, bytes) or isinstance(buffer, bytearray)
        _buffer = buffer if isinstance(buffer, bytearray) else bytearray(buffer)
        self._tlsh_obj.update(_buffer)

    def final(self, buffer: Union[bytes, bytearray] = b"") -> None:
        assert isinstance(buffer, bytes) or isinstance(buffer, bytearray)
        _buffer = buffer if isinstance(buffer, bytearray) else bytearray(buffer)
        self._tlsh_obj.final(_buffer, 0)

    def hexdigest(self) -> str:
        assert bool(self)
        return str(self._tlsh_obj.getHash(0))

    def digest(self) -> bytes:
        return bytes.fromhex(self.hexdigest())

    def diff(self, other: "Tlsh", different_length: bool = True) -> int:
        return self._tlsh_obj.totalDiff(other._tlsh_obj, different_length)


version: str = _Tlsh().version


def hexdigest(buffer: bytes) -> str:
    t = Tlsh(buffer)
    t.final()
    return t.hexdigest()


def digest(buffer: bytes) -> bytes:
    t = Tlsh(buffer)
    t.final()
    return t.digest()
