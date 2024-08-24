import Adamlibrary

# Sabit değerler belirleyin (sisteminizdeki `sizeof(int)`'i kontrol edin)
SIZEOF_INT = 4  # veya doğru boyutu belirlemek için uygun bir değer

def test_calloc():
    ptr = Adamlibrary.calloc(5, 10)
    assert ptr is not None
    print("calloc test passed.")

def test_realloc():
    ptr = Adamlibrary.calloc(5, 10)
    new_ptr = Adamlibrary.realloc(ptr, 100)
    assert new_ptr is not None
    print("realloc test passed.")

def test_bsearch():
    base_list = [1, 2, 3, 4, 5]
    key = 3
    result = Adamlibrary.bsearch(key, base_list, len(base_list), SIZEOF_INT)
    assert result == key
    print("bsearch test passed.")

def test_qsort():
    base_list = [5, 3, 1, 4, 2]
    sorted_list = Adamlibrary.qsort(base_list, len(base_list), SIZEOF_INT)
    assert sorted_list == [1, 2, 3, 4, 5]
    print("qsort test passed.")

def test_memcpy():
    dest = bytearray(10)
    src = bytearray([1, 2, 3, 4, 5])
    Adamlibrary.memcpy(dest, src, len(src))
    assert dest[:len(src)] == src
    print("memcpy test passed.")

def test_strtok():
    string = "hello world"
    delimiters = " "
    token = Adamlibrary.strtok(string, delimiters)
    assert token == "hello"
    token = Adamlibrary.strtok(None, delimiters)
    assert token == "world"
    print("strtok test passed.")

def test_asctime():
    import time
    tm = time.localtime()
    result = Adamlibrary.asctime(tm.tm_sec, tm.tm_min, tm.tm_hour, tm.tm_mday, tm.tm_mon, tm.tm_year)
    assert isinstance(result, str)
    print("asctime test passed.")

def test_localtime():
    import time
    rawtime = time.time()
    result = Adamlibrary.localtime(rawtime)
    assert len(result) == 6
    print("localtime test passed.")

def main():
    test_calloc()
    test_realloc()
    test_bsearch()
    test_qsort()
    test_memcpy()
    test_strtok()
    test_asctime()
    test_localtime()

if __name__ == "__main__":
    main()

