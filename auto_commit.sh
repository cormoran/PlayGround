#!/usr/bin/env bash
cd $(dirname $0)

git add --all && git commit -m "daily auto commit $(date '+%Y/%m/%d')"

git push origin master
