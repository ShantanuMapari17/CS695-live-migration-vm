#!/bin/bash

VM_NAME=$1

# Get the start time
start_time=$(date +%s)

# Perform the migration
# virsh migrate-setmaxdowntime $VM_NAME 5
# virsh migrate-start-postcopy vm-1
virsh migrate --postcopy --live $VM_NAME --unsafe --verbose qemu+ssh://tatha@10.96.27.66/system


# Get the end time
end_time=$(date +%s)

virsh migrate-getmaxdowntime vm-1

# Calculate the migration time
migration_time=$((end_time - start_time))

echo "Total migration time: $migration_time seconds"

# To calculate downtime, you need to monitor the VM and detect when it goes down and when it comes back up.
# This is highly dependent on your specific setup and may require additional tools or scripts.
# Here is a simple example of how you might do it:

# Get the downtime start time
downtime_start=$(date +%s)

# Wait for the VM to go down
while virsh domstate $VM_NAME | grep -q running; do
  sleep 1
done

# Get the downtime end time
downtime_end=$(date +%s)

# Calculate the downtime
downtime=$((downtime_end - downtime_start))

echo "Total downtime: $downtime seconds"


# virsh domifaddr <vm_name>: