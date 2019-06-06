import argparse

parser = argparse.ArgumentParser()

parser.add_argument("u", type=float)
parser.add_argument("cd", type=float)
parser.add_argument("ps", type=float)
parser.add_argument("pi", type=float)
parser.add_argument("ls", type=float)

#parser.add_argument("-ci", "--connectionInterval", type=float)

args = parser.parse_args()

res = ((args.ps*8/1000000.0)*args.cd)/(args.u*args.ls*args.pi)
        
print(res)
