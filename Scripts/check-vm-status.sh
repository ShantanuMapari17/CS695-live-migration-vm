#!/bin/bash

VM_NAME=$1
PAUSE_COUNTER=0
OUTPUT_LOCATION="/home/shantanu/CS695/assignment4/vm-migrate-downtime.txt"

while true; do
  # Get the current time
  current_time=$(date +"%Y-%m-%d %T")

  # Get the state of the VM
  vm_state=$(virsh domstate $VM_NAME)

  # Check if the VM is paused
  if [ "$vm_state" == "paused" ]; then
    # If the VM is shut off, increment the pause counter
    PAUSE_COUNTER=$((PAUSE_COUNTER + 1))
  fi

  # Print the VM state, the current time, and the pause counter
  # echo "$current_time: $VM_NAME is $vm_state, paused $PAUSE_COUNTER times"

  # Check if the VM is shut off
  if [ "$vm_state" == "shut off" ]; then
    # If the VM is shut off, break the loop
    break
  fi

  # Wait for 1 millisecond before checking again
  sleep 0.001
done

# Append the pause counter to the file
current_time=$(date +"%Y-%m-%d %T")
echo "$current_time: $VM_NAME is paused $PAUSE_COUNTER times" >> $OUTPUT_LOCATION
echo "output is redirected to $OUTPUT_LOCATION"

