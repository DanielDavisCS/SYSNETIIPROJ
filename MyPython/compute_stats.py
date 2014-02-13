#!/usr/bin/env python
'''
Name: Thomas Cole Amick
Course:COP3990C 
Assignment:hw03

Run: python compute_stats.py <file_name.csv>
Description: Takes in input from a csv file and calculates the mean, and variance of each line.
For each line of the input file, the mean, variance and number of columns are writen to the output file

'''

#import librarys
import sys

#define functions
def calc_mean(num_list):
    """Calculates mean; The parameter should be a list to perform calculation correctly"""
    num = 0.0
    for i in num_list:
        num += float(i)
    return num/len(num_list) 

def calc_variance(num_list):
    """Calculate variance; The parameter should be a list to perform the calculation correctly"""
    num = 0.0
    for i in num_list:
        num += float(i)**2
    return (num/len(num_list)) - calc_mean(num_list)**2

#check for proper command line arguments"""
if len(sys.argv) != 3:
	print 'Incorrect number of command line arguments'
   	print 'python compute_stats.py <csv_file.csv> <some_output_file.csv>'
   	sys.exit()
if sys.argv[1][-3:] != 'csv' or sys.argv[2][-3:] != 'csv':
	print 'Incorrect file extensions'
    	print 'python compute_stats.py <csv_file.csv> <some_output_file.csv>'
	sys.exit()

#define variables
csv_data = {}
mean = variance = col_count = 0.0

#open csv files
argv_list = sys.argv
csv_file_in = open(argv_list[1],'r')
csv_file_out = open(argv_list[2], 'w')

#create outfile header
header = '# of columns,mean,variance\n'
csv_file_out.write(header)
    	
#calculates csv file statistics by reading data line by line from the input file. Writes # of columns, mean, and variance to out_put file in csv format"""
print "Calculating on " + argv_list[1] + "..."  
lines = csv_file_in.readlines()
for line in lines:
	line = line.strip().split(',')
	mean = calc_mean(line)
	variance = calc_variance(line)
	row = str(len(line)) + ',' + str(mean) + ',' + str(variance) + '\n'
	csv_file_out.write(row)
print "Writing to " + argv_list[2] + "..."

#close files
csv_file_in.close()
csv_file_out.close()









