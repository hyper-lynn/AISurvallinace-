#!/bin/bash

# this is an example for update depend package
# usually it doesn't need to modify

TARGET_TYPE=$1

# export PYTHONPATH=./:$PYTHONPATH
# python -c "import dslct; do_update_depend_ui( $TARGET_TYPE )"

python dslct.py do_update_depend_ui $TARGET_TYPE

