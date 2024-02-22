import json
import sys

path = "test\\test\\" + sys.argv[1]
file_ptr = open(path,)


try:
    data = json.load(file_ptr)
    if type(data) is dict or type(data) is list:
        print(data)
        print("Exiting the code with exit code 0")
        sys.exit(0)
    else:
        print("Invalid Syntax")
        print("Exiting with the exit code 1")
        sys.exit(1)
except (json.JSONDecodeError, ValueError, KeyError) as e:
    print(e)
    print("Exiting the code with exit code 1")
    sys.exit(1)


file_ptr.close()
