#!/bin/bash
xvfb-run -a $(dirname -- "$0")/rabarbar --no-sandbox $@
