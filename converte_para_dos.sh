#!/bin/bash
shopt -s nullglob
if [ -n "$1" ]; then
	if [ -f "$1" ]; then
		echo "-> $1"
		unix2dos -n "$1" tmp
		iconv -f "UTF-8" -t "Latin1" tmp > "$1"
		rm tmp
	else
		for f in "$1"/*
		do
			if [ -f "$f" ]; then
				echo "-> $f"
				unix2dos -n "$f" tmp
				iconv -f "UTF-8" -t "Latin1" tmp > "$1"
				rm tmp
			fi
		done
	fi
fi

