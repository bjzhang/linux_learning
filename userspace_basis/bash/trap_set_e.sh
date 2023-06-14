#!/bin/bash

set -e

trap 'echo "initramfs failed, fall back up bash"; /bin/bash' EXIT
#do nothing mean cancel the previous trap for EXIT
#trap - EXIT

ls 
ls aaa


echo "ERROR: should not arrive here"
