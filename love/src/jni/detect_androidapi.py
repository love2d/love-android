import sys
import re

def main(argv):
    if len(argv) > 1:
        # argv[0] = android-%d
        # argv[1] = %d
        matches = re.findall("android-(\d+)", argv[0])
        if len(matches) >= 1 and int(matches[0]) >= int(argv[1]):
            print("yes")
        else:
            print("no")
    else:
        print("unknown")

if __name__ == "__main__":
    main(sys.argv[1:])
