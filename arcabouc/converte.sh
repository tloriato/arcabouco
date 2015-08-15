#!/bin/bash
shopt -s nullglob
if [ -n "$1" ]; then
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
