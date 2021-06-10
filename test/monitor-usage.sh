#!/bin/sh
# Usage: ./monitor-usage.sh <PID of the process>
# Output: top.dat with lines such as `1539689171 305m 2.0`, i.e. unix time - memory with m/g suffix - CPU load in %
# To plot the output, see https://gist.github.com/jakubholynet/931a3441982c833f5f8fcdcf54d05c91
export PID=$1
rm input/top.txt
while true; do top -b -p $PID -n 1 >> input/top.txt; done
