import subprocess
import sys
from pathlib import Path

BUILD_PATH = "./.build/Release"


def main():
    exepath = Path.cwd() / BUILD_PATH
    for exe in exepath.glob("test*.exe"):
        args = [str(exe.absolute())]
        print(
            "========================================================================================"
        )
        print(f"==== Run {exe.name}")
        print(
            "========================================================================================"
        )
        proc = subprocess.run(args, cwd=exepath, capture_output=True)

        print(proc.stdout)

        if proc.returncode != 0:
            print(f"{exe.name} failed!")
            sys.exit(1)


if __name__ == "__main__":
    main()
