import main
import unittest
import sys

class TestMain(unittest.TestCase):

    def test_read_empty_file(self):
        path_1=""
        path_2=""
        path_3=""
        c = main.Cnki(path_1, path_2, path_3)
        c.cnki()

    def test_non_exist_file(self):
        path_1 = "C:Users/mumao/Desktop/neloneli/neloneli/3122004444/orig.txt"
        path_2 = "C:Users/mumao/Desktop/neloneli/neloneli/3122004444/orig_0.8.add.txt"
        path_3 = "C:Users/mumao/Desktop/neloneli/neloneli/3122004444/orig_2.txt"
        c = main.Cnki(path_1, path_2, path_3)
        c.cnki()

if __name__ == '__main__':
    test=TestMain()
    test.test_read_empty_file()
    test.test_non_exist_file()