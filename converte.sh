#!/bin/bash
shopt -s nullglob
if [ -n "$1" ]; then
	if [ -f "$1" ]; then
		echo "-> $1"
		iconv -f "ISO-8859-1" -t "UTF-8" "$1" | tr -d '\r' > tmp
		rm "$1"
		mv tmp "$1"
	else
		for f in "$1"/*
		do
			if [ -f "$f" ]; then
				echo "-> $f"
				iconv -f "ISO-8859-1" -t "UTF-8" "$f" | tr -d '\r' > tmp
				rm "$f"
				mv tmp "$f"
			fi
		done
	fi
fi
