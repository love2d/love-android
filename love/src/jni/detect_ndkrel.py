import sys
import re

def main(argv):
    if len(argv) > 1:
        # argv[0] = source.properties
        # argv[1] = desired NDK version
        f = open(argv[0], "r")
        contents = f.read()
        f.close()
        matches = re.findall("Pkg.Revision = (\d+)", contents)
        if len(matches) >= 1 and int(matches[0]) >= int(argv[1]):
            print("yes")
        else:
            print("no")
    else:
        print("unknown")

if __name__ == "__main__":
    main(sys.argv[1:])
