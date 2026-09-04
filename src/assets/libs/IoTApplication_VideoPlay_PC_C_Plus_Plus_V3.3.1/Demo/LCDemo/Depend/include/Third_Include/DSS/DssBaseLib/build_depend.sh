#!/bin/bash

# this is an example for build depend package
# usually it doesn't need to modify

TARGET_TYPE=$1

# export PYTHONPATH=./:$PYTHONPATH
# python -c "import dslct; do_build_depend_ui( $TARGET_TYPE )"

python dslct.py do_build_depend_ui $TARGET_TYPE

