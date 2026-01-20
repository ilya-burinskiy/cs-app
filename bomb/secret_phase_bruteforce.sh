#!/bin/bash

PROGRAM="./bomb"
FILE_PATH="./defuse_input.txt"
TARGET="Wow! You've defused the secret stage!"

for ((i=1; i<=1001; i++)); do
    echo "$i" | "$PROGRAM" "$FILE_PATH" \
        | sed "s/^/[$i] /" \
        | grep -F "$TARGET"
done