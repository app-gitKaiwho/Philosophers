#!/bin/sh

git remote add both "$1"
git add . && git commit -m "remote added" && git push && git push -f both
