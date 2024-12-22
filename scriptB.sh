#!/bin/bash

# Load balancer URL
URL="http://10.0.2.15/compute"

# Function to send HTTP requests
send_request() {
    local thread_id=$1
    while true; do
        local wait_time=$((RANDOM % 6 + 5))  # Random delay between 5 and 10 seconds
        echo "[$(date)] [Thread $thread_id] Sending request to $URL..."
        curl -s "$URL" > /dev/null
        echo "[$(date)] [Thread $thread_id] Request sent successfully. Waiting for $wait_time seconds."
        sleep $wait_time
    done
}

# Launch multiple asynchronous requests
num_requests=10
echo "[$(date)] Starting $num_requests asynchronous HTTP requests..."

for i in $(seq 1 $num_requests); do
    sleep 0.2  
    send_request $i &  # Run each request in a separate background process
done

# Wait for all background processes to complete
wait

