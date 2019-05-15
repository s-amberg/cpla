import ctypes

_fancy = ctypes.CDLL('libw13_solution_01_FancyLibHourglass.dll')
_fancy.cppug_be_fancy_on_stdout.argtypes = [ctypes.c_char_p]

def be_fancy(ent):
    if not type(ent) is str:
        raise TypeError("Argument must be a string")

    _fancy.cppug_be_fancy_on_stdout(ent.encode('utf-8'))

if __name__ == "__main__":
    be_fancy("python")
