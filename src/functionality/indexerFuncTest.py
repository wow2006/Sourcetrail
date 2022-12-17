#!/usr/bin/env python3
from argparse import ArgumentParser
import os
import subprocess

def main(indexer_path):
    """
    1. check the exectuable exists
    2. run the exectuable with corrent argments
    3. check the process exit value
    4. check the process output
    """
    #
    assert os.path.exists(indexer_path)
    #
    process = subprocess.run(indexer_path, check=True)
    assert process.returncode == 0

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("process_path", type=str)
    args = parser.parse_args()
    main(args.process_path)
