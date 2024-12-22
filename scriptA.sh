#!/bin/bash

# Function to get the CPU usage of a container
get_container_cpu_usage() {
    docker stats --no-stream --format "{{.CPUPerc}}" "$1" | awk -F'%' '{print $1}'
}

# Function to start a container on a specific CPU core
initialize_container() {
    container=$1
    cpu=$2
    # Remove the container if it already exists
    if docker ps -a -q -f name="$container" > /dev/null; then
        echo "Stopping and removing container $container..."
        docker stop "$container" > /dev/null
        docker rm "$container" > /dev/null
    fi
    echo "Starting container $container on CPU core $cpu..."
    docker run -d --name "$container" --cpuset-cpus="$cpu" --network my-network malynkod/optimafuncnew
}

# Function to update containers if they are active
update_active_containers() {
    docker pull malynkod/optimafuncnew:latest
    containers=("srv1" "srv2" "srv3")
    for container in "${containers[@]}"; do
        if docker ps -q -f name="$container" > /dev/null; then
            echo "Updating container $container..."
            docker stop "$container"
            docker rm "$container"
            initialize_container "$container"  # Restart on the same core
        fi
    done
}

# Function to monitor and manage containers
monitor_and_manage_containers() {
    last_activity_times=([srv1]=$(date +%s) [srv2]=$(date +%s) [srv3]=$(date +%s))

    while true; do
        current_time=$(date +%s)

        # Iterate over all containers to check their status
        for container in srv1 srv2 srv3; do
            if docker ps -q -f name="$container" > /dev/null; then
                usage=$(get_container_cpu_usage "$container")
                echo "CPU usage of container $container: $usage%"

                # If CPU usage is more than 40%, start the next container (gradually)
                if (( $(echo "$usage > 40" | bc -l) )); then
                    echo "$container is overloaded..."
                    if [ "$container" == "srv1" ] && [ ! "$(docker ps -q -f name=srv2)" ]; then
                        echo "Starting srv2 on CPU core 1 because srv1 is overloaded..."
                        initialize_container srv2 1
                    elif [ "$container" == "srv2" ] && [ ! "$(docker ps -q -f name=srv3)" ]; then
                        echo "Starting srv3 on CPU core 2 because srv2 is overloaded..."
                        initialize_container srv3 2
                    fi
                fi

                # If the container is actively working, update its activity time
                if (( $(echo "$usage > 10" | bc -l) )); then
                    last_activity_times[$container]=$current_time
                fi

                # If the container has been idle for more than 60 seconds, stop it
                if [ $(($current_time - ${last_activity_times[$container]})) -gt 60 ]; then
                    echo "$container has been idle for more than 1 minute, stopping it..."
                    docker stop "$container"
                    docker rm "$container"
                fi
            fi
        done

        # Ensure that at least one container is always running
        if [ ! "$(docker ps -q -f name=srv1)" ]; then
            echo "srv1 is not running, starting it..."
            initialize_container srv1 0
        fi

        # Check for container image updates every 2 minutes
        if [ $(( $current_time % 120 )) -eq 0 ]; then
            echo "Checking for container image updates..."
            update_active_containers
        fi

        sleep 5
    done
}

# Main execution block
# Start the primary container (srv1) on CPU core 0
initialize_container srv1 0
# Begin monitoring and managing the containers
monitor_and_manage_containers

