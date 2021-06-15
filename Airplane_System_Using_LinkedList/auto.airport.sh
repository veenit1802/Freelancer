#!/bin/sh

ls *.c | xargs grep -Pnr '\[(.*?)\]|\((.*?)\)|\{(.*?)\}'


#command to run is bash filename