import main
import sys

def Check():
    c = main.Cnki(sys.argv[1], sys.argv[2], sys.argv[3])
    c.cnki()

if __name__ == "__main__":
    Check()