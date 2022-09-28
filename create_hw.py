# !/usr/bin/python3
import argparse,os
from shutil import copyfile

parser = argparse.ArgumentParser()
parser.add_argument('contest_name',type=str)
parser.add_argument('problem_count',type=int)
args = parser.parse_args()

dir_name = args.contest_name + '/'

try:
    # Create target Directory
    os.mkdir(dir_name)
    print("Directory " , dir_name ,  " created ") 
except FileExistsError:
    print("Directory " , dir_name ,  " already exists")



for problem_id in range(1,args.problem_count+1):
  file_name = f'p{problem_id}.cpp'

  try:
    copyfile('template.cpp', os.path.join(dir_name, file_name))
    print('File ' + file_name + ' created')
  except:
    print("Failed while copying file " + file_name)
