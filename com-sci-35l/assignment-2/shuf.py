#!/usr/bin/env python3

import argparse, random, sys

class Shuf:
    def __init__(self, lines):
        self.lines = lines

    def chooseline(self):
        return random.choice(self.lines)

    def shuffle(self, count=None, repeat=False):
        if repeat:
            while True:
                yield random.choice(self.lines)
        else:
            shuffled = self.lines[:]
            random.shuffle(shuffled)
            if count is None:
                yield from shuffled
            else:
                yield from shuffled[:count]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-e", "--echo", nargs="*")
    parser.add_argument("-i", "--input-range", metavar="LO-HI", type=str)
    parser.add_argument("-n", "--head-count", metavar="COUNT", type=int)
    parser.add_argument("-r", "--repeat", action="store_true")
    parser.add_argument("file", nargs="?", default="-")

    args = parser.parse_args()

    if args.input_range:
        try:
            lo, hi = map(int, args.input_range.split('-'))
        except ValueError:
            parser.error("Invalid input")
        if lo > hi:
            parser.error("LO cannot be greater than HI")
        input_lines = list(map(str, range(lo, hi + 1)))
    elif args.echo is not None:
        input_lines = args.echo
    elif args.file == "-":
        input_lines = sys.stdin.read().splitlines()
    else:
        try:
            with open(args.file, 'r') as f:
                input_lines = f.read().splitlines()
        except IOError as e:
            parser.error("I/O error")

    generator = Shuf(input_lines)

    try:
        count = args.head_count
        for line in generator.shuffle(count=count, repeat=args.repeat):
            print(line)
            if count is not None:
                count -= 1
                if count <= 0:
                    break
    except KeyboardInterrupt:
        sys.exit(0)

if __name__ == "__main__":
    main()
