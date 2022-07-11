#!/usr/bin/env python

import sys
import os.path

# This is a tiny script to help you creating a CSV file from a face
# database with a similar hierarchie:
#
#  philipp@mango:~/facerec/data/at$ tree
#  .
#  |-- README
#  |-- s1
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  |-- s2
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  ...
#  |-- s40
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print ("usage: create_csv <base_path>")
        sys.exit(1)

    BASE_PATH=sys.argv[1]
    SEPARATOR=";"
    sys.stdout = open("new_500_masked.csv", "w")

    label = 0
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for name in filenames:
            if label >= 500:
                break
            subject_path = dirname
            abs_path = "%s/%s" % (subject_path, name)
            print ("%s%s%d" % (abs_path, SEPARATOR, label))
            label = label + 1
    
    sys.stdout.close()