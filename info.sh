#!/bin/bash
#output file duration
ffprobe -i $1 -show_entries format=duration -v quiet -of csv="p=0"
